#ifndef YEALINK_RTVC_API_CALL_H_
#define YEALINK_RTVC_API_CALL_H_

#include <memory>

#include "yealink/rtvc/api/video/video_source.h"
#include "yealink/rtvc/api/video/video_sink.h"

namespace rtvc {

enum class CallState {
  kNone,
  kAnswered,
  kProgress,
  kConfirmed,
  kEstablished,
  kCanceled,
  kTerminated,
};

class CallObserver {
 public:
  virtual void OnMediaReady() = 0;
  virtual void OnShareReady() = 0;
  virtual void OnFocusReady() = 0;
  virtual void OnChatReady() = 0;

  virtual void OnLocalSharing() = 0;
  virtual void OnRemoteSharing() = 0;

 protected:
  virtual ~CallObserver() = default;
};

class Call {
 public:
  // call direction should be determined at creation time as we don't want it
  // changed for later use, and different direction usually represent different
  // call.
  static std::unique_ptr<Call> Create(CallObserver* observer);

  virtual void Connect() = 0;
  virtual void Disconnect() = 0;

  virtual void Forward() = 0;
  virtual void Refer() = 0;
  virtual void Replace() = 0;

  virtual void Hold() = 0;
  virtual void Unhold() = 0;

  virtual void Mute() = 0;
  virtual void Unmute() = 0;

  // useful when network environment changed
  virtual void Renegotiate() = 0;

  virtual void GetStats() = 0;

  virtual bool isInProgress() = 0;
  virtual bool isEstablished() = 0;
  virtual bool isEnded() = 0;

  virtual bool local_sharing() = 0;
  virtual bool remote_sharing() = 0;

  // start local sharing, remote sharing is always connected
  virtual void StartShare() = 0;
  virtual void StopShare() = 0;

  virtual void SetMediaBitrate(int bitrate) = 0;
  virtual void SetShareBitrate(int bitrate) = 0;

  // set custom video source for local video streaming, device setted in
  // VideoManager is used by default.
  virtual void SetLocalVideoSource(VideoSource* source = nullptr) = 0;
  virtual void SetLocalShareVideoSource(VideoSource* source = nullptr) = 0;

  // TBD
  // should we support multiple VideoSink?
  // aka, change set(videosink) to add & remove(videosink)
  //
  // aside note: local video sink is setted in VideoManager
  virtual void SetRemoteVideoSink(VideoSink* sink = nullptr) = 0;
  virtual void SetRemoteShareVideoSink(VideoSink* sink = nullptr) = 0;

  // when conference media session is connected, conference aware means we
  // should try to connect conference focus session automatically
  virtual bool conference_aware() = 0;
  virtual void SetConferenceAware(bool enable) = 0;

 protected:
  virtual ~Call() = default;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_API_CALL_H_
