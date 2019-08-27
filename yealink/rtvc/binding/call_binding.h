#ifndef YEALINK_RTVC_BINDING_CALL_BINDING_H_
#define YEALINK_RTVC_BINDING_CALL_BINDING_H_

#include "yealink/libvc/include/meeting/meeting_api.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/rtvc/api/call.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/user_agent_binding.h"

namespace yealink {

namespace rtvc {

class CallBinding : public mate::EventEmitter<CallBinding>,
                    public MeetingObserver {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<CallBinding> Create(
      v8::Isolate* isolate,
      base::WeakPtr<UserAgentBinding> user_agent,
      bool incoming = true);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  CallBinding(v8::Isolate* isolate,
              v8::Local<v8::Object> wrapper,
              mate::Handle<UserAgentBinding> user_agent,
              bool incoming);
  CallBinding(v8::Isolate* isolate,
              v8::Local<v8::Object> wrapper,
              base::WeakPtr<UserAgentBinding> user_agent,
              bool incoming);

  CallBinding(v8::Isolate* isolate,
              base::WeakPtr<UserAgentBinding> user_agent,
              bool incoming);
  ~CallBinding() override;

  void Connect(std::string target, mate::Arguments* args);
  void Answer(mate::Arguments* args);
  void Hangup(mate::Arguments* args);

  void Forward(std::string target);
  void Refer(std::string target);
  void Replace(mate::Handle<CallBinding> call);

  void Hold();
  void Unhold();

  void Mute();
  void Unmute();

  void Renegotiate();

  void GetStats();

  void InsertDTMF(std::string tone);
  void SendDTMF(std::string tone);

  bool isInProgress();
  bool isEstablished();
  bool isEnded();

  bool local_sharing();
  bool remote_sharing();

  void StartShare();
  void StopShare();

  void SetMediaBitrate(int64_t send_bitrate, int64_t recv_bitrate);
  void SetShareBitrate(int64_t send_bitrate, int64_t recv_bitrate);

  void SetLocalVideoSource(mate::PersistentDictionary source);
  void SetLocalShareVideoSource(mate::PersistentDictionary source);

  void SetRemoteVideoSink(mate::PersistentDictionary sink);
  void SetRemoteShareVideoSink(mate::PersistentDictionary sink);

  bool conference_aware();
  void SetConferenceAware(bool enable);

  void AsConference();

  void SetUserAgent(mate::Handle<UserAgentBinding> user_agent);

  // meeting observer impl
  void OnEvent(yealink::MeetingEventId id) override;
  void OnMediaEvent(yealink::MeetingMediaEventId id) override;
  void OnCallInfoChanged(const yealink::MeetingInfo& infoNew) override;
  void OnCreateConferenceAfter(yealink::RoomController* pObject) override;
  void OnRealseConferenceBefore(yealink::RoomController* pObject) override;
  void OnVideoFrame(const yealink::VideoFrame& frame) override;
  void OnShareFrame(const yealink::VideoFrame& frame) override;

 private:
  bool incoming() { return incoming_; }
  bool outgoing() { return !incoming_; }

  base::WeakPtr<UserAgentBinding> user_agent_;
  base::WeakPtr<yealink::SIPClient> sip_client_;

  yealink::Media* media_;

  struct MeetingDeleter {
    void operator()(yealink::Meeting* c) { yealink::ReleaseMeeting(c); }
  };
  std::unique_ptr<yealink::Meeting, MeetingDeleter> meeting_;

  CallState state_ = CallState::kNone;
  bool local_sharing_ = false;
  bool remote_sharing_ = false;
  bool incoming_ = false;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CALL_BINDING_H_
