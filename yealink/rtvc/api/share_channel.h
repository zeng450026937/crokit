#ifndef YEALINK_RTVC_API_SHARE_CHANNEL_H_
#define YEALINK_RTVC_API_SHARE_CHANNEL_H_

#include "base/optional.h"
#include "yealink/rtvc/api/channel.h"

namespace yealink {

namespace rtvc {

class ShareChannelObserver : public ChannelObserver {
 protected:
  virtual ~ShareChannelObserver() = default;
};

class ShareChannel : public Channel {
 public:
  virtual void SendMessage(
      std::string msg,
      base::Optional<std::vector<std::string>> users = base::nullopt);

 protected:
  virtual ~ShareChannel() = default;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_SHARE_CHANNEL_H_
