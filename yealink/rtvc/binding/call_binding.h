#ifndef YEALINK_RTVC_BINDING_CALL_BINDING_H_
#define YEALINK_RTVC_BINDING_CALL_BINDING_H_

#include "yealink/libvc/include/meeting/meeting_api.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/rtvc/api/call.h"
#include "yealink/rtvc/binding/conference_binding.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/binding/user_agent_binding.h"
#include "yealink/rtvc/binding/video_sink_v8.h"
#include "yealink/rtvc/binding/video_source_adapter.h"

namespace yealink {

namespace rtvc {

class CallBinding : public mate::EventEmitter<CallBinding>,
                    public MeetingObserver {
 public:
  static mate::WrappableBase* New(mate::Handle<UserAgentBinding> user_agent,
                                  mate::Arguments* args);

  static mate::Handle<CallBinding> Create(
      v8::Isolate* isolate,
      mate::Handle<UserAgentBinding> user_agent,
      bool incoming = true);

  static mate::Handle<CallBinding> Create(
      v8::Isolate* isolate,
      UserAgentBinding* user_agent,
      bool incoming = true);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  yealink::Meeting* GetMeeting() { return meeting_.get(); };

 protected:
  CallBinding(v8::Isolate* isolate,
              v8::Local<v8::Object> wrapper,
              mate::Handle<UserAgentBinding> user_agent,
              bool incoming = false);
  CallBinding(v8::Isolate* isolate,
              mate::Handle<UserAgentBinding> user_agent,
              bool incoming = true);
  CallBinding(v8::Isolate* isolate,
              UserAgentBinding* user_agent,
              bool incoming = true);
  ~CallBinding() override;

  v8::Local<v8::Object> local_identity();
  v8::Local<v8::Object> remote_identity();

  void Connect(std::string target, mate::Arguments* args);
  void Answer(mate::Arguments* args);
  void Hangup(mate::Arguments* args);

  void Forward(std::string target);
  v8::Local<v8::Promise> Refer(std::string target);
  v8::Local<v8::Promise> Replace(mate::Handle<CallBinding> call);

  v8::Local<v8::Promise> Upgrade(mate::Arguments* args);

  void Hold();
  void Unhold();

  void Mute();
  void Unmute();

  void Renegotiate();

  void GetStats();
  v8::Local<v8::Object> GetInfos();

  void InsertDTMF(std::string tone);
  void SendDTMF(std::string tone);

  bool isInProgress();
  bool isEstablished();
  bool isEnded();
  bool isRefering();
  bool isReplacing();
  bool isUpgrading();
  bool isReadyForShare();
  bool isShareChannelSupported();
  bool isShareChannelEstablished();

  bool local_sharing();
  bool remote_sharing();

  bool incoming() { return incoming_; }
  bool outgoing() { return !incoming_; }

  bool portrait_mode();
  void SetPortraitMode(bool enable);

  void StartShare(mate::Dictionary dict, mate::Arguments* args);
  void StopShare();

  void SetMediaBitrate(int64_t send_bitrate, int64_t recv_bitrate);
  void SetShareBitrate(int64_t send_bitrate, int64_t recv_bitrate);

  void SetLocalVideoSource(mate::PersistentDictionary source);
  void SetLocalShareVideoSource(mate::PersistentDictionary source);

  void SetRemoteVideoSink(mate::Arguments* args);
  void AddRemoteVideoSink(mate::PersistentDictionary sink);
  void RemoveRemoteVideoSink(mate::PersistentDictionary sink);

  void SetRemoteShareVideoSink(mate::Arguments* args);
  void AddRemoteShareVideoSink(mate::PersistentDictionary sink);
  void RemoveRemoteShareVideoSink(mate::PersistentDictionary sink);

  bool conference_aware();
  void SetConferenceAware(bool enable);

  v8::Local<v8::Value> AsConference();

  // event
  void OnEstablished();

  // meeting observer impl
  void OnEvent(yealink::MeetingEventId id) override;
  void OnMediaEvent(yealink::MeetingMediaEventId id) override;
  void OnCallInfoChanged(const yealink::MeetingInfo& info) override;
  void OnCreateConferenceAfter(yealink::RoomController* controller) override;
  void OnRealseConferenceBefore(yealink::RoomController* controller) override;
  void OnVideoFrame(const yealink::VideoFrame& frame) override;
  void OnShareFrame(const yealink::VideoFrame& frame) override;

 private:
  yealink::AVContentType GetContentType();
  void ExtractInfo(yealink::MeetingInfo info);

  base::WeakPtr<UserAgentBinding> user_agent_;
  base::WeakPtr<yealink::SIPClient> sip_client_;
  base::WeakPtrFactory<CallBinding> weak_factory_;

  yealink::Media* media_;

  struct MeetingDeleter {
    void operator()(yealink::Meeting* c) { yealink::ReleaseMeeting(c); }
  };
  std::unique_ptr<yealink::Meeting, MeetingDeleter> meeting_;
  yealink::RoomController* controller_;

  yealink::MeetingInfo meeting_info_;

  mate::PersistentDictionary local_identity_;
  mate::PersistentDictionary remote_identity_;
  mate::PersistentDictionary call_info_;

  CallState state_ = CallState::kNone;
  bool local_sharing_ = false;
  bool remote_sharing_ = false;
  bool portrait_mode_ = false;
  bool incoming_ = false;
  bool ready_for_share_ = false;

  std::unique_ptr<Promise> refer_promise_;
  std::unique_ptr<Promise> replace_promise_;
  std::unique_ptr<Promise> upgrade_promise_;

  std::unique_ptr<VideoSourceAdapter> remote_video_source_;
  std::unique_ptr<VideoSourceAdapter> remote_share_video_source_;

  std::map<int, VideoSinkV8*> remote_video_sinks_;
  std::map<int, VideoSinkV8*> remote_share_video_sinks_;

  v8::Global<v8::Value> v8_conference_;
  mate::Handle<ConferenceBinding> conference_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CALL_BINDING_H_
