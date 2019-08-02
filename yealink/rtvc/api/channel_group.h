#ifndef YEALINK_RTVC_API_CHANNEL_GROUP_H_
#define YEALINK_RTVC_API_CHANNEL_GROUP_H_

#include "yealink/rtvc/api/channel.h"

namespace yealink {

namespace rtvc {

class Call;
class Conference;

class ChannelGroup {
 public:
  virtual bool isChannelReady(ChannelType type) = 0;
  virtual bool isChannelSupported(ChannelType type) = 0;

  virtual bool isReadyForMedia() = 0;
  virtual bool isReadyForFocus() = 0;
  virtual bool isReadyForShare() = 0;
  virtual bool isReadyForChat() = 0;

  virtual bool media_supported() = 0;
  virtual bool focus_supported() = 0;
  virtual bool share_supported() = 0;
  virtual bool chat_supported() = 0;

  virtual bool channel_aware() = 0;
  virtual void SetChannelAware(bool enable) = 0;

  virtual const Call* AsCall() = 0;
  virtual const Conference* AsConference() = 0;

 protected:
  virtual ~ChannelGroup() = default;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_CHANNEL_GROUP_H_
