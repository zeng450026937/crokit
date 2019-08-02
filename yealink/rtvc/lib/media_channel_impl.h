#ifndef YEALINK_RTVC_LIB_MEDIA_CHANNEL_IMPL_H_
#define YEALINK_RTVC_LIB_MEDIA_CHANNEL_IMPL_H_

#include "yealink/rtvc/api/media_channel.h"

namespace yealink {

namespace rtvc {

class MediaChannelImpl : public MediaChannel {
 public:
  MediaChannelImpl();
  ~MediaChannelImpl() override;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_LIB_MEDIA_CHANNEL_IMPL_H_
