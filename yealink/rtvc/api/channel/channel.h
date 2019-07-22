#ifndef API_CHANNEL_H_
#define API_CHANNEL_H_

#include <string>
#include <vector>

namespace yealink {

enum class SignalingState {
  kStable,
  kHaveLocalOffer,
  kHaveLocalPrAnswer,
  kHaveRemoteOffer,
  kHaveRemotePrAnswer,
  kClosed,
};

enum class IceGatheringState {
  kNew,
  kGathering,
  kComplete,
};

enum class IceConnectionState {
  kNew,
  kConnectin,
  kConnected,
  kDisconnected,
  kFailed,
  kClosed,
};

enum class RTCSessionState {
  kNew,
  kConnectin,
  kConnected,
  kDisconnected,
  kFailed,
  kClosed,
};

struct RTCCodec {
  std::string payloadType;
  std::string codec;
  int clockRate;
  std::string parameters;
};

struct RTCTransportStats {
  int bytesSent;
  int bytesReceived;
  int packetSent;
  int packetLost;
  int packetLostRate;
  int bitrate;
  int jitter;
  int rtt;
};

struct RTCStreamStats : public RTCTransportStats {
  bool isRemote;
  std::string ssrc;
  RTCCodec codec;
};

struct RTCAudioStreamStats : public RTCStreamStats {
  int sampelrate;
  int channel;
  int delay;
};
struct RTCVideoStreamStats : public RTCStreamStats {
  int width;
  int height;
  int frameRate;
};

struct RTCMediaStats {
  RTCAudioStreamStats audio;
  RTCVideoStreamStats video;
};

struct RTCStats {
  RTCMediaStats inbound;
  RTCMediaStats outbound;
};

class RTCSession {
 public:
  class Observer {
   public:
    virtual void OnClose() = 0;
  };

  virtual void CreateOffer() = 0;
  virtual void CreateAnswer() = 0;

  virtual void Close() = 0;

  virtual bool ice() = 0;
  virtual void SetICE(bool enable) = 0;

  virtual bool dtls() = 0;
  virtual void SetDTLS(bool enable) = 0;

  virtual std::string local_description() = 0;
  virtual std::string remote_descrition() = 0;

  virtual void SetLocalDescription(std::string desc) = 0;
  virtual void SetRemoteDescription(std::string desc) = 0;

  virtual void SetLocalVideoSink() = 0;
  virtual void SetRemoteVideoSink() = 0;

  virtual void InsertDTMF(std::string tones,
                          int duration = 100,
                          int inter_tone_gap = 100) = 0;

  virtual void GetStats() = 0;

  virtual void SetBitrate(int bitrate) = 0;

 protected:
  virtual ~RTCSession() {}
};

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

class Channel {
 public:
  class Observer {
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
    // media state
    virtual void OnRtcNegotiateFailed() = 0;
    virtual void OnRtcConnectFailed() = 0;
    virtual void onRtcConnected() = 0;
    // chat
    virtual void OnChatMessage() = 0;
  };

 public:
  virtual ChannelState state() = 0;
  virtual ChannelDirection direction() = 0;
  virtual std::string local_identity() = 0;
  virtual std::string remote_identity() = 0;
  // custom data
  // TBD
  virtual void data() = 0;
  virtual void SetData() = 0;

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
  virtual ~Channel() {}
};

class MediaChannel : public Channel {
 public:
  virtual bool isReadyForReOffer() = 0;

  virtual void Hold() = 0;
  virtual void Unhold() = 0;

  virtual void Mute() = 0;
  virtual void Unmute() = 0;

 protected:
  virtual ~MediaChannel() {}
};

class ChatChannel : public Channel {
 public:
  virtual void sendMessage(std::string msg, std::vector<std::string> users);

 protected:
  virtual ~ChatChannel() {}
};

}  // namespace yealink

#endif  // API_CHANNEL_H_