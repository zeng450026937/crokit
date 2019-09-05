#include "yealink/rtvc/binding/call_binding.h"

#include "base/logging.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/context.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* CallBinding::New(mate::Arguments* args) {
  mate::Handle<UserAgentBinding> user_agent;

  if (args->Length() < 1 || !args->GetNext(&user_agent) ||
      user_agent.IsEmpty()) {
    args->ThrowError("UserAgent is required to construct Call");
    return nullptr;
  }

  return new CallBinding(args->isolate(), args->GetThis(), user_agent, false);
}

// static
mate::Handle<CallBinding> CallBinding::Create(
    v8::Isolate* isolate,
    base::WeakPtr<UserAgentBinding> user_agent,
    bool incoming) {
  return mate::CreateHandle(isolate,
                            new CallBinding(isolate, user_agent, incoming));
}

// static
void CallBinding::BuildPrototype(v8::Isolate* isolate,
                                 v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "Call"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetMethod("connect", &CallBinding::Connect)
      .SetMethod("answer", &CallBinding::Answer)
      .SetMethod("hangup", &CallBinding::Hangup)
      .SetMethod("forward", &CallBinding::Forward)
      .SetMethod("refer", &CallBinding::Refer)
      .SetMethod("replace", &CallBinding::Replace)
      .SetMethod("upgrade", &CallBinding::Upgrade)
      .SetMethod("hold", &CallBinding::Hold)
      .SetMethod("unhold", &CallBinding::Unhold)
      .SetMethod("mute", &CallBinding::Mute)
      .SetMethod("unmute", &CallBinding::Unmute)
      .SetMethod("renegotiate", &CallBinding::Renegotiate)
      .SetProperty("isInProgress", &CallBinding::isInProgress)
      .SetProperty("isEstablished", &CallBinding::isEstablished)
      .SetProperty("isEnded", &CallBinding::isEnded)
      .SetProperty("localSharing", &CallBinding::local_sharing)
      .SetProperty("remoteSharing", &CallBinding::remote_sharing)
      .SetMethod("startShare", &CallBinding::StartShare)
      .SetMethod("stopShare", &CallBinding::StopShare)
      .SetMethod("setMediaBitrate", &CallBinding::SetMediaBitrate)
      .SetMethod("setShareBitrate", &CallBinding::SetShareBitrate)
      .SetMethod("setLocalVideoSource", &CallBinding::SetLocalVideoSource)
      .SetMethod("setLocalShareVideoSource",
                 &CallBinding::SetLocalShareVideoSource)
      .SetMethod("setRemoteVideoSink", &CallBinding::SetRemoteVideoSink)
      .SetMethod("setRemoteShareVideoSink",
                 &CallBinding::SetRemoteShareVideoSink)
      .SetProperty("conferenceAware", &CallBinding::conference_aware,
                   &CallBinding::SetConferenceAware)
      .SetMethod("asConference", &CallBinding::AsConference)
      .SetProperty("conference", &CallBinding::AsConference);
}

CallBinding::CallBinding(v8::Isolate* isolate,
                         v8::Local<v8::Object> wrapper,
                         mate::Handle<UserAgentBinding> user_agent,
                         bool incoming)
    : CallBinding(isolate, wrapper, user_agent->GetWeakPtr(), incoming) {}
CallBinding::CallBinding(v8::Isolate* isolate,
                         v8::Local<v8::Object> wrapper,
                         base::WeakPtr<UserAgentBinding> user_agent,
                         bool incoming)
    : user_agent_(user_agent),
      sip_client_(user_agent->GetWeakSIPClientPtr()),
      media_(Context::Instance()->GetMedia()),
      meeting_(yealink::CreateMeeting(*sip_client_, *media_, incoming)),
      controller_(nullptr),
      incoming_(incoming),
      remote_video_source_(new VideoSourceAdapter()),
      remote_share_video_source_(new VideoSourceAdapter()) {
  InitWith(isolate, wrapper);
  meeting_->SetObserver(this);
  controller_ = meeting_->Room();
  conference_ = ConferenceBinding::Create(isolate, nullptr);
  v8_conference_.Reset(isolate, conference_.ToV8());
}

CallBinding::CallBinding(v8::Isolate* isolate,
                         base::WeakPtr<UserAgentBinding> user_agent,
                         bool incoming)
    : user_agent_(user_agent),
      sip_client_(user_agent->GetWeakSIPClientPtr()),
      media_(Context::Instance()->GetMedia()),
      meeting_(yealink::CreateMeeting(*sip_client_, *media_, incoming)),
      controller_(nullptr),
      incoming_(incoming),
      remote_video_source_(new VideoSourceAdapter()),
      remote_share_video_source_(new VideoSourceAdapter()) {
  Init(isolate);
  meeting_->SetObserver(this);
  controller_ = meeting_->Room();
  conference_ = ConferenceBinding::Create(isolate, nullptr);
  v8_conference_.Reset(isolate, conference_.ToV8());
}
CallBinding::~CallBinding() {
  meeting_->SetObserver(nullptr);
}

void CallBinding::Connect(std::string target, mate::Arguments* args) {
  yealink::DailParam param;
  param.strUri = target.c_str();
  param.typAVContent = yealink::AV_VIDEO_AUDIO;

  meeting_->Dail(param);

  state_ = CallState::kProgress;
}
void CallBinding::Answer(mate::Arguments* args) {
  state_ = CallState::kAnswered;
  meeting_->Early("");
  meeting_->Answer(yealink::AV_VIDEO_AUDIO);

  state_ = CallState::kProgress;
}

void CallBinding::Hangup(mate::Arguments* args) {
  std::string reason;
  args->GetNext(&reason);
  yealink::SIPCode code = yealink::SIPCode::SIP_BUSY_HERE;
  meeting_->Hangup(code, reason.c_str());

  if (outgoing() && isInProgress()) {
    state_ = CallState::kCanceled;
  } else {
    state_ = CallState::kTerminated;
  }
}

void CallBinding::Forward(std::string target) {
  meeting_->Forward(target.c_str());
}
void CallBinding::Refer(std::string target) {
  meeting_->TransferToUri(target.c_str());
}
void CallBinding::Replace(mate::Handle<CallBinding> call) {
  meeting_->TransferToCall(meeting_.get());
}

void CallBinding::Upgrade() {
  meeting_->CreateAplloConference(yealink::AV_VIDEO_AUDIO);
}

void CallBinding::Hold() {
  meeting_->SetHold(true);
}
void CallBinding::Unhold() {
  meeting_->SetHold(false);
}

void CallBinding::Mute() {
  media_->Mute(true);
}
void CallBinding::Unmute() {
  media_->Mute(false);
}

void CallBinding::Renegotiate() {}

void CallBinding::GetStats() {
  yealink::MediaStreamStats media_stats = meeting_->AVMediaStats();
  yealink::VideoStreamStats share_stats = meeting_->ShareMediaStats();
}

void CallBinding::InsertDTMF(std::string tone) {
  for (char t : tone) {
    meeting_->SendDTMF(t);
  }
}
void CallBinding::SendDTMF(std::string tone) {
  // currently, we don't send dtmf with sip request
  return InsertDTMF(tone);
}

bool CallBinding::isInProgress() {
  return state_ == CallState::kProgress;
}
bool CallBinding::isEstablished() {
  return state_ == CallState::kEstablished;
}
bool CallBinding::isEnded() {
  return state_ == CallState::kTerminated || state_ == CallState::kCanceled;
}

bool CallBinding::local_sharing() {
  return local_sharing_;
}
bool CallBinding::remote_sharing() {
  return remote_sharing_;
}

void CallBinding::StartShare() {
  yealink::ShareWindow share_window;
  meeting_->StartSendShare(share_window);
  local_sharing_ = true;
}
void CallBinding::StopShare() {
  meeting_->StopSendShare();
  local_sharing_ = false;
}

void CallBinding::SetMediaBitrate(int64_t send_bitrate, int64_t recv_bitrate) {
  meeting_->SetCallBitRate(send_bitrate, recv_bitrate);
}
void CallBinding::SetShareBitrate(int64_t send_bitrate, int64_t recv_bitrate) {
  meeting_->SetShareBitRate(send_bitrate, recv_bitrate);
}

void CallBinding::SetLocalVideoSource(mate::PersistentDictionary source) {}
void CallBinding::SetLocalShareVideoSource(mate::PersistentDictionary source) {}

void CallBinding::SetRemoteVideoSink(mate::PersistentDictionary sink) {
  if (sink.GetHandle()->IsNullOrUndefined()) {
    for (auto it : remote_video_sinks_) {
      remote_video_source_->RemoveSink(it.second);
      delete it.second;
    }
    remote_video_sinks_.clear();
    return;
  }

  int hash = sink.GetHandle()->GetIdentityHash();
  VideoSinkV8* sink_v8 = new VideoSinkV8(sink);
  remote_video_source_->AddOrUpdateSink(sink_v8);
  remote_video_sinks_.emplace(hash, sink_v8);
}
void CallBinding::SetRemoteShareVideoSink(mate::PersistentDictionary sink) {
  if (sink.GetHandle()->IsNullOrUndefined()) {
    for (auto it : remote_share_video_sinks_) {
      remote_share_video_source_->RemoveSink(it.second);
      delete it.second;
    }
    remote_share_video_sinks_.clear();
    return;
  }

  int hash = sink.GetHandle()->GetIdentityHash();
  VideoSinkV8* sink_v8 = new VideoSinkV8(sink);
  remote_share_video_source_->AddOrUpdateSink(sink_v8);
  remote_share_video_sinks_.emplace(hash, sink_v8);
}

bool CallBinding::conference_aware() {
  return true;
}
void CallBinding::SetConferenceAware(bool enable) {}

v8::Local<v8::Value> CallBinding::AsConference() {
  DCHECK(conference_.get());
  return v8::Local<v8::Value>::New(isolate(), v8_conference_);
}

void CallBinding::SetUserAgent(mate::Handle<UserAgentBinding> user_agent) {
  user_agent_ = user_agent->GetWeakPtr();
}

void CallBinding::OnEstablished() {
  LOG(INFO) << __FUNCTIONW__;

  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    context->PostTask(FROM_HERE, base::BindOnce(&CallBinding::OnEstablished,
                                                base::Unretained(this)));
    return;
  }

  state_ = CallState::kEstablished;
  Emit("established");
}

void CallBinding::OnEvent(yealink::MeetingEventId id) {
  switch (id) {
    case yealink::MEETING_CREATE:
      break;
    case yealink::MEETING_CONNECTED:
      state_ = CallState::kEstablished;
      break;
    case yealink::MEETING_RING:
      break;
    case yealink::MEETING_REDIRECT:
      break;
    case yealink::MEETING_ESTABLISHED:
      state_ = CallState::kEstablished;
      break;
    case yealink::MEETING_SHARE_ESTABLISHED:
      break;
    case yealink::MEETING_SHARE_FINISHED:
      break;
    case yealink::MEETING_REFER_FAILED:
      break;
    case yealink::MEETING_REFER_DONE:
      break;
    case yealink::MEETING_REPLACED:
      break;
    case yealink::MEETING_FINISHED:
      state_ = CallState::kTerminated;
      break;
    default:
      NOTREACHED();
      break;
  }
}
void CallBinding::OnMediaEvent(yealink::MeetingMediaEventId id) {
  switch (id) {
    case yealink::MEETING_MEDIA_AUDIO_START:
      break;
    case yealink::MEETING_MEDIA_AUDIO_STOPED:
      break;
    case yealink::MEETING_MEDIA_AUDIO_BROKEN:
      break;
    case yealink::MEETING_MEDIA_VIDEO_START:
      break;
    case yealink::MEETING_MEDIA_VIDEO_STOPED:
      break;
    case yealink::MEETING_MEDIA_VIDEO_BROKEN:
      break;
    case yealink::MEETING_MEDIA_SHARE_RECV_START:
      remote_sharing_ = true;
      break;
    case yealink::MEETING_MEDIA_SHARE_RECV_STOPED:
      remote_sharing_ = false;
      break;
    case yealink::MEETING_MEDIA_SHARE_SEND_START:
      local_sharing_ = true;
      break;
    case yealink::MEETING_MEDIA_SHARE_SEND_STOPED:
      local_sharing_ = false;
      break;
    case yealink::MEETING_MEDIA_SHARE_BROKEN:
      local_sharing_ = false;
      remote_sharing_ = false;
      break;
    case yealink::MEETING_MEDIA_HOLD_CHANGED:
      break;
    default:
      NOTREACHED();
      break;
  }
}
void CallBinding::OnCallInfoChanged(const yealink::MeetingInfo& info) {
  meeting_info_ = info;
}
void CallBinding::OnCreateConferenceAfter(yealink::RoomController* controller) {
  // TODO
  // ensure conference is not nullptr

  // TBD
  // maybe alloc conference in constructor()

  controller_ = controller;

  // add interface on conference binding to allow
  // setting controller later(after constructor)

  // eg. conference_->SetController(controller_);
  conference_->SetController(controller);

  // emit conference connected event here
  Emit("focusChannelReady");
  Emit("conferenceReady");
  // and fire the same event on conference object
  conference_->Emit("focusChannelReady");
  conference_->Emit("connected");
}
void CallBinding::OnRealseConferenceBefore(
    yealink::RoomController* controller) {}
void CallBinding::OnVideoFrame(const yealink::VideoFrame& frame) {
  remote_video_source_->OnVideoFrame(frame);
}
void CallBinding::OnShareFrame(const yealink::VideoFrame& frame) {
  remote_share_video_source_->OnVideoFrame(frame);
}

}  // namespace rtvc

}  // namespace yealink
