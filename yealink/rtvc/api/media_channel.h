#ifndef YEALINK_RTVC_API_MEDIA_CHANNEL_H_
#define YEALINK_RTVC_API_MEDIA_CHANNEL_H_

#include "yealink/rtvc/api/channel.h"

namespace rtvc {

class MediaChannelObserver : public ChannelObserver {
 public:
  // media state
  virtual void OnRtcNegotiateFailed() = 0;
  virtual void OnRtcConnectFailed() = 0;
  virtual void onRtcConnected() = 0;

 protected:
  virtual ~MediaChannelObserver() = default;
};

class MediaChannel : public Channel {
 public:
  static std::unique_ptr<MediaChannel> Create(MediaChannelObserver* observer);

  virtual bool isReadyForReOffer() = 0;

  virtual void Hold() = 0;
  virtual void Unhold() = 0;

  virtual void Mute() = 0;
  virtual void Unmute() = 0;

 protected:
  virtual ~MediaChannel() = default;
};
}  // namespace rtvc

#endif  // YEALINK_RTVC_API_MEDIA_CHANNEL_H_
