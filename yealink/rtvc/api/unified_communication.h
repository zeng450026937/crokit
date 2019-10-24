#ifndef YEALINK_RTVC_API_UNIFIED_COMMUNICATION_H_
#define YEALINK_RTVC_API_UNIFIED_COMMUNICATION_H_

#include "yealink/rtvc/api/channel.h"

namespace rtvc {

class Call;
class Conference;

class UnifiedCommunication {
 public:
  virtual bool isChannelReady(ChannelType type) = 0;
  virtual bool isChannelSupported(ChannelType type) = 0;

  virtual bool channel_aware() = 0;
  virtual void SetChannelAware(bool enable) = 0;

  virtual const Call* AsCall() = 0;
  virtual const Conference* AsConference() = 0;

 protected:
  friend class Call;
  friend class Conference;

  virtual ~UnifiedCommunication() = default;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_API_UNIFIED_COMMUNICATION_H_
