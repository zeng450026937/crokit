#ifndef YEALINK_RTVC_LIB_CHANNEL_HOLDER_H_
#define YEALINK_RTVC_LIB_CHANNEL_HOLDER_H_

#include <memory>

#include "base/memory/ref_counted.h"
#include "base/supports_user_data.h"

#include "yealink/rtvc/api/chat_channel.h"
#include "yealink/rtvc/api/focus_channel.h"
#include "yealink/rtvc/api/media_channel.h"
#include "yealink/rtvc/api/share_channel.h"

namespace yealink {

namespace rtvc {

class ChannelHolder : public base::RefCounted<ChannelHolder> {
 public:
  explicit ChannelHolder(std::unique_ptr<MediaChannel> media_channel,
                         std::unique_ptr<FocusChannel> focus_channel,
                         std::unique_ptr<ShareChannel> share_channel,
                         std::unique_ptr<ChatChannel> chat_channel);
  ~ChannelHolder() = default;

  MediaChannel* media_channel() { return media_channel_.get(); }
  FocusChannel* focus_channel() { return focus_channel_.get(); }
  ShareChannel* share_channel() { return share_channel_.get(); }
  ChatChannel* chat_channel() { return chat_channel_.get(); }

 private:
  std::unique_ptr<MediaChannel> media_channel_;
  std::unique_ptr<FocusChannel> focus_channel_;
  std::unique_ptr<ShareChannel> share_channel_;
  std::unique_ptr<ChatChannel> chat_channel_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_LIB_CHANNEL_HOLDER_H_
