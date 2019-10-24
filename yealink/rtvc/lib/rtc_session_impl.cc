#include "yealink/rtvc/lib/rtc_session_impl.h"

#include "base/logging.h"

namespace rtvc {

RTCSessionImpl::RTCSessionImpl() {}
RTCSessionImpl::~RTCSessionImpl() = default;

void RTCSessionImpl::CreateOffer() {
  LOG(INFO) << __FUNCTIONW__;
}
void RTCSessionImpl::CreateAnswer() {
  LOG(INFO) << __FUNCTIONW__;
}

void RTCSessionImpl::Close() {
  LOG(INFO) << __FUNCTIONW__;
}

bool RTCSessionImpl::ice() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void RTCSessionImpl::SetICE(bool enable) {
  LOG(INFO) << __FUNCTIONW__;
}

bool RTCSessionImpl::dtls() {
  LOG(INFO) << __FUNCTIONW__;
  return false;
}
void RTCSessionImpl::SetDTLS(bool enable) {
  LOG(INFO) << __FUNCTIONW__;
}

std::string RTCSessionImpl::local_description() {
  LOG(INFO) << __FUNCTIONW__;
  return "";
}
std::string RTCSessionImpl::remote_descrition() {
  LOG(INFO) << __FUNCTIONW__;
  return "";
}

void RTCSessionImpl::SetLocalDescription(std::string desc) {
  LOG(INFO) << __FUNCTIONW__;
}
void RTCSessionImpl::SetRemoteDescription(std::string desc) {
  LOG(INFO) << __FUNCTIONW__;
}

void RTCSessionImpl::SetLocalVideoSink() {
  LOG(INFO) << __FUNCTIONW__;
}
void RTCSessionImpl::SetRemoteVideoSink() {
  LOG(INFO) << __FUNCTIONW__;
}

void RTCSessionImpl::InsertDTMF(std::string tones,
                                int duration = 100,
                                int inter_tone_gap = 100) {
  LOG(INFO) << __FUNCTIONW__;
}

void RTCSessionImpl::GetStats() {
  LOG(INFO) << __FUNCTIONW__;
}

void RTCSessionImpl::SetBitrate(int bitrate) {
  LOG(INFO) << __FUNCTIONW__;
}

}  // namespace rtvc
