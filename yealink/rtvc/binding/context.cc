#include "yealink/rtvc/binding/context.h"

#include <node.h>
#include "base/at_exit.h"
#include "base/base_paths.h"
#include "base/bind.h"
#include "base/command_line.h"
#include "base/feature_list.h"
#include "base/logging.h"
#include "base/memory/ptr_util.h"
#include "base/memory/scoped_refptr.h"
#include "base/message_loop/message_loop.h"
#include "base/no_destructor.h"
#include "base/path_service.h"
#include "base/run_loop.h"
#include "base/strings/string_util.h"
#include "base/task/task_scheduler/task_scheduler.h"
#include "base/threading/thread_task_runner_handle.h"
#include "base/unguessable_token.h"
#include "gin/array_buffer.h"
#include "gin/public/isolate_holder.h"
#include "yealink/libvc/include/media/media_api.h"
#include "yealink/rtvc/binding/libuv_task_runner.h"
#include "yealink/rtvc/binding/null_task_runner.h"
#include "yealink/rtvc/binding/uv_task_runner.h"

namespace yealink {

namespace rtvc {

// static
Context* Context::Instance() {
  static Context* instance = new Context();
  return instance;
}

Context::Context() : unique_id_(base::UnguessableToken::Create().ToString()) {}
Context::~Context() {
  // Make sure destruction callbacks are called before message loop is
  // destroyed, otherwise some objects that need to be deleted on IO thread
  // won't be freed.
  // We don't use ranged for loop because iterators are getting invalided when
  // the callback runs.
  for (auto iter = destructors_.begin(); iter != destructors_.end();) {
    base::OnceClosure callback = std::move(*iter);
    if (!callback.is_null())
      std::move(callback).Run();
    ++iter;
  }
  
  if (base::TaskScheduler::GetInstance()) {
    base::TaskScheduler::GetInstance()->Shutdown();
  }
  if (media_) {
    Media::ReleaseInstance(media_);
  }
}

void Context::Initialize(v8::Isolate* isolate) {
  base::FilePath workspace_folder;
  base::PathService::Get(base::DIR_MODULE, &workspace_folder);

#if defined(OS_WIN)
  std::vector<base::FilePath::StringType> components;
  workspace_folder.GetComponents(&components);
  components.erase(components.begin());
  components.erase(components.begin());
  workspace_folder =
      base::FilePath(base::JoinString(components, base::FilePath::kSeparators));
#endif

  Initialize(isolate, workspace_folder);
}

void Context::Initialize(v8::Isolate* isolate,
                         const base::FilePath& workspace_folder) {
  DCHECK(!initialized_);

  isolate_ = isolate;
  workspace_folder_ = workspace_folder;

  at_exit_.reset(new base::AtExitManager);

  base::CommandLine::Init(0, nullptr);
  base::FeatureList::SetInstance(base::WrapUnique(new base::FeatureList));

  // setup logging
  logging::LoggingSettings settings;
  settings.logging_dest = logging::LOG_TO_SYSTEM_DEBUG_LOG;

  logging::InitLogging(settings);
  logging::SetLogItems(true, false, true, false);

  task_runner_ = base::MakeRefCounted<yealink::rtvc::UvTaskRunner>();
  high_priority_task_runner_ =
      base::MakeRefCounted<yealink::rtvc::LibuvTaskRunner>();

  message_loop_.reset(new base::MessageLoop);
  message_loop_->SetTaskRunner(high_priority_task_runner_);

  // base::ThreadTaskRunnerHandle handle(high_priority_task_runner_);

  base::TaskScheduler::CreateAndStartWithDefaultParams("rtvc");

  // setup gin
  gin::IsolateHolder::Initialize(gin::IsolateHolder::kStrictMode,
                                 gin::ArrayBufferAllocator::SharedInstance(),
                                 nullptr,
                                 gin::IsolateHolder::IsolateType::kNode);

  static gin::IsolateHolder instance(
      task_runner_, gin::IsolateHolder::IsolateType::kNode, isolate);

  ::node::AddEnvironmentCleanupHook(
      isolate,
      [](void* arg) {
        Context* context = reinterpret_cast<Context*>(arg);
        delete context;
      },
      Context::Instance());

  initialized_ = true;
}

void Context::RegisterDestructionCallback(base::OnceClosure callback) {
  // The destructors should be called in reversed order, so dependencies between
  // JavaScript objects can be correctly resolved.
  // For example WebContentsView => WebContents => Session.
  destructors_.insert(destructors_.begin(), std::move(callback));
}

scoped_refptr<base::SingleThreadTaskRunner> Context::GetTaskRunner(
    bool high_priority) {
  return high_priority ? high_priority_task_runner_ : task_runner_;
}

bool Context::CalledOnValidThread() {
  return thread_checker_.CalledOnValidThread();
}

void Context::PostTask(const base::Location& from_here,
                       base::OnceClosure task) {
  high_priority_task_runner_->PostDelayedTask(from_here, std::move(task),
                                              base::TimeDelta());
}
void Context::PostDelayedTask(const base::Location& from_here,
                              base::OnceClosure task) {
  task_runner_->PostDelayedTask(from_here, std::move(task), base::TimeDelta());
}

v8::Isolate* Context::GetIsolate() {
  return isolate_;
}

std::string Context::GetUniqueId() {
  return unique_id_;
}

base::FilePath Context::GetWorkspaceFolder() {
  return workspace_folder_;
}

Media* Context::GetMedia() {
  if (!media_) {
    media_ = yealink::Media::CreateInstance(
        workspace_folder_.AsUTF8Unsafe().c_str());
  }

  return media_;
}

}  // namespace rtvc

}  // namespace yealink
