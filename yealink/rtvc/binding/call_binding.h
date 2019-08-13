#ifndef YEALINK_RTVC_BINDING_CALL_BINDING_H_
#define YEALINK_RTVC_BINDING_CALL_BINDING_H_

#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/native_mate/persistent_dictionary.h"

namespace yealink {

namespace rtvc {

class VideoSource;
class VideoSink;

class CallBinding : public mate::EventEmitter<CallBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  CallBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~CallBinding() override;

  void Connect();
  void Disconnect();

  void Forward();
  void Refer();
  void Replace();

  void Hold();
  void Unhold();

  void Mute();
  void Unmute();

  void Renegotiate();

  bool isInProgress();
  bool isEstablished();
  bool isEnded();

  bool local_sharing();
  bool remote_sharing();

  void StartShare();
  void StopShare();

  void SetMediaBitrate(int bitrate);
  void SetShareBitrate(int bitrate);

  void SetLocalVideoSource(mate::PersistentDictionary source);
  void SetLocalShareVideoSource(mate::PersistentDictionary source);

  void SetRemoteVideoSink(mate::PersistentDictionary sink);
  void SetRemoteShareVideoSink(mate::PersistentDictionary sink);

  bool conference_aware();
  void SetConferenceAware(bool enable);

  void AsConference();
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CALL_BINDING_H_
