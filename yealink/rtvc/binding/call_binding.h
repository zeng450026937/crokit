#ifndef YEALINK_RTVC_BINDING_CALL_BINDING_H_
#define YEALINK_RTVC_BINDING_CALL_BINDING_H_

#include "yealink/libvc/include/meeting/meeting_api.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/user_agent_binding.h"

namespace yealink {

namespace rtvc {

class CallBinding : public mate::EventEmitter<CallBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  CallBinding(v8::Isolate* isolate,
              v8::Local<v8::Object> wrapper,
              mate::Handle<UserAgentBinding> user_agent);
  CallBinding(v8::Isolate* isolate,
              v8::Local<v8::Object> wrapper,
              base::WeakPtr<UserAgentBinding> user_agent);
  ~CallBinding() override;

  void Connect(mate::Arguments* args);
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

  void SetUserAgent(mate::Handle<UserAgentBinding> user_agent);

 private:
  base::WeakPtr<UserAgentBinding> user_agent_;
  base::WeakPtr<yealink::SIPClient> sip_client_;

  yealink::Media* media_;

  struct MeetingDeleter {
    void operator()(yealink::Meeting* c) { yealink::ReleaseMeeting(c); }
  };
  std::unique_ptr<yealink::Meeting, MeetingDeleter> meeting_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CALL_BINDING_H_
