#ifndef YEALINK_RTVC_LIB_CALL_IMPL_H_
#define YEALINK_RTVC_LIB_CALL_IMPL_H_

#include "base/memory/weak_ptr.h"
#include "base/memory/scoped_refptr.h"

#include "yealink/rtvc/api/call.h"
#include "yealink/rtvc/api/channel.h"
#include "yealink/rtvc/lib/user_agent_impl.h"

namespace rtvc {

class CallImpl : public Call {
 public:
  CallImpl();
  ~CallImpl() override;

  void Connect() override;
  void Disconnect() override;

  void Forward() override;
  void Refer() override;
  void Replace() override;

  void Hold() override;
  void Unhold() override;

  void Mute() override;
  void Unmute() override;

  // useful when network environment changed
  void Renegotiate() override;

  bool isInProgress() override;
  bool isEstablished() override;
  bool isEnded() override;

  bool local_sharing() override;
  bool remote_sharing() override;

  // start local sharing, remote sharing is always connected
  void StartShare() override;
  void StopShare() override;

  void SetMediaBitrate(int bitrate) override;
  void SetShareBitrate(int bitrate) override;

  // set custom video source for local video streaming, device setted in
  // VideoManager is used by default.
  void SetLocalVideoSource(VideoSource* source = nullptr) override;
  void SetLocalShareVideoSource(VideoSource* source = nullptr) override;

  // TBD
  // should we support multiple VideoSink?
  // aka, change set(videosink) to add & remove(videosink)
  //
  // aside note: local video sink is setted in VideoManager
  void SetRemoteVideoSink(VideoSink* sink = nullptr) override;
  void SetRemoteShareVideoSink(VideoSink* sink = nullptr) override;

  // when conference media session is connected, conference aware means we
  // should try to connect conference focus session automatically
  bool conference_aware() override;
  void SetConferenceAware(bool enable) override;

 private:
  base::WeakPtr<UserAgentImpl> user_agent_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_LIB_CALL_IMPL_H_
