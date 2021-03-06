#include <node.h>

#include "base/debug/stack_trace.h"
#include "base/memory/ptr_util.h"
#include "yealink/native_mate/dictionary.h"
#include "yealink/rtvc/api/video/i420_buffer.h"
#include "yealink/rtvc/binding/audio_manager_binding.h"
#include "yealink/rtvc/binding/bootstrap_binding.h"
#include "yealink/rtvc/binding/call_binding.h"
#include "yealink/rtvc/binding/cloud_contact_binding.h"
#include "yealink/rtvc/binding/conference_binding.h"
#include "yealink/rtvc/binding/connector_binding.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/desktop_capture_binding.h"
#include "yealink/rtvc/binding/local_contact_binding.h"
#include "yealink/rtvc/binding/schedule_binding.h"
#include "yealink/rtvc/binding/user_agent_binding.h"
#include "yealink/rtvc/binding/v8_util.h"
#include "yealink/rtvc/binding/video_frame_binding.h"
#include "yealink/rtvc/binding/video_manager_binding.h"
#include "yealink/rtvc/binding/ytms_binding.h"

namespace {

using yealink::rtvc::AudioManagerBinding;
using yealink::rtvc::BootstrapBinding;
using yealink::rtvc::CallBinding;
using yealink::rtvc::CloudContactBinding;
using yealink::rtvc::ConferenceBinding;
using yealink::rtvc::ConnectorBinding;
using yealink::rtvc::DesktopCaptureBinding;
using yealink::rtvc::LocalContactBinding;
using yealink::rtvc::ScheduleBinding;
using yealink::rtvc::UserAgentBinding;
using yealink::rtvc::VideoFrameBinding;
using yealink::rtvc::VideoManagerBinding;
using yealink::rtvc::YTMSBinding;

void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
#if defined(DEBUG)
  _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);

  _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG | _CRTDBG_MODE_FILE);
  _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);

  _set_error_mode(_OUT_TO_STDERR);
  
  base::debug::EnableInProcessStackDumping();
#endif
  v8::Isolate* isolate = context->GetIsolate();

  yealink::rtvc::Context::Instance()->Initialize(isolate);
  // setup exports
  mate::Dictionary dict(isolate, exports);

  dict.Set("version", "1.0.0-alpha");

  mate::Dictionary v8_util = mate::Dictionary::CreateEmpty(isolate);
  v8_util.SetMethod("getHiddenValue", &yealink::rtvc::GetHiddenValue);
  v8_util.SetMethod("setHiddenValue", &yealink::rtvc::SetHiddenValue);
  v8_util.SetMethod("deleteHiddenValue", &yealink::rtvc::DeleteHiddenValue);
  v8_util.SetMethod("getObjectHash", &yealink::rtvc::GetObjectHash);
  v8_util.SetMethod("takeHeapSnapshot", &yealink::rtvc::TakeHeapSnapshot);
  v8_util.SetMethod("requestGarbageCollectionForTesting",
                    &yealink::rtvc::RequestGarbageCollectionForTesting);
  dict.Set("v8Util", v8_util);

  DesktopCaptureBinding::SetConstructor(
      isolate, base::BindRepeating(&DesktopCaptureBinding::New));
  dict.Set("DesktopCapture", DesktopCaptureBinding::GetConstructor(isolate)
                                 ->GetFunction(context)
                                 .ToLocalChecked());

  UserAgentBinding::SetConstructor(isolate,
                                   base::BindRepeating(&UserAgentBinding::New));
  dict.Set("UserAgent", UserAgentBinding::GetConstructor(isolate)
                            ->GetFunction(context)
                            .ToLocalChecked());

  CallBinding::SetConstructor(isolate, base::BindRepeating(&CallBinding::New));
  dict.Set("Call", CallBinding::GetConstructor(isolate)
                       ->GetFunction(context)
                       .ToLocalChecked());

  ConferenceBinding::SetConstructor(
      isolate, base::BindRepeating(&ConferenceBinding::New));
  dict.Set("Conference", ConferenceBinding::GetConstructor(isolate)
                             ->GetFunction(context)
                             .ToLocalChecked());

  AudioManagerBinding::SetConstructor(
      isolate, base::BindRepeating(&AudioManagerBinding::New));
  dict.Set("AudioManager", AudioManagerBinding::GetConstructor(isolate)
                               ->GetFunction(context)
                               .ToLocalChecked());

  VideoManagerBinding::SetConstructor(
      isolate, base::BindRepeating(&VideoManagerBinding::New));
  dict.Set("VideoManager", VideoManagerBinding::GetConstructor(isolate)
                               ->GetFunction(context)
                               .ToLocalChecked());

  BootstrapBinding::SetConstructor(isolate,
                                   base::BindRepeating(&BootstrapBinding::New));
  dict.Set("Bootstrap", BootstrapBinding::GetConstructor(isolate)
                            ->GetFunction(context)
                            .ToLocalChecked());

  ConnectorBinding::SetConstructor(isolate,
                                   base::BindRepeating(&ConnectorBinding::New));
  dict.Set("Connector", ConnectorBinding::GetConstructor(isolate)
                            ->GetFunction(context)
                            .ToLocalChecked());

  ScheduleBinding::SetConstructor(isolate,
                                  base::BindRepeating(&ScheduleBinding::New));
  dict.Set("Schedule", ScheduleBinding::GetConstructor(isolate)
                           ->GetFunction(context)
                           .ToLocalChecked());

  CloudContactBinding::SetConstructor(
      isolate, base::BindRepeating(&CloudContactBinding::New));
  dict.Set("CloudContact", CloudContactBinding::GetConstructor(isolate)
                               ->GetFunction(context)
                               .ToLocalChecked());

  LocalContactBinding::SetConstructor(
      isolate, base::BindRepeating(&LocalContactBinding::New));
  dict.Set("LocalContact", LocalContactBinding::GetConstructor(isolate)
                               ->GetFunction(context)
                               .ToLocalChecked());

  YTMSBinding::SetConstructor(isolate, base::BindRepeating(&YTMSBinding::New));
  dict.Set("YTMS", YTMSBinding::GetConstructor(isolate)
                       ->GetFunction(context)
                       .ToLocalChecked());
}

}  // namespace

NODE_MODULE_CONTEXT_AWARE(yealink_rtvc, Initialize)
