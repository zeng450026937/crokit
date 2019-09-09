#include "yealink/rtvc/binding/call_binding.h"

#include "base/logging.h"
#include "build/build_config.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/converter.h"

#ifdef OS_WIN
#include "third_party/webrtc/modules/desktop_capture/win/screen_capture_utils.h"
#endif

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* CallBinding::New(mate::Handle<UserAgentBinding> user_agent,
                                      mate::Arguments* args) {
  return new CallBinding(args->isolate(), args->GetThis(), user_agent, false);
}

// static
mate::Handle<CallBinding> CallBinding::Create(
    v8::Isolate* isolate,
    mate::Handle<UserAgentBinding> user_agent,
    bool incoming) {
  return mate::CreateHandle(isolate,
                            new CallBinding(isolate, user_agent, incoming));
}

// static
mate::Handle<CallBinding> CallBinding::Create(
    v8::Isolate* isolate,
    UserAgentBinding* user_agent,
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
      .SetProperty("isRefering", &CallBinding::isRefering)
      .SetProperty("isUpgrading", &CallBinding::isUpgrading)
      .SetProperty("isEnded", &CallBinding::isEnded)
      .SetProperty("localSharing", &CallBinding::local_sharing)
      .SetProperty("remoteSharing", &CallBinding::remote_sharing)
      .SetProperty("incoming", &CallBinding::incoming)
      .SetProperty("outgoing", &CallBinding::outgoing)
      .SetProperty("portraitMode", &CallBinding::portrait_mode,
                   &CallBinding::SetPortraitMode)
      .SetMethod("setPortraitMode", &CallBinding::SetPortraitMode)
      .SetMethod("startShare", &CallBinding::StartShare)
      .SetMethod("stopShare", &CallBinding::StopShare)
      .SetMethod("setMediaBitrate", &CallBinding::SetMediaBitrate)
      .SetMethod("setShareBitrate", &CallBinding::SetShareBitrate)
      .SetMethod("setLocalVideoSource", &CallBinding::SetLocalVideoSource)
      .SetMethod("setLocalShareVideoSource",
                 &CallBinding::SetLocalShareVideoSource)
      .SetMethod("setRemoteVideoSink", &CallBinding::SetRemoteVideoSink)
      .SetMethod("addRemoteVideoSink", &CallBinding::AddRemoteVideoSink)
      .SetMethod("removeRemoteVideoSink", &CallBinding::RemoveRemoteVideoSink)
      .SetMethod("setRemoteShareVideoSink",
                 &CallBinding::SetRemoteShareVideoSink)
      .SetMethod("addRemoteShareVideoSink",
                 &CallBinding::AddRemoteShareVideoSink)
      .SetMethod("removeRemoteShareVideoSink",
                 &CallBinding::RemoveRemoteShareVideoSink)
      .SetMethod("getInfos", &CallBinding::GetInfos)
      .SetProperty("conferenceAware", &CallBinding::conference_aware,
                   &CallBinding::SetConferenceAware)
      .SetMethod("asConference", &CallBinding::AsConference)
      .SetProperty("conference", &CallBinding::AsConference);
}

CallBinding::CallBinding(v8::Isolate* isolate,
                         v8::Local<v8::Object> wrapper,
                         mate::Handle<UserAgentBinding> user_agent,
                         bool incoming)
    : user_agent_(user_agent->GetWeakPtr()),
      sip_client_(user_agent->GetWeakSIPClientPtr()),
      weak_factory_(this),
      media_(Context::Instance()->GetMedia()),
      meeting_(yealink::CreateMeeting(*sip_client_, *media_, incoming)),
      local_identity_(isolate, v8::Object::New(isolate)),
      remote_identity_(isolate, v8::Object::New(isolate)),
      call_info_(isolate, v8::Object::New(isolate)),
      incoming_(incoming),
      remote_video_source_(new VideoSourceAdapter()),
      remote_share_video_source_(new VideoSourceAdapter()) {
  InitWith(isolate, wrapper);
  meeting_->SetObserver(this);
}

CallBinding::CallBinding(v8::Isolate* isolate,
                         mate::Handle<UserAgentBinding> user_agent,
                         bool incoming)
    : user_agent_(user_agent->GetWeakPtr()),
      sip_client_(user_agent->GetWeakSIPClientPtr()),
      weak_factory_(this),
      media_(Context::Instance()->GetMedia()),
      meeting_(yealink::CreateMeeting(*sip_client_, *media_, incoming)),
      controller_(nullptr),
      local_identity_(isolate, v8::Object::New(isolate)),
      remote_identity_(isolate, v8::Object::New(isolate)),
      call_info_(isolate, v8::Object::New(isolate)),
      incoming_(incoming),
      remote_video_source_(new VideoSourceAdapter()),
      remote_share_video_source_(new VideoSourceAdapter()) {
  Init(isolate);
  meeting_->SetObserver(this);
  controller_ = meeting_->Room();
  conference_ = ConferenceBinding::Create(isolate, nullptr);
  v8_conference_.Reset(isolate, conference_.ToV8());
}

CallBinding::CallBinding(v8::Isolate* isolate,
                         UserAgentBinding* user_agent,
                         bool incoming)
    : user_agent_(user_agent->GetWeakPtr()),
      sip_client_(user_agent->GetWeakSIPClientPtr()),
      weak_factory_(this),
      media_(Context::Instance()->GetMedia()),
      meeting_(yealink::CreateMeeting(*sip_client_, *media_, incoming)),
      controller_(nullptr),
      local_identity_(isolate, v8::Object::New(isolate)),
      remote_identity_(isolate, v8::Object::New(isolate)),
      call_info_(isolate, v8::Object::New(isolate)),
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

v8::Local<v8::Object> CallBinding::local_identity() {
  return local_identity_.GetHandle();
}
v8::Local<v8::Object> CallBinding::remote_identity() {
  return remote_identity_.GetHandle();
}

void CallBinding::Connect(std::string target, mate::Arguments* args) {
  if (incoming()) {
    args->ThrowError("Can not connect target with a incoming call.");
    return;
  }

  bool has_audio = true;
  bool has_video = true;
  yealink::AVContentType content_type = yealink::AV_VIDEO_AUDIO;

  mate::Dictionary dict;
  if (args->GetNext(&dict)) {
    dict.Get("audio", &has_audio);
    dict.Get("video", &has_video);
    content_type = has_audio && has_video ? yealink::AV_VIDEO_AUDIO
                                          : has_video ? yealink::AV_ONLY_VIDEO
                                                      : yealink::AV_ONLY_AUDIO;
  }

  yealink::DailParam param;
  param.strUri = target.c_str();
  param.typAVContent = content_type;

  bool ret = meeting_->Dail(param);

  if (!ret) {
    args->ThrowError("Call is one time use. Create new Call instance instead.");
    return;
  }

  state_ = CallState::kProgress;
  Emit("progress");
}

void CallBinding::Answer(mate::Arguments* args) {
  if (outgoing()) {
    args->ThrowError("Can not answer with a outgoing call.");
    return;
  }

  bool has_audio = true;
  bool has_video = true;
  yealink::AVContentType content_type = yealink::AV_VIDEO_AUDIO;

  mate::Dictionary dict;
  if (args->GetNext(&dict)) {
    dict.Get("audio", &has_audio);
    dict.Get("video", &has_video);
    content_type = has_audio && has_video ? yealink::AV_VIDEO_AUDIO
                                          : has_video ? yealink::AV_ONLY_VIDEO
                                                      : yealink::AV_ONLY_AUDIO;
  }

  meeting_->Answer(content_type);

  state_ = CallState::kProgress;
  Emit("progress");
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

v8::Local<v8::Promise> CallBinding::Refer(std::string target) {
  if (refer_promise_) {
    Promise promise(isolate());
    promise.RejectWithErrorMessage(
        "Can not refer while previous refer request is processing.");
    return promise.GetHandle();
  }

  if (!refer_promise_) {
    refer_promise_.reset(new Promise(isolate()));
    meeting_->TransferToUri(target.c_str());
  }

  return refer_promise_->GetHandle();
}

v8::Local<v8::Promise> CallBinding::Replace(mate::Handle<CallBinding> call) {
  if (replace_promise_) {
    Promise promise(isolate());
    promise.RejectWithErrorMessage(
        "Can not replace while previous replace request is processing.");
    return promise.GetHandle();
  }

  if (!replace_promise_) {
    replace_promise_.reset(new Promise(isolate()));
    meeting_->TransferToCall(call->GetMeeting());
  }

  return replace_promise_->GetHandle();
}

v8::Local<v8::Promise> CallBinding::Upgrade(mate::Arguments* args) {
  return Promise::ResolvedPromise(isolate());
  // if (!upgrade_promise_) {
  //   upgrade_promise_.reset(new Promise(isolate()));
  //   DCHECK(meeting_info_.isEstablished);
  //   DCHECK(!meeting_info_.isFinished);
  //   meeting_->CreateAplloConference(GetContentType());
  // }

  // return upgrade_promise_->GetHandle();
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
bool CallBinding::isRefering() {
  return !!refer_promise_;
}
bool CallBinding::isReplacing() {
  return !!replace_promise_;
}
bool CallBinding::isUpgrading() {
  return !!upgrade_promise_;
}

bool CallBinding::local_sharing() {
  return local_sharing_;
}
bool CallBinding::remote_sharing() {
  return remote_sharing_;
}
bool CallBinding::portrait_mode() {
  return portrait_mode_;
}
void CallBinding::SetPortraitMode(bool enable) {
  meeting_->EnableVideoPortraitMode(enable);
}

void CallBinding::StartShare(mate::Dictionary dict, mate::Arguments* args) {
  int64_t window_id = -1;
  int64_t screen_id = -1;
  std::string file_path;
  int64_t width = 1080;
  int64_t height = 720;
  int64_t frame_rate = 5;

  dict.Get("window", &window_id);
  dict.Get("screen", &screen_id);
  dict.Get("file", &file_path);
  dict.Get("width", &width);
  dict.Get("height", &height);
  dict.Get("frameRate", &frame_rate);

  if (window_id < 0 && screen_id < 0 && !file_path.size()) {
    args->ThrowError(
        "Can not start share without any window/screen or image file.");
    return;
  }

  if (!file_path.size()) {
    args->ThrowError("Can not start share without fallback image file.");
    return;
  }

  if (screen_id != -1) {
#ifdef OS_WIN
    std::wstring device_key;
    if (!webrtc::IsScreenValid(screen_id, &device_key)) {
      args->ThrowError("Invalid screen id.");
      return;
    }
    webrtc::DesktopRect screen_rect =
        webrtc::GetScreenRect(screen_id, device_key);
    RECT rect;
    rect.left = screen_rect.left();
    rect.top = screen_rect.top();
    rect.right = screen_rect.right();
    rect.bottom = screen_rect.bottom();
    width = screen_rect.width();
    height = screen_rect.height();
    window_id = reinterpret_cast<intptr_t>(
        MonitorFromRect(&rect, MONITOR_DEFAULTTONEAREST));
#endif
  }

  yealink::ShareWindow share_window;

  HWND window = reinterpret_cast<HWND>(window_id);
  share_window.pHandle = reinterpret_cast<void*>(window);
  share_window.strCoverImgFile = file_path.c_str();
  share_window.nScreenWidth = width;
  share_window.nScreenHeight = height;
  share_window.nMaxSampleRate = frame_rate;

  meeting_->StartSendShare(share_window);
  local_sharing_ = true;
}
void CallBinding::StopShare() {
  if (!local_sharing_)
    return;
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

  AddRemoteVideoSink(sink);
}

void CallBinding::AddRemoteVideoSink(mate::PersistentDictionary sink) {
  if (sink.GetHandle()->IsNullOrUndefined()) {
    return;
  }

  int hash = sink.GetHandle()->GetIdentityHash();
  auto it = remote_video_sinks_.find(hash);

  if (it == remote_video_sinks_.end()) {
    VideoSinkV8* sink_v8 = new VideoSinkV8(sink);
    remote_video_source_->AddOrUpdateSink(sink_v8);
    remote_video_sinks_.emplace(hash, sink_v8);
  }
}

void CallBinding::RemoveRemoteVideoSink(mate::PersistentDictionary sink) {
  if (sink.GetHandle()->IsNullOrUndefined())
    return;

  int hash = sink.GetHandle()->GetIdentityHash();
  auto it = remote_video_sinks_.find(hash);

  if (it != remote_video_sinks_.end()) {
    remote_video_source_->RemoveSink(it->second);
    delete it->second;
    remote_video_sinks_.erase(it);
  }
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

  AddRemoteShareVideoSink(sink);
}

void CallBinding::AddRemoteShareVideoSink(mate::PersistentDictionary sink) {
  if (sink.GetHandle()->IsNullOrUndefined()) {
    return;
  }

  int hash = sink.GetHandle()->GetIdentityHash();
  auto it = remote_share_video_sinks_.find(hash);

  if (it == remote_share_video_sinks_.end()) {
    VideoSinkV8* sink_v8 = new VideoSinkV8(sink);
    remote_share_video_source_->AddOrUpdateSink(sink_v8);
    remote_share_video_sinks_.emplace(hash, sink_v8);
  }
}

void CallBinding::RemoveRemoteShareVideoSink(mate::PersistentDictionary sink) {
  if (sink.GetHandle()->IsNullOrUndefined())
    return;

  int hash = sink.GetHandle()->GetIdentityHash();
  auto it = remote_share_video_sinks_.find(hash);

  if (it != remote_share_video_sinks_.end()) {
    remote_share_video_source_->RemoveSink(it->second);
    delete it->second;
    remote_share_video_sinks_.erase(it);
  }
}

v8::Local<v8::Object> CallBinding::GetInfos() {
  return call_info_.GetHandle();
}

bool CallBinding::conference_aware() {
  return true;
}
void CallBinding::SetConferenceAware(bool enable) {}

v8::Local<v8::Value> CallBinding::AsConference() {
  DCHECK(conference_.get());
  return v8::Local<v8::Value>::New(isolate(), v8_conference_);
}

yealink::AVContentType CallBinding::GetContentType() {
  bool has_audio = meeting_info_.isAudioEnabled;
  bool has_video = meeting_info_.isVideoEnabled;
  return has_audio && has_video
             ? yealink::AV_VIDEO_AUDIO
             : has_video ? yealink::AV_ONLY_VIDEO : yealink::AV_ONLY_AUDIO;
}

void CallBinding::ExtractInfo(yealink::MeetingInfo info) {
  meeting_info_ = info;

  remote_identity_.Set("number", info.strNumber);
  remote_identity_.Set("domain", info.strDomain);
  remote_identity_.Set("display_name", info.strDisplayName);
  remote_identity_.Set("user_agent", info.strUserAgent);

  call_info_.Set("localIdentity", local_identity_.GetHandle());
  call_info_.Set("remoteIdentity", remote_identity_.GetHandle());

  call_info_.Set("audio", info.isAudioEnabled);
  call_info_.Set("video", info.isVideoEnabled);
  call_info_.Set("encrypted", info.isMediaEncrypted);
  call_info_.Set("succeed", info.isEstablished);
  call_info_.Set("established", !info.isFinished);
  call_info_.Set("finished", info.isFinished);
  call_info_.Set("remoteHold", info.isHoldByRemote);
  call_info_.Set("localHold", info.isHoldByLocal);
  call_info_.Set("incoming", info.isOffer);
  call_info_.Set("outgoing", !info.isOffer);
  call_info_.Set("supportReplace", info.isSupportReplaces);

  std::string reason;

  if (info.isFinished) {
    switch (info.idFinishEvent) {
      case yealink::AVCallHandler::FINISH_BY_ERROR:
        reason = "kError";
        break;
      case yealink::AVCallHandler::FINISH_BY_REPLACED:
        reason = "kReplaced";
        break;
      case yealink::AVCallHandler::FINISH_BY_REMOTE_CANCEL:
        reason = "kRemoteCanceled";
        break;
      case yealink::AVCallHandler::FINISH_BY_LOCAL_CANCEL:
        reason = "kLocalCanceled";
        break;
      case yealink::AVCallHandler::FINISH_BY_REMOTE_REFUSE:
        reason = "kRemoteRefuseed";
        break;
      case yealink::AVCallHandler::FINISH_BY_LOCAL_REFUSE:
        reason = "kLocalRefuseed";
        break;
      case yealink::AVCallHandler::FINISH_BY_REFERED:
        reason = "kRefered";
        break;
      case yealink::AVCallHandler::FINISH_BY_REMOTE_HANGUP:
        reason = "kRemoteHangup";
        break;
      case yealink::AVCallHandler::FINISH_BY_LOCAL_HANGUP:
        reason = "kLocalHangup";
        break;
      default:
        NOTREACHED();
        break;
    }
  }

  call_info_.Set("reason", reason);
}

void CallBinding::OnEvent(yealink::MeetingEventId id) {
  if (!Context::Instance()->CalledOnValidThread()) {
    Context::Instance()->PostTask(
        FROM_HERE,
        base::BindOnce(&CallBinding::OnEvent, weak_factory_.GetWeakPtr(), id));
    return;
  }

  switch (id) {
    case yealink::MEETING_CREATE:
      break;
    case yealink::MEETING_CONNECTED:
      if (incoming_ && user_agent_) {
        meeting_->Early("");
        user_agent_->Emit("incoming", this);
      }
      if (state_ != CallState::kProgress) {
        state_ = CallState::kProgress;
        Emit("progress");
      }
      break;
    case yealink::MEETING_RING:
      Emit("ringing");
      break;
    case yealink::MEETING_REDIRECT:
      Emit("redirect");
      break;
    case yealink::MEETING_ESTABLISHED:
      if (state_ != CallState::kEstablished) {
        state_ = CallState::kEstablished;
        Emit("established");
      }
      break;
    case yealink::MEETING_SHARE_ESTABLISHED:
      Emit("share:established");
      break;
    case yealink::MEETING_SHARE_FINISHED:
      local_sharing_ = false;
      remote_sharing_ = false;
      Emit("share:finished");
      break;
    case yealink::MEETING_REFER_FAILED:
      if (refer_promise_) {
        std::unique_ptr<Promise> promise(refer_promise_.release());
        promise->Reject();
        Emit("referFailed");
      }
      if (replace_promise_) {
        std::unique_ptr<Promise> promise(replace_promise_.release());
        promise->Reject();
        Emit("replaceFailed");
      }
      break;
    case yealink::MEETING_REFER_DONE:
      if (refer_promise_) {
        std::unique_ptr<Promise> promise(refer_promise_.release());
        promise->Resolve();
        Emit("refered");
      }
      break;
    case yealink::MEETING_REPLACED:
      if (replace_promise_) {
        std::unique_ptr<Promise> promise(replace_promise_.release());
        promise->Resolve();
        Emit("replaced");
      }
      break;
    case yealink::MEETING_FINISHED:
      if (state_ != CallState::kTerminated) {
        state_ = CallState::kTerminated;
        Emit("finished");
      }
      break;
    default:
      NOTREACHED();
      break;
  }
}
void CallBinding::OnMediaEvent(yealink::MeetingMediaEventId id) {
  if (!Context::Instance()->CalledOnValidThread()) {
    Context::Instance()->PostTask(
        FROM_HERE, base::BindOnce(&CallBinding::OnMediaEvent,
                                  weak_factory_.GetWeakPtr(), id));
    return;
  }

  switch (id) {
    case yealink::MEETING_MEDIA_AUDIO_START:
      Emit("rtc:audioStart");
      break;
    case yealink::MEETING_MEDIA_AUDIO_STOPED:
      Emit("rtc:audioStop");
      break;
    case yealink::MEETING_MEDIA_AUDIO_BROKEN:
      Emit("rtc:audioBroken");
      break;
    case yealink::MEETING_MEDIA_VIDEO_START:
      Emit("rtc:videoStart");
      break;
    case yealink::MEETING_MEDIA_VIDEO_STOPED:
      Emit("rtc:videoStop");
      break;
    case yealink::MEETING_MEDIA_VIDEO_BROKEN:
      Emit("rtc:videoBroken");
      break;
    case yealink::MEETING_MEDIA_SHARE_RECV_START:
      remote_sharing_ = true;
      Emit("rtc:shareRecvStart");
      break;
    case yealink::MEETING_MEDIA_SHARE_RECV_STOPED:
      remote_sharing_ = false;
      Emit("rtc:shareRecvStop");
      break;
    case yealink::MEETING_MEDIA_SHARE_SEND_START:
      local_sharing_ = true;
      Emit("rtc:shareSendStart");
      break;
    case yealink::MEETING_MEDIA_SHARE_SEND_STOPED:
      local_sharing_ = false;
      Emit("rtc:shareSendStop");
      break;
    case yealink::MEETING_MEDIA_SHARE_BROKEN:
      local_sharing_ = false;
      remote_sharing_ = false;
      Emit("rtc:shareBroken");
      break;
    case yealink::MEETING_MEDIA_HOLD_CHANGED:
      break;
    default:
      NOTREACHED();
      break;
  }
}
void CallBinding::OnCallInfoChanged(const yealink::MeetingInfo& info) {
  if (!Context::Instance()->CalledOnValidThread()) {
    Context::Instance()->PostTask(
        FROM_HERE, base::BindOnce(&CallBinding::OnCallInfoChanged,
                                  weak_factory_.GetWeakPtr(), info));
    return;
  }

  ExtractInfo(info);
  Emit("update", call_info_.GetHandle());
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

}
void CallBinding::OnRealseConferenceBefore(
    yealink::RoomController* controller) {
  if (!Context::Instance()->CalledOnValidThread()) {
    Context::Instance()->PostTask(
        FROM_HERE, base::BindOnce(&CallBinding::OnRealseConferenceBefore,
                                  weak_factory_.GetWeakPtr(), controller));
    return;
  }

  DCHECK(controller);
  controller_ = nullptr;
  // if (upgrade_promise_) {
  //   std::unique_ptr<Promise> promise(upgrade_promise_.release());
  //   promise->Resolve();
  //   Emit("upgradeFailed");
  // }
}
void CallBinding::OnVideoFrame(const yealink::VideoFrame& frame) {
  if (!Context::Instance()->CalledOnValidThread()) {
    Context::Instance()->PostTask(
        FROM_HERE, base::BindOnce(&CallBinding::OnVideoFrame,
                                  weak_factory_.GetWeakPtr(), frame));

    return;
  }

  remote_video_source_->OnVideoFrame(frame);
}
void CallBinding::OnShareFrame(const yealink::VideoFrame& frame) {
  if (!Context::Instance()->CalledOnValidThread()) {
    Context::Instance()->PostTask(
        FROM_HERE, base::BindOnce(&CallBinding::OnShareFrame,
                                  weak_factory_.GetWeakPtr(), frame));

    return;
  }

  remote_share_video_source_->OnVideoFrame(frame);
}

}  // namespace rtvc

}  // namespace yealink
