#ifndef YEALINK_RTVC_API_CHAT_CHANNEL_H_
#define YEALINK_RTVC_API_CHAT_CHANNEL_H_

#include "yealink/rtvc/api/channel.h"

namespace rtvc {

class ChatChannelObserver : public ChannelObserver {
 public:
  // chat
  virtual void OnChatMessage() = 0;

 protected:
  virtual ~ChatChannelObserver() = default;
};

class ChatChannel : public Channel {
 public:
  static std::unique_ptr<ChatChannel> Create(ChatChannelObserver* observer);

  ChannelType type() override { return ChannelType::kChat; }

  virtual void SendMessage() = 0;

 protected:
  virtual ~ChatChannel() = default;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_API_CHAT_CHANNEL_H_
