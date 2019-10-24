#ifndef YEALINK_RTVC_LIB_MEDIA_CHANNEL_IMPL_H_
#define YEALINK_RTVC_LIB_MEDIA_CHANNEL_IMPL_H_

#include "yealink/rtvc/api/media_channel.h"

namespace rtvc {

class MediaChannelImpl : public MediaChannel {
 public:
  MediaChannelImpl();
  ~MediaChannelImpl() override;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_LIB_MEDIA_CHANNEL_IMPL_H_
