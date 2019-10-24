#ifndef YEALINK_RTVC_LIB_CHANNEL_IMPL_H_
#define YEALINK_RTVC_LIB_CHANNEL_IMPL_H_

#include "yealink/rtvc/api/channel.h"


namespace rtvc {

class ChannelImpl : public Channel {
 public:
  ChannelImpl();
  ~ChannelImpl();

  ChannelType type() override { return type_; }
  ChannelState state() override { return state_; }
  ChannelDirection direction() override { return direction_; }

  std::string local_identity() override { return local_identity_; }
  std::string remote_identity() override { return remote_identity_; }

  bool isInProgress() override;
  bool isEstablished() override;
  bool isEnded() override;

  void Offer() override;
  void Answer() override;

  void Refer() override;

  void SendDTMF() override;
  void SendInfo() override;

  void Renegotiate() override;

 private:
  ChannelType type_;
  ChannelState state_;
  ChannelDirection direction_;

  std::string local_identity_;
  std::string remote_identity_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_LIB_CHANNEL_IMPL_H_
