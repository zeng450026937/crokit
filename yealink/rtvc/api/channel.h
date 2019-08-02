#ifndef YEALINK_RTVC_API_CHANNEL_H_
#define YEALINK_RTVC_API_CHANNEL_H_

#include <memory>
#include <string>

namespace yealink {

namespace rtvc {

enum class ChannelState {
  kConnecting,
  kConnected,
  kFailed,
  kFinished,
};

enum class ChannelDirection {
  kNone,
  kIncoming,
  kOutgoing,
};

enum class ChannelType {
  kNormal,
  kMedia,
  kFocus,
  kShare,
  kChat,
};

class ChannelObserver {
 public:
  // singaling state
  virtual void OnConnecting() = 0;
  virtual void OnConnected() = 0;
  virtual void OnFailed() = 0;
  virtual void OnEnded() = 0;
  // p2p
  virtual void OnRinging() = 0;
  virtual void OnForward() = 0;
  virtual void OnRefer() = 0;
  virtual void OnReplace() = 0;
  virtual void OnHold() = 0;
  virtual void OnNewInfo() = 0;
  virtual void OnNewDTMF() = 0;

 protected:
  virtual ~ChannelObserver() = default;
};

class Channel {
 public:
  static std::unique_ptr<Channel> Create(ChannelObserver* observer);

  virtual ChannelType type() = 0;
  virtual ChannelState state() = 0;
  virtual ChannelDirection direction() = 0;
  virtual std::string local_identity() = 0;
  virtual std::string remote_identity() = 0;

  virtual bool isInProgress() = 0;
  virtual bool isEstablished() = 0;
  virtual bool isEnded() = 0;

  virtual void Offer() = 0;
  virtual void Answer() = 0;

  virtual void Refer() = 0;

  virtual void SendDTMF() = 0;
  virtual void SendInfo() = 0;

  virtual void Renegotiate() = 0;

 protected:
  virtual ~Channel() = default;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_CHANNEL_H_
