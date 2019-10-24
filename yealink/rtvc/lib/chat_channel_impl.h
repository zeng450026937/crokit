#ifndef YEALINK_RTVC_LIB_CHAT_CHANNEL_IMPL_H_
#define YEALINK_RTVC_LIB_CHAT_CHANNEL_IMPL_H_

#include "yealink/rtvc/api/chat_channel.h"

namespace rtvc {

class ChatChannelImpl : public ChatChannel {
 public:
  ChatChannelImpl();
  ~ChatChannelImpl() override;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_LIB_CHAT_CHANNEL_IMPL_H_
