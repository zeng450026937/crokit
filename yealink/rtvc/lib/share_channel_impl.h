#ifndef YEALINK_RTVC_LIB_SHARE_CHANNEL_IMPL_H_
#define YEALINK_RTVC_LIB_SHARE_CHANNEL_IMPL_H_

#include "yealink/rtvc/api/share_channel.h"

namespace yealink {

namespace rtvc {

class ShareChannelImpl : public ShareChannel {
 public:
  ShareChannelImpl();
  ~ShareChannelImpl() override;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_LIB_SHARE_CHANNEL_IMPL_H_
