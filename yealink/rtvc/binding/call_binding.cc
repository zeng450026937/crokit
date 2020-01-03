#include "yealink/rtvc/binding/call_binding.h"

#include "base/logging.h"
#include "build/build_config.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/glue/struct_traits.h"

#ifdef OS_WIN
#include "third_party/webrtc/modules/desktop_capture/win/screen_capture_utils.h"
#endif

namespace rtvc {

class CallBinding::UpgradeDelegate : public yealink::MeetingObserver {
 public:
  UpgradeDelegate(yealink::Meeting* pending_meeting,
                  base::OnceClosure success_callback,
                  base::OnceClosure fail_callback)
      : pending_meeting_(pending_meeting),
        success_callback_(std::move(success_callback)),
        fail_callback_(std::move(fail_callback)),
        weak_factory_(this) {
    observer_ = pending_meeting_->GetObserver();
    pending_meeting_->SetObserver(this);
  }
  ~UpgradeDelegate() { pending_meeting_->SetObserver(observer_); }

  bool GetResult() { return result_; }

  void Cancel() {
    if (completed_)
      return;
    yealink::SIPCode code = yealink::SIPCode::SIP_BUSY_HERE;
    pending_meeting_->Hangup(code, "Canceled");
  }

 protected:
  void OnEvent(yealink::MeetingEventId id) override {
    if (!Context::Instance()->CalledOnValidThread()) {
      Context::Instance()->PostTask(
          FROM_HERE, base::BindOnce(&UpgradeDelegate::OnEvent,
                                    weak_factory_.GetWeakPtr(), id));
      return;
    }

    switch (id) {
      case yealink::MEETING_ESTABLISHED:
        std::move(success_callback_).Run();
        result_ = true;
        break;
      case yealink::MEETING_FINISHED:
        std::move(fail_callback_).Run();
        result_ = false;
        break;
      default:
        return;
    }

    completed_ = true;
    pending_meeting_->SetObserver(observer_);
  }

 private:
  bool completed_ = false;
  bool result_ = false;
  yealink::MeetingObserver* observer_;
  yealink::Meeting* pending_meeting_;
  base::OnceClosure success_callback_;
  base::OnceClosure fail_callback_;
  base::WeakPtrFactory<UpgradeDelegate> weak_factory_;
};

// static
mate::WrappableBase* CallBinding::New(mate::Handle<UserAgentBinding> user_agent,
                                      mate::Arguments* args) {
  return new CallBinding(args->isolate(), args->GetThis(), user_agent, false);
}

// static
mate::Handle<CallBinding> CallBinding::Create(v8::Isolate* isolate,
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
      .SetMethod("getStats", &CallBinding::GetStats)
      .SetMethod("getInfos", &CallBinding::GetInfos)
      .SetProperty("isInProgress", &CallBinding::isInProgress)
      .SetProperty("isEstablished", &CallBinding::isEstablished)
      .SetProperty("isEnded", &CallBinding::isEnded)
      .SetProperty("isRefering", &CallBinding::isRefering)
      .SetProperty("isUpgrading", &CallBinding::isUpgrading)
      .SetProperty("isReadyForShare", &CallBinding::isReadyForShare)
      .SetProperty("isShareChannelSupported",
                   &CallBinding::isShareChannelSupported)
      .SetProperty("isShareChannelEstablished",
                   &CallBinding::isShareChannelEstablished)
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
      .SetProperty("conferenceAware", &CallBinding::conference_aware,
                   &CallBinding::SetConferenceAware)
      .SetMethod("asConference", &CallBinding::AsConference)
      .SetProperty("conference", &CallBinding::AsConference)
      .SetMethod("sendDTMF", &CallBinding::SendDTMF);
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
      controller_(nullptr),
      local_identity_(isolate, v8::Object::New(isolate)),
      remote_identity_(isolate, v8::Object::New(isolate)),
      call_info_(isolate, v8::Object::New(isolate)),
      incoming_(incoming),
      remote_video_source_(new VideoSourceAdapter()),
      remote_share_video_source_(new VideoSourceAdapter()) {
  InitWith(isolate, wrapper);
  meeting_->SetObserver(this);
  controller_ = meeting_->Room();
  conference_ = ConferenceBinding::Create(isolate, nullptr, user_agent_.get());
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
  conference_ = ConferenceBinding::Create(isolate, nullptr, user_agent_.get());
  v8_conference_.Reset(isolate, conference_.ToV8());
}

CallBinding::~CallBinding() {
  meeting_->SetObserver(nullptr);

  for (auto it : remote_video_source_->sinks()) {
    RemoveRemoteVideoSink(static_cast<VideoSinkV8*>(it)->GetHandle());
  }
  remote_video_source_->RemoveAllSinks();

  for (auto it : remote_share_video_source_->sinks()) {
    RemoveRemoteShareVideoSink(static_cast<VideoSinkV8*>(it)->GetHandle());
  }
  remote_share_video_source_->RemoveAllSinks();
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
    args->ThrowError(
        "Call is one time use. Create new Call instance instead."
        " Or maybe target uri is incorrect."
        " Or tcp(5061)/udp(5060) port is occupied");
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
  bool has_audio = true;
  bool has_video = true;
  mate::Dictionary dict;
  if (args->GetNext(&dict)) {
    dict.Get("audio", &has_audio);
    dict.Get("video", &has_video);
  }
  if (outgoing() && state_ == CallState::kNone) {
    meeting_->CreateAplloConference(GetContentType(has_audio, has_video));
    return Promise::ResolvedPromise(isolate());
  }
  if (state_ != CallState::kEstablished) {
    return Promise::RejectedPromise(
        isolate(), "Can not upgrade a call while it's not established.");
  }

  if (!upgrade_promise_) {
    upgrade_promise_.reset(new Promise(isolate()));

    meeting_->SetObserver(nullptr);

    pending_meeting_.reset(
        yealink::CreateMeeting(*sip_client_, *media_, false));
    pending_meeting_->SetObserver(this);
    pending_meeting_->CreateAplloConference(GetContentType(
        meeting_info_.isAudioEnabled, meeting_info_.isVideoEnabled));

    meeting_->SetObserver(this);

    upgrade_delegate_.reset(
        new UpgradeDelegate(pending_meeting_.get(),
                            base::BindOnce(&CallBinding::OnUpgradeSucceed,
                                           weak_factory_.GetWeakPtr()),
                            base::BindOnce(&CallBinding::OnUpgradeFailed,
                                           weak_factory_.GetWeakPtr())));
  }

  return upgrade_promise_->GetHandle();
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

v8::Local<v8::Promise> CallBinding::GetStats() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  yealink::MediaStreamStats media_stats = meeting_->AVMediaStats();
  yealink::VideoStreamStats share_stats = meeting_->ShareMediaStats();

  RTCStats v8_media_stats;
  ConvertFrom(v8_media_stats, media_stats);

  RTCVideoStats v8_share_video_stats;
  ConvertFrom(v8_share_video_stats, share_stats);

  RTCStats v8_share_stats;
  v8_share_stats.video = v8_share_video_stats;

  RTCStatsInfo result;

  result.media = v8_media_stats;
  result.share = v8_share_stats;

  std::move(promise).Resolve(result);

  return handle;
}

v8::Local<v8::Object> CallBinding::GetInfos() {
  return call_info_.GetHandle();
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
bool CallBinding::isReadyForShare() {
  return ready_for_share_;
}
bool CallBinding::isShareChannelSupported() {
  return true;
}
bool CallBinding::isShareChannelEstablished() {
  return ready_for_share_;
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

  HWND window = NULL;

  if (window_id != -1) {
#ifdef OS_WIN
    std::wstring device_key;
    if (webrtc::IsScreenValid(0, &device_key)) {
      webrtc::DesktopRect screen_rect = webrtc::GetScreenRect(0, device_key);
      width = screen_rect.width();
      height = screen_rect.height();
    }
    window = reinterpret_cast<HWND>(window_id);
#endif
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
    memset(&rect, 0, sizeof(RECT));
    rect.left = screen_rect.left();
    rect.top = screen_rect.top();
    rect.right = screen_rect.right();
    rect.bottom = screen_rect.bottom();
    width = screen_rect.width();
    height = screen_rect.height();
    window_id = reinterpret_cast<intptr_t>(
        ::MonitorFromRect(&rect, MONITOR_DEFAULTTONEAREST));
    window = reinterpret_cast<HWND>(window_id);
#endif
  }

  yealink::ShareWindow share_window;

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

void CallBinding::SetRemoteVideoSink(mate::Arguments* args) {
  mate::PersistentDictionary sink;
  if (!args->GetNext(&sink)) {
    for (auto it : remote_video_source_->sinks()) {
      RemoveRemoteVideoSink(static_cast<VideoSinkV8*>(it)->GetHandle());
    }
    remote_video_source_->RemoveAllSinks();
    return;
  }

  AddRemoteVideoSink(sink);
}

void CallBinding::AddRemoteVideoSink(mate::PersistentDictionary sink) {
  intptr_t hash;
  VideoSinkV8* sink_v8;

  if (!sink.GetHidden("hash", &hash)) {
    sink_v8 = new VideoSinkV8(sink);
    sink.SetHidden("hash", reinterpret_cast<intptr_t>(sink_v8));
  } else {
    sink_v8 = reinterpret_cast<VideoSinkV8*>(hash);
  }

  remote_video_source_->AddOrUpdateSink(sink_v8);
}

void CallBinding::RemoveRemoteVideoSink(mate::PersistentDictionary sink) {
  intptr_t hash;
  VideoSinkV8* sink_v8;

  if (!sink.GetHidden("hash", &hash))
    return;

  sink_v8 = reinterpret_cast<VideoSinkV8*>(hash);
  sink_v8->GetHandle().DeletePrivate("hash");
  remote_video_source_->RemoveSink(sink_v8);

  delete sink_v8;
}

void CallBinding::SetRemoteShareVideoSink(mate::Arguments* args) {
  mate::PersistentDictionary sink;
  if (!args->GetNext(&sink)) {
    for (auto it : remote_share_video_source_->sinks()) {
      RemoveRemoteShareVideoSink(static_cast<VideoSinkV8*>(it)->GetHandle());
    }
    remote_share_video_source_->RemoveAllSinks();
    return;
  }

  AddRemoteShareVideoSink(sink);
}

void CallBinding::AddRemoteShareVideoSink(mate::PersistentDictionary sink) {
  intptr_t hash;
  VideoSinkV8* sink_v8;

  if (!sink.GetHidden("hash", &hash)) {
    sink_v8 = new VideoSinkV8(sink);
    sink.SetHidden("hash", reinterpret_cast<intptr_t>(sink_v8));
  } else {
    sink_v8 = reinterpret_cast<VideoSinkV8*>(hash);
  }

  remote_share_video_source_->AddOrUpdateSink(sink_v8);
}

void CallBinding::RemoveRemoteShareVideoSink(mate::PersistentDictionary sink) {
  intptr_t hash;
  VideoSinkV8* sink_v8;

  if (!sink.GetHidden("hash", &hash))
    return;

  sink_v8 = reinterpret_cast<VideoSinkV8*>(hash);
  sink_v8->GetHandle().DeletePrivate("hash");
  remote_share_video_source_->RemoveSink(sink_v8);

  delete sink_v8;
}

bool CallBinding::conference_aware() {
  return true;
}
void CallBinding::SetConferenceAware(bool enable) {}

v8::Local<v8::Value> CallBinding::AsConference() {
  if (v8_conference_.IsEmpty()) {
    return v8::Null(isolate());
  }
  return v8::Local<v8::Value>::New(isolate(), v8_conference_);
}

void CallBinding::OnUpgradeSucceed() {
  meeting_->TransferToCall(pending_meeting_.get());
}
void CallBinding::OnUpgradeFailed() {
  if (upgrade_promise_) {
    std::unique_ptr<Promise> promise(upgrade_promise_.release());
    promise->Resolve("upgradeFailed");
  }
}

yealink::AVContentType CallBinding::GetContentType(bool has_audio,
                                                   bool has_video) {
  return has_audio && has_video
             ? yealink::AV_VIDEO_AUDIO
             : has_video ? yealink::AV_ONLY_VIDEO : yealink::AV_ONLY_AUDIO;
}

void CallBinding::ExtractCallInfo(yealink::MeetingInfo info) {
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

void CallBinding::ExtractConfInfo(yealink::AplloConferenceInvite info) {
  mate::Dictionary dict = mate::Dictionary::CreateEmpty(isolate());
  dict.Set("uri", info.strUri.ConstData());
  dict.Set("entity", info.strEntity.ConstData());
  dict.Set("number", info.strNumber.ConstData());
  dict.Set("subject", info.strSubject.ConstData());
  dict.Set("uuid", info.strUUID.ConstData());
  dict.Set("invitee", info.strInviter.ConstData());
  dict.Set("organizer", info.strOrganizer.ConstData());
  remote_identity_.Set("conference", dict);
}

void CallBinding::ExtractInfo() {
  yealink::MeetingInfo call_info;
  yealink::AplloConferenceInvite conf_info;

  meeting_->FetchInfo(call_info);
  ExtractCallInfo(call_info);

  if (meeting_->FetchInviteInfo(conf_info)) {
    ExtractConfInfo(conf_info);
  }
}

void CallBinding::OnConnectSuccess() {
  Emit("focus:ready");
  Emit("focus:established");
}

void CallBinding::OnConnectFailure(const char* reason) {
  Emit("focus:finished");
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
      ExtractInfo();
      if (outgoing()) {
        Emit("trying");
      }
      if (state_ != CallState::kProgress) {
        state_ = CallState::kProgress;
        Emit("progress");
      }
      if (incoming_ && user_agent_) {
        meeting_->Early("");
        user_agent_->Emit("incoming", this);
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
      ready_for_share_ = true;
      Emit("share:ready");
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
      if (upgrade_promise_) {
        std::unique_ptr<Promise> promise(upgrade_promise_.release());
        promise->Resolve();
        Emit("upgradeFailed");
      }
      break;
    case yealink::MEETING_REFER_DONE:
      if (refer_promise_) {
        std::unique_ptr<Promise> promise(refer_promise_.release());
        promise->Resolve();
        Emit("refered");
      }
      if (replace_promise_) {
        std::unique_ptr<Promise> promise(replace_promise_.release());
        promise->Reject();
        Emit("replaced");
      }
      if (upgrade_promise_) {
        std::unique_ptr<Promise> promise(upgrade_promise_.release());
        promise->Resolve();
        meeting_.swap(pending_meeting_);
        // update room controller
        OnCreateConferenceAfter(meeting_->Room());
        Emit("upgraded");
        Context::Instance()->PostTask(FROM_HERE,
                                      base::BindOnce(
                                          [](base::WeakPtr<CallBinding> call) {
                                            call->pending_meeting_.reset();
                                          },
                                          weak_factory_.GetWeakPtr()));
      }
      break;
    case yealink::MEETING_REPLACED:
      Emit("replaced");
      break;
    case yealink::MEETING_FINISHED:
      if (upgrade_promise_) {
        std::unique_ptr<Promise> promise(upgrade_promise_.release());
        promise->Resolve();
        Emit("upgradeFailed");
      }
      if (!upgrade_delegate_ && state_ != CallState::kTerminated) {
        state_ = CallState::kTerminated;
        Emit("finished");
      }
      if (upgrade_delegate_) {
        state_ = upgrade_delegate_->GetResult() ? CallState::kEstablished
                                                : CallState::kTerminated;
        upgrade_delegate_.reset();
      }
      // pending_meeting_ is the finished meeting, as it's refered
      // and we swap it
      if (pending_meeting_) {
        pending_meeting_->SetObserver(nullptr);
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

  std::string event_name;

  switch (id) {
    case yealink::MEETING_MEDIA_AUDIO_START:
      event_name = "rtc:audioStart";
      break;
    case yealink::MEETING_MEDIA_AUDIO_STOPED:
      event_name = "rtc:audioStop";
      break;
    case yealink::MEETING_MEDIA_AUDIO_BROKEN:
      event_name = "rtc:audioBroken";
      break;
    case yealink::MEETING_MEDIA_VIDEO_START:
      event_name = "rtc:videoStart";
      break;
    case yealink::MEETING_MEDIA_VIDEO_STOPED:
      event_name = "rtc:videoStop";
      break;
    case yealink::MEETING_MEDIA_VIDEO_BROKEN:
      event_name = "rtc:videoBroken";
      break;
    case yealink::MEETING_MEDIA_SHARE_RECV_START:
      remote_sharing_ = true;
      event_name = "rtc:shareRecvStart";
      break;
    case yealink::MEETING_MEDIA_SHARE_RECV_STOPED:
      remote_sharing_ = false;
      event_name = "rtc:shareRecvStop";
      break;
    case yealink::MEETING_MEDIA_SHARE_SEND_START:
      local_sharing_ = true;
      event_name = "rtc:shareSendStart";
      break;
    case yealink::MEETING_MEDIA_SHARE_SEND_STOPED:
      local_sharing_ = false;
      event_name = "rtc:shareSendStop";
      break;
    case yealink::MEETING_MEDIA_SHARE_BROKEN:
      local_sharing_ = false;
      remote_sharing_ = false;
      event_name = "rtc:shareBroken";
      break;
    case yealink::MEETING_MEDIA_HOLD_CHANGED:
      break;
    default:
      NOTREACHED();
      break;
  }

  if (event_name.size() && state_ != CallState::kNone) {
    Emit(event_name);
  }
}
void CallBinding::OnCallInfoChanged(const yealink::MeetingInfo& info) {
  if (!Context::Instance()->CalledOnValidThread()) {
    Context::Instance()->PostTask(
        FROM_HERE, base::BindOnce(&CallBinding::OnCallInfoChanged,
                                  weak_factory_.GetWeakPtr(), info));
    return;
  }

  ExtractCallInfo(info);
  Emit("update", call_info_.GetHandle());
}
void CallBinding::OnCreateConferenceAfter(yealink::RoomController* controller) {
  if (!controller) {
    conference_->SetController(controller);
    return;
  }

  if (!Context::Instance()->CalledOnValidThread()) {
    Context::Instance()->PostTask(
        FROM_HERE, base::BindOnce(&CallBinding::OnCreateConferenceAfter,
                                  weak_factory_.GetWeakPtr(), controller));
    return;
  }
  // ensure conference is not nullptr
  if (conference_.IsEmpty()) {
    conference_ =
        ConferenceBinding::Create(isolate(), controller, user_agent_.get());
    v8_conference_.Reset(isolate(), conference_.ToV8());
  }

  DCHECK(controller);

  controller_ = controller;
  controller_->AddObserver(this);

  if (user_agent_.get())
    controller_->SetAccessAgent(user_agent_->GetAccessAgent());

  // add interface on conference binding to allow
  // setting controller later(after constructor)
  conference_->SetController(controller);
  conference_->Emit("prepare");
  Emit("focus:prepare");
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
  DCHECK_EQ(controller, controller_);
  controller_->RemoveObserver(this);
  controller_ = nullptr;

  conference_->SetController(nullptr);
  conference_.Clear();
  v8_conference_.Reset();
}
void CallBinding::OnVideoFrame(const yealink::VideoFrame& frame, unsigned int id) {
  // we must copy video frame as soon as possible

  // if (!Context::Instance()->CalledOnValidThread()) {
  //   Context::Instance()->PostTask(
  //       FROM_HERE, base::BindOnce(&CallBinding::OnVideoFrame,
  //                                 weak_factory_.GetWeakPtr(), frame));

  //   return;
  // }

  remote_video_source_->OnVideoFrame(frame, id);
}
void CallBinding::OnShareFrame(const yealink::VideoFrame& frame, unsigned int id) {
  // we must copy video frame as soon as possible

  // if (!Context::Instance()->CalledOnValidThread()) {
  //   Context::Instance()->PostTask(
  //       FROM_HERE, base::BindOnce(&CallBinding::OnShareFrame,
  //                                 weak_factory_.GetWeakPtr(), frame));

  //   return;
  // }

  remote_share_video_source_->OnVideoFrame(frame, id);
}

}  // namespace rtvc
