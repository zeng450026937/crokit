#include "yealink/rtvc/lib/channel_holder.h"

namespace yealink {

namespace rtvc {

ChannelHolder::ChannelHolder(std::unique_ptr<MediaChannel> media_channel,
                             std::unique_ptr<FocusChannel> focus_channel,
                             std::unique_ptr<ShareChannel> share_channel,
                             std::unique_ptr<ChatChannel> chat_channel)
    : media_channel_(std::move(media_channel)),
      focus_channel_(std::move(focus_channel)),
      share_channel_(std::move(share_channel)),
      chat_channel_(std::move(chat_channel)) {}

}  // namespace rtvc

}  // namespace yealink
