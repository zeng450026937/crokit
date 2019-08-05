#ifndef YEALINK_RTVC_BINDING_CALL_BINDING_H_
#define YEALINK_RTVC_BINDING_CALL_BINDING_H_

#include "yealink/rtvc/api/call.h"
#include "yealink/rtvc/binding/event_emitter.h"

namespace yealink {

namespace rtvc {

class CallBinding : public mate::EventEmitter<CallBinding>, Call, CallObserver {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  CallBinding(v8::Isolate* isolate);
  ~CallBinding() override;

  void Connect() override;
  void Disconnect() override;

  void Forward() override;
  void Refer() override;
  void Replace() override;

  void Hold() override;
  void Unhold() override;

  void Mute() override;
  void Unmute() override;

  void Renegotiate() override;

  bool isInProgress() override;
  bool isEstablished() override;
  bool isEnded() override;

  bool local_sharing() override;
  bool remote_sharing() override;

  void StartShare() override;
  void StopShare() override;

  void SetMediaBitrate(int bitrate) override;
  void SetShareBitrate(int bitrate) override;

  void SetLocalVideoSource(VideoSource* source = nullptr) override;
  void SetLocalShareVideoSource(VideoSource* source = nullptr) override;

  void SetRemoteVideoSink(VideoSink* sink = nullptr) override;
  void SetRemoteShareVideoSink(VideoSink* sink = nullptr) override;

  bool conference_aware() override;
  void SetConferenceAware(bool enable) override;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CALL_BINDING_H_
