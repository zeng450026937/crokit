#ifndef YEALINK_RTVC_LIB_FOCUS_CHANNEL_IMPL_H_
#define YEALINK_RTVC_LIB_FOCUS_CHANNEL_IMPL_H_

#include "yealink/rtvc/api/focus_channel.h"

namespace yealink {

namespace rtvc {

class FocusChannelImpl : public FocusChannel {
 public:
  FocusChannelImpl();
  ~FocusChannelImpl() override;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_LIB_FOCUS_CHANNEL_IMPL_H_
