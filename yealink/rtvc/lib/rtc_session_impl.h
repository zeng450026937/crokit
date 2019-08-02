#ifndef YEALINK_RTVC_LIB_RTC_SESSION_IMPL_H_
#define YEALINK_RTVC_LIB_RTC_SESSION_IMPL_H_

#include "yealink/rtvc/api/rtc_session.h"

namespace yealink {

namespace rtvc {

class RTCSessionImpl : public RTCSession {
 public:
  RTCSessionImpl();
  ~RTCSessionImpl() override;

  void CreateOffer() override;
  void CreateAnswer() override;

  void Close() override;

  bool ice() override;
  void SetICE(bool enable) override;

  bool dtls() override;
  void SetDTLS(bool enable) override;

  std::string local_description() override;
  std::string remote_descrition() override;

  void SetLocalDescription(std::string desc) override;
  void SetRemoteDescription(std::string desc) override;

  void SetLocalVideoSink() override;
  void SetRemoteVideoSink() override;

  void InsertDTMF(std::string tones,
                  int duration = 100,
                  int inter_tone_gap = 100) override;

  void GetStats() override;

  void SetBitrate(int bitrate) override;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_LIB_RTC_SESSION_IMPL_H_
