#include "yealink/rtvc/lib/unified_communication_impl.h"

#include "yealink/rtvc/lib/call_impl.h"
#include "yealink/rtvc/lib/chat_channel_impl.h"
#include "yealink/rtvc/lib/conference_impl.h"
#include "yealink/rtvc/lib/focus_channel_impl.h"
#include "yealink/rtvc/lib/media_channel_impl.h"
#include "yealink/rtvc/lib/share_channel_impl.h"

namespace yealink {

namespace rtvc {

UnifiedCommunicationImpl::UnifiedCommunicationImpl()
    : channel_holder_(base::MakeRefCounted<ChannelHolder>(
          std::make_unique<MediaChannelImpl>(),
          std::make_unique<FocusChannelImpl>(),
          std::make_unique<ShareChannelImpl>(),
          std::make_unique<ChatChannelImpl>())),
      call_(new CallImpl(channel_holder_)),
      conference_(new ConferenceImpl(channel_holder_)) {}
UnifiedCommunicationImpl::~UnifiedCommunicationImpl() {}

bool UnifiedCommunicationImpl::isChannelReady(ChannelType type) {
  switch (type) {
    case ChannelType::kMedia:
      return channel_holder_->media_channel()->isEstablished();
    case ChannelType::kFocus:
      return channel_holder_->focus_channel()->isEstablished();
    case ChannelType::kShare:
      return channel_holder_->share_channel()->isEstablished();
    case ChannelType::kChat:
      return channel_holder_->chat_channel()->isEstablished();
  }
}

const Call* UnifiedCommunicationImpl::AsCall() {
  return call_.get();
}
const Conference* UnifiedCommunicationImpl::AsConference() {
  return conference_.get();
}

}  // namespace rtvc

}  // namespace yealink
