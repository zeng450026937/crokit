#include "yealink/rtvc/binding/call_binding.h"

#include "base/logging.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* CallBinding::New(mate::Arguments* args) {
  UserAgent::Config config;
  mate::Dictionary options;

  if (!args->GetNext(&options)) {
    args->ThrowError();
    return nullptr;
  }

  options.Get("username", &config.username);
  options.Get("password", &config.password);
  options.Get("domain", &config.domain);

  return new CallBinding(args->isolate(), args->GetThis(),
                              UserAgent::Create(std::move(config)));
}

// static
void CallBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  LOG(INFO) << __FUNCTIONW__;
  prototype->SetClassName(mate::StringToV8(isolate, "UserAgent"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("workspaceFolder", &UserAgentBinding::workspace_folder)
      .SetProperty("username", &UserAgentBinding::username)
      .SetProperty("password", &UserAgentBinding::password)
      .SetProperty("domain", &UserAgentBinding::domain)
      .SetMethod("register", &UserAgentBinding::Register)
      .SetMethod("unregister", &UserAgentBinding::UnRegister)
      .SetProperty("registered", &UserAgentBinding::registered);
}


CallBinding::CallBinding(v8::Isolate* isolate) {
  Init(isolate);
}
CallBinding::~CallBinding() {}

void CallBinding::Connect() {
  LOG(INFO) << __FUNCTIONW__;
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

void CallBinding::SetLocalVideoSource(VideoSource* source = nullptr) {
  LOG(INFO) << __FUNCTIONW__;
}
void CallBinding::SetLocalShareVideoSource(VideoSource* source = nullptr) {
  LOG(INFO) << __FUNCTIONW__;
}

void CallBinding::SetRemoteVideoSink(VideoSink* sink = nullptr) {
  LOG(INFO) << __FUNCTIONW__;
}
void CallBinding::SetRemoteShareVideoSink(VideoSink* sink = nullptr) {
  LOG(INFO) << __FUNCTIONW__;
}

bool CallBinding::conference_aware() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void CallBinding::SetConferenceAware(bool enable) {
  LOG(INFO) << __FUNCTIONW__;
}

}  // namespace rtvc

}  // namespace yealink
