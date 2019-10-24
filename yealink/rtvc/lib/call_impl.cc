#include "yealink/rtvc/lib/call_impl.h"

#include "base/logging.h"

namespace rtvc {

CallImpl::CallImpl() {}
CallImpl::~CallImpl() = default;

void CallImpl::Connect() {
  LOG(INFO) << __FUNCTIONW__;
};
void CallImpl::Disconnect() {
  LOG(INFO) << __FUNCTIONW__;
};

void CallImpl::Forward() {
  LOG(INFO) << __FUNCTIONW__;
};
void CallImpl::Refer() {
  LOG(INFO) << __FUNCTIONW__;
};
void CallImpl::Replace() {
  LOG(INFO) << __FUNCTIONW__;
};

void CallImpl::Hold() {
  LOG(INFO) << __FUNCTIONW__;
};
void CallImpl::Unhold() {
  LOG(INFO) << __FUNCTIONW__;
};

void CallImpl::Mute() {
  LOG(INFO) << __FUNCTIONW__;
};
void CallImpl::Unmute() {
  LOG(INFO) << __FUNCTIONW__;
};

// useful when network environment changed
void CallImpl::Renegotiate() {
  LOG(INFO) << __FUNCTIONW__;
};

bool CallImpl::isInProgress() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
};
bool CallImpl::isEstablished() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
  return false;
};
bool CallImpl::isEnded() {
  LOG(INFO) << __FUNCTIONW__;
};

bool CallImpl::local_sharing() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
};
bool CallImpl::remote_sharing() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
};

// start local sharing, remote sharing is always connected
void CallImpl::StartShare() {
  LOG(INFO) << __FUNCTIONW__;
};
void CallImpl::StopShare() {
  LOG(INFO) << __FUNCTIONW__;
};

void CallImpl::SetMediaBitrate(int bitrate) {
  LOG(INFO) << __FUNCTIONW__;
};
void CallImpl::SetShareBitrate(int bitrate){};

// set custom video source for local video streaming, device setted in
// VideoManager is used by default.
void CallImpl::SetLocalVideoSource(VideoSource* source = nullptr) {
  LOG(INFO) << __FUNCTIONW__;
};
void CallImpl::SetLocalShareVideoSource(VideoSource* source = nullptr){};

// TBD
// should we support multiple VideoSink?
// aka, change set(videosink) to add & remove(videosink)
//
// aside note: local video sink is setted in VideoManager
void CallImpl::SetRemoteVideoSink(VideoSink* sink = nullptr) {
  LOG(INFO) << __FUNCTIONW__;
};
void CallImpl::SetRemoteShareVideoSink(VideoSink* sink = nullptr) {
  LOG(INFO) << __FUNCTIONW__;
};

// when conference media session is connected, conference aware means we
// should try to connect conference focus session automatically
bool CallImpl::conference_aware() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
};
void CallImpl::SetConferenceAware(bool enable) {
  LOG(INFO) << __FUNCTIONW__;
};

}  // namespace rtvc
