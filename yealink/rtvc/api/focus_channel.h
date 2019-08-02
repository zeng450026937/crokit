#ifndef YEALINK_RTVC_API_FOCUS_CHANNEL_H_
#define YEALINK_RTVC_API_FOCUS_CHANNEL_H_

#include "yealink/rtvc/api/channel.h"

namespace yealink {

namespace rtvc {

class FocusChannelObserver : public ChannelObserver {
 protected:
  virtual ~FocusChannelObserver() = default;
};

class FocusChannel : public Channel {
 public:
  static std::unique_ptr<FocusChannel> Create(FocusChannelObserver* observer);

 protected:
  virtual ~FocusChannel() = default;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_FOCUS_CHANNEL_H_
