#ifndef YEALINK_RTVC_API_RTC_SESSION_H_
#define YEALINK_RTVC_API_RTC_SESSION_H_

#include <memory>
#include <string>

namespace yealink {

namespace rtvc {

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

class RTCSessionObserver {
 public:
  virtual void OnClose() = 0;

 protected:
  virtual ~RTCSessionObserver() = default;
};

class RTCSession {
 public:
  static std::unique_ptr<RTCSession> Create(RTCSessionObserver* observer);

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

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_RTC_SESSION_H_
