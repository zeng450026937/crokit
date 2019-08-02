#ifndef YEALINK_RTVC_LIB_UNIFIED_COMMUNICATION_IMPL_H_
#define YEALINK_RTVC_LIB_UNIFIED_COMMUNICATION_IMPL_H_

#include "yealink/rtvc/api/call.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/api/unified_communication.h"
#include "yealink/rtvc/lib/channel_holder.h"

namespace yealink {

namespace rtvc {

class UnifiedCommunicationImpl : public UnifiedCommunication {
 public:
  UnifiedCommunicationImpl();
  ~UnifiedCommunicationImpl() override;

  bool isChannelReady(ChannelType type) override;
  bool isChannelSupported(ChannelType type) override;

  bool isReadyForMedia() override;
  bool isReadyForFocus() override;
  bool isReadyForShare() override;
  bool isReadyForChat() override;

  bool media_supported() override;
  bool focus_supported() override;
  bool share_supported() override;
  bool chat_supported() override;

  bool channel_aware() override;
  void SetChannelAware(bool enable) override;

  const Call* AsCall() override;
  const Conference* AsConference() override;

 private:
  scoped_refptr<ChannelHolder> channel_holder_;

  std::unique_ptr<Call> call_;
  std::unique_ptr<Conference> conference_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_LIB_UNIFIED_COMMUNICATION_IMPL_H_
