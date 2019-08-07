#include <node.h>

#include "base/memory/ptr_util.h"
#include "yealink/native_mate/dictionary.h"
#include "yealink/rtvc/api/video/i420_buffer.h"
#include "yealink/rtvc/binding/audio_manager_binding.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/user_agent_binding.h"
#include "yealink/rtvc/binding/v8_util.h"
#include "yealink/rtvc/binding/video_frame_binding.h"
#include "yealink/rtvc/binding/video_manager_binding.h"

namespace {

using yealink::rtvc::AudioManagerBinding;
using yealink::rtvc::UserAgentBinding;
using yealink::rtvc::VideoFrameBinding;
using yealink::rtvc::VideoManagerBinding;

void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
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

  UserAgentBinding::SetConstructor(isolate,
                                   base::BindRepeating(&UserAgentBinding::New));
  dict.Set("UserAgent", UserAgentBinding::GetConstructor(isolate)
                            ->GetFunction(context)
                            .ToLocalChecked());

  dict.Set("audioManager", AudioManagerBinding::Create(isolate));
  dict.Set("videoManager", VideoManagerBinding::Create(isolate));

  auto buffer = yealink::rtvc::I420BufferImpl::Create(480, 360);
  yealink::rtvc::I420BufferImpl::SetBlack(buffer.get());

  auto frame = yealink::rtvc::VideoFrame::Builder()
                   .set_video_frame_buffer(buffer)
                   .build();

  dict.Set("videoFrame", VideoFrameBinding::Create(isolate, frame));
}

}  // namespace

NODE_MODULE_CONTEXT_AWARE(yealink_rtvc, Initialize)
