#include "yealink/rtvc/binding/context.h"

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
#include "yealink/rtvc/binding/null_task_runner.h"

namespace yealink {

namespace rtvc {

namespace {
bool g_initialized = false;
v8::Isolate* g_isolate = nullptr;
base::FilePath g_workspace_folder;
}  // namespace

// static
void Context::Initialize(v8::Isolate* isolate) {
  DCHECK(!g_initialized);

  g_isolate = isolate;

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

  scoped_refptr<base::SingleThreadTaskRunner> task_runner =
      base::MakeRefCounted<yealink::node::NullTaskRunner>();

  static gin::IsolateHolder instance(
      task_runner, gin::IsolateHolder::IsolateType::kNode, isolate);

  base::PathService::Get(base::DIR_MODULE, &g_workspace_folder);

#if defined(OS_WIN)
  std::vector<base::FilePath::StringType> components;
  g_workspace_folder.GetComponents(&components);
  components.erase(components.begin());
  components.erase(components.begin());
  g_workspace_folder =
      base::FilePath(base::JoinString(components, base::FilePath::kSeparators));
#endif

  g_initialized = true;

  LOG(INFO) << g_workspace_folder << g_workspace_folder.value();
}

// static
v8::Isolate* Context::GetIsolate() {
  return g_isolate;
}

// static
const base::FilePath& Context::GetWorkspaceFolder() {
  return g_workspace_folder;
}
// static
void Context::SetWorkspaceFolder(const base::FilePath& workspace_folder) {
  g_workspace_folder = workspace_folder;
}

}  // namespace rtvc

}  // namespace yealink
