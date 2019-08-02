#include "yealink/rtvc/lib/channel_impl.h"

#include "base/logging.h"

namespace yealink {

namespace rtvc {

ChannelImpl::ChannelImpl() {}
ChannelImpl::~ChannelImpl() = default;

bool ChannelImpl::isInProgress() {
  return state_ == ChannelState::kConnecting;
}
bool ChannelImpl::isEstablished() {
  return state_ == ChannelState::kConnected;
}
bool ChannelImpl::isEnded() {
  return state_ == ChannelState::kFinished || state_ == ChannelState::kFailed;
}

void ChannelImpl::Offer() {
  LOG(INFO) << __FUNCTIONW__;
}
void ChannelImpl::Answer() {
  LOG(INFO) << __FUNCTIONW__;
}

void ChannelImpl::ChannelImpl::Refer() {
  LOG(INFO) << __FUNCTIONW__;
}

void SendDTMF() {
  LOG(INFO) << __FUNCTIONW__;
}
void ChannelImpl::SendInfo() {
  LOG(INFO) << __FUNCTIONW__;
}

void ChannelImpl::Renegotiate() {
  LOG(INFO) << __FUNCTIONW__;
}

}  // namespace rtvc

}  // namespace yealink
