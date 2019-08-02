#include <node.h>

#include "base/at_exit.h"
#include "base/bind.h"
#include "base/command_line.h"
#include "base/feature_list.h"
#include "base/logging.h"
#include "base/memory/ptr_util.h"
#include "base/memory/scoped_refptr.h"
#include "gin/array_buffer.h"

#include "yealink/native_mate/dictionary.h"
#include "yealink/rtvc/binding/audio_manager_binding.h"
#include "yealink/rtvc/binding/libuv_task_runner.h"
#include "yealink/rtvc/binding/null_task_runner.h"
#include "yealink/rtvc/binding/user_agent_binding.h"
#include "yealink/rtvc/binding/video_manager_binding.h"

namespace {

using yealink::rtvc::AudioManagerBinding;
using yealink::rtvc::UserAgentBinding;
using yealink::rtvc::VideoManagerBinding;

void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
  static base::AtExitManager at_exit;
  base::CommandLine::Init(0, nullptr);
  base::FeatureList::SetInstance(base::WrapUnique(new base::FeatureList));

  logging::LoggingSettings settings;
  settings.logging_dest = logging::LOG_TO_SYSTEM_DEBUG_LOG;

  logging::InitLogging(settings);
  logging::SetLogItems(true, false, true, false);

  gin::IsolateHolder::Initialize(gin::IsolateHolder::kStrictMode,
                                 gin::ArrayBufferAllocator::SharedInstance(),
                                 nullptr,
                                 gin::IsolateHolder::IsolateType::kNode);

  v8::Isolate* isolate = context->GetIsolate();

  static gin::IsolateHolder instance(
      base::MakeRefCounted<yealink::node::NullTaskRunner>(),
      gin::IsolateHolder::IsolateType::kNode, isolate);

  mate::Dictionary dict(isolate, exports);
  dict.Set("version", "1.0.0-alpha");

  UserAgentBinding::SetConstructor(isolate,
                                   base::BindRepeating(&UserAgentBinding::New));
  dict.Set("UserAgent", UserAgentBinding::GetConstructor(isolate)
                            ->GetFunction(context)
                            .ToLocalChecked());

  dict.Set("audioManager", AudioManagerBinding::Create(isolate));
  dict.Set("videoManager", VideoManagerBinding::Create(isolate));
}

}  // namespace

NODE_MODULE_CONTEXT_AWARE(yealink_rtvc, Initialize)
