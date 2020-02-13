#ifndef YEALINK_RTVC_API_CHANNEL_H_
#define YEALINK_RTVC_API_CHANNEL_H_

#include <memory>
#include <string>

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

enum class StatsAudioCodecType {
  kNone = -1,
  kARES,
  kOPUS,
  kG722,
  kG7221,
  kG72221C,
  kG729,
  kAACLC,
  kPCMU,
  kPCMA
};

enum class StatsVideoCodecType {
  kNone = -1,
  kH263,
  kH264,
  kH264SVC,
};

enum class StatsVideoProfileType {
  kNone = -1,
  kBase,
  kMain,
  kHigh,
  kMax,
};

struct AudioStatsInfo {
  StatsAudioCodecType codec;
  int bitrate;
  int samplerate;
  int loss_rate;
  int total_lost_packets;
  int jitter;
  int delay;
  AudioStatsInfo()
      : codec(StatsAudioCodecType::kNone),
        bitrate(-1),
        samplerate(-1),
        loss_rate(-1),
        total_lost_packets(-1),
        jitter(-1),
        delay(-1) {}
};

struct VideoStatsInfo {
  unsigned int id;
  StatsVideoCodecType codec;
  StatsVideoProfileType profile;
  int width;
  int height;
  int frame_rate;
  int bit_rate;
  int loss_rate;
  int total_loss_packets;
  int jitter;
  int rtt;
  VideoStatsInfo()
      : codec(StatsVideoCodecType::kNone),
        profile(StatsVideoProfileType::kNone),
        width(-1),
        height(-1),
        frame_rate(-1),
        bit_rate(-1),
        loss_rate(-1),
        total_loss_packets(-1),
        jitter(-1),
        rtt(-1) {}
};

struct RTCVideoStats {
  VideoStatsInfo outbound;
  std::vector<VideoStatsInfo> inbound;
};

struct RTCAudioStats {
  AudioStatsInfo outbound;
  AudioStatsInfo inbound;
};

struct RTCStats {
  RTCAudioStats audio;
  RTCVideoStats video;
};

struct RTCStatsInfo {
  RTCStats media;
  RTCStats share;
};

enum class CaptureDeviceFormatType {
  kNone,
  KWebcam,
  kJPEG,
};

struct CaptureInfo {
  std::string id;
  CaptureDeviceFormatType type;
  int width;
  int height;
  int fps;
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

#endif  // YEALINK_RTVC_API_CHANNEL_H_
