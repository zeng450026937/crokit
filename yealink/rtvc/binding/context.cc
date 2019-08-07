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
#include "base/path_service.h"
#include "base/strings/string_util.h"
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

Context::Context() {}
Context::~Context() {
  // if (media_) {
  //   Media::ReleaseInstance(media_);
  // }
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

  static base::AtExitManager at_exit;

  base::CommandLine::Init(0, nullptr);
  base::FeatureList::SetInstance(base::WrapUnique(new base::FeatureList));

  // setup logging
  logging::LoggingSettings settings;
  settings.logging_dest = logging::LOG_TO_SYSTEM_DEBUG_LOG;

  logging::InitLogging(settings);
  logging::SetLogItems(true, false, true, false);

  // setup gin
  gin::IsolateHolder::Initialize(gin::IsolateHolder::kStrictMode,
                                 gin::ArrayBufferAllocator::SharedInstance(),
                                 nullptr,
                                 gin::IsolateHolder::IsolateType::kNode);

  task_runner_ = base::MakeRefCounted<yealink::rtvc::LibuvTaskRunner>();

  static gin::IsolateHolder instance(
      task_runner_, gin::IsolateHolder::IsolateType::kNode, isolate);

  media_ =
      yealink::Media::CreateInstance(workspace_folder_.AsUTF8Unsafe().c_str());

  ::node::AddEnvironmentCleanupHook(
      isolate,
      [](void* arg) {
        Context* context = reinterpret_cast<Context*>(arg);
        delete context;
      },
      this);

  initialized_ = true;
}

scoped_refptr<base::SingleThreadTaskRunner> Context::GetTaskRunner() {
  return task_runner_;
}

v8::Isolate* Context::GetIsolate() {
  return isolate_;
}

base::FilePath Context::GetWorkspaceFolder() {
  return workspace_folder_;
}

Media* Context::GetMedia() {
  return media_;
}

}  // namespace rtvc

}  // namespace yealink
