#include "yealink/rtvc/binding/call_binding.h"

#include "base/logging.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/context.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* CallBinding::New(mate::Arguments* args) {
  mate::Handle<UserAgentBinding> user_agent;

  if (args->Length() < 1 || !args->GetNext(&user_agent) ||
      user_agent.IsEmpty()) {
    args->ThrowError("UserAgent is required to construct Call");
    return nullptr;
  }

  return new CallBinding(args->isolate(), args->GetThis(), user_agent);
}

// static
void CallBinding::BuildPrototype(v8::Isolate* isolate,
                                 v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "Call"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetMethod("connect", &CallBinding::Connect)
      .SetMethod("disconnect", &CallBinding::Disconnect)
      .SetMethod("forward", &CallBinding::Forward)
      .SetMethod("refer", &CallBinding::Refer)
      .SetMethod("replace", &CallBinding::Replace)
      .SetMethod("hold", &CallBinding::Hold)
      .SetMethod("unhold", &CallBinding::Unhold)
      .SetMethod("mute", &CallBinding::Mute)
      .SetMethod("unmute", &CallBinding::Unmute)
      .SetMethod("renegotiate", &CallBinding::Renegotiate)
      .SetProperty("isInProgress", &CallBinding::isInProgress)
      .SetProperty("isEstablished", &CallBinding::isEstablished)
      .SetProperty("isEnded", &CallBinding::isEnded)
      .SetProperty("localSharing", &CallBinding::local_sharing)
      .SetProperty("remoteSharing", &CallBinding::remote_sharing)
      .SetMethod("startShare", &CallBinding::StartShare)
      .SetMethod("stopShare", &CallBinding::StopShare)
      .SetMethod("setMediaBitrate", &CallBinding::SetMediaBitrate)
      .SetMethod("setShareBitrate", &CallBinding::SetShareBitrate)
      .SetMethod("setLocalVideoSource", &CallBinding::SetLocalVideoSource)
      .SetMethod("setLocalShareVideoSource",
                 &CallBinding::SetLocalShareVideoSource)
      .SetMethod("setRemoteVideoSink", &CallBinding::SetRemoteVideoSink)
      .SetMethod("setRemoteShareVideoSink",
                 &CallBinding::SetRemoteShareVideoSink)
      .SetProperty("conferenceAware", &CallBinding::conference_aware,
                   &CallBinding::SetConferenceAware)
      .SetMethod("asConference", &CallBinding::AsConference);
}

CallBinding::CallBinding(v8::Isolate* isolate,
                         v8::Local<v8::Object> wrapper,
                         mate::Handle<UserAgentBinding> user_agent)
    : CallBinding(isolate, wrapper, user_agent->GetWeakPtr()) {}
CallBinding::CallBinding(v8::Isolate* isolate,
                         v8::Local<v8::Object> wrapper,
                         base::WeakPtr<UserAgentBinding> user_agent)
    : user_agent_(user_agent),
      sip_client_(user_agent->GetWeakSIPClientPtr()),
      media_(Context::Instance()->GetMedia()),
      meeting_(
          yealink::CreateMeeting(*sip_client_, *media_, false /* incoming */)) {
  InitWith(isolate, wrapper);
}
CallBinding::~CallBinding() {
  LOG(INFO) << __FUNCTIONW__;
}

void CallBinding::Connect(mate::Arguments* args) {
  LOG(INFO) << __FUNCTIONW__;
  std::string target;

  if (!args->GetNext(&target)) {
    args->ThrowError("Target is required to make a call");
    return;
  }

  yealink::DailParam param;
  param.strUri = target.c_str();
  param.typAVContent = yealink::AV_VIDEO_AUDIO;

  meeting_->Dail(param);
}
void CallBinding::Disconnect() {
  LOG(INFO) << __FUNCTIONW__;
}

void CallBinding::Forward() {
  LOG(INFO) << __FUNCTIONW__;
}
void CallBinding::Refer() {
  LOG(INFO) << __FUNCTIONW__;
}
void CallBinding::Replace() {
  LOG(INFO) << __FUNCTIONW__;
}

void CallBinding::Hold() {
  LOG(INFO) << __FUNCTIONW__;
}
void CallBinding::Unhold() {
  LOG(INFO) << __FUNCTIONW__;
}

void CallBinding::Mute() {
  LOG(INFO) << __FUNCTIONW__;
}
void CallBinding::Unmute() {
  LOG(INFO) << __FUNCTIONW__;
}

void CallBinding::Renegotiate() {
  LOG(INFO) << __FUNCTIONW__;
}

bool CallBinding::isInProgress() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
bool CallBinding::isEstablished() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
bool CallBinding::isEnded() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}

bool CallBinding::local_sharing() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
bool CallBinding::remote_sharing() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}

void CallBinding::StartShare() {
  LOG(INFO) << __FUNCTIONW__;
}
void CallBinding::StopShare() {
  LOG(INFO) << __FUNCTIONW__;
}

void CallBinding::SetMediaBitrate(int bitrate) {
  LOG(INFO) << __FUNCTIONW__;
}
void CallBinding::SetShareBitrate(int bitrate) {
  LOG(INFO) << __FUNCTIONW__;
}

void CallBinding::SetLocalVideoSource(mate::PersistentDictionary source) {
  LOG(INFO) << __FUNCTIONW__;
}
void CallBinding::SetLocalShareVideoSource(mate::PersistentDictionary source) {
  LOG(INFO) << __FUNCTIONW__;
}

void CallBinding::SetRemoteVideoSink(mate::PersistentDictionary sink) {
  LOG(INFO) << __FUNCTIONW__;
}
void CallBinding::SetRemoteShareVideoSink(mate::PersistentDictionary sink) {
  LOG(INFO) << __FUNCTIONW__;
}

bool CallBinding::conference_aware() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void CallBinding::SetConferenceAware(bool enable) {
  LOG(INFO) << __FUNCTIONW__;
}

void CallBinding::AsConference() {
  LOG(INFO) << __FUNCTIONW__;
}

void CallBinding::SetUserAgent(mate::Handle<UserAgentBinding> user_agent) {
  user_agent_ = user_agent->GetWeakPtr();
}

}  // namespace rtvc

}  // namespace yealink
