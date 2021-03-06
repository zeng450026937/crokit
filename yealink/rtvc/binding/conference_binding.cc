#include "yealink/rtvc/binding/conference_binding.h"

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "base/unguessable_token.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/conference_state_binding.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* ConferenceBinding::New(
    mate::Handle<UserAgentBinding> user_agent,
    mate::Arguments* args) {
  return new ConferenceBinding(args->isolate(), args->GetThis(), user_agent);
}

mate::Handle<ConferenceBinding> ConferenceBinding::Create(
    v8::Isolate* isolate,
    yealink::RoomController* controller,
    UserAgentBinding* user_agent) {
  return mate::CreateHandle(
      isolate, new ConferenceBinding(isolate, controller, user_agent));
}

// static
void ConferenceBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "Conference"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetMethod("connect", &ConferenceBinding::Connect)
      .SetMethod("disconnect", &ConferenceBinding::Disconnect)
      .SetMethod("create", &ConferenceBinding::CreateConference)
      .SetProperty("description", &ConferenceBinding::description)
      .SetProperty("view", &ConferenceBinding::view)
      .SetProperty("state", &ConferenceBinding::state)
      .SetProperty("users", &ConferenceBinding::users)
      .SetProperty("rtmp", &ConferenceBinding::rtmp)
      .SetProperty("record", &ConferenceBinding::record)
      .SetProperty("chat", &ConferenceBinding::chat)
      .SetProperty("isInProgress", &ConferenceBinding::isInProgress)
      .SetProperty("isEstablished", &ConferenceBinding::isEstablished)
      .SetProperty("isEnded", &ConferenceBinding::isEnded)
      .SetProperty("isChatChannelSupported",
                   &ConferenceBinding::isChatChannelSupported)
      .SetProperty("isChatChannelEstablished",
                   &ConferenceBinding::isChatChannelEstablished);
}

ConferenceBinding::ConferenceBinding(v8::Isolate* isolate,
                                     v8::Local<v8::Object> wrapper,
                                     mate::Handle<UserAgentBinding> user_agent)
    : locally_generated_controller_(true),
      controller_(nullptr),
      chat_controller_(nullptr),
      user_agent_(user_agent->GetWeakPtr()),
      sip_client_(user_agent->GetWeakSIPClientPtr()),
      weak_factory_(this) {
  InitWith(isolate, wrapper);

  description_ =
      ConferenceDescriptionBinding::Create(isolate, controller_.get());
  v8_description_.Reset(isolate, description_.ToV8());

  view_ = ConferenceViewBinding::Create(isolate, controller_.get());
  v8_view_.Reset(isolate, view_.ToV8());

  state_ = ConferenceStateBinding::Create(isolate, controller_.get());
  v8_state_.Reset(isolate, state_.ToV8());

  users_ = ConferenceUsersBinding::Create(isolate, controller_.get());
  v8_users_.Reset(isolate, users_.ToV8());

  rtmp_ = ConferenceRtmpBinding::Create(isolate, controller_.get());
  v8_rtmp_.Reset(isolate, rtmp_.ToV8());

  record_ = ConferenceRecordBinding::Create(isolate, controller_.get());
  v8_record_.Reset(isolate, record_.ToV8());

  chat_ = ConferenceChatBinding::Create(isolate, controller_.get());
  v8_chat_.Reset(isolate, chat_.ToV8());
}
ConferenceBinding::ConferenceBinding(v8::Isolate* isolate,
                                     yealink::RoomController* controller,
                                     UserAgentBinding* user_agent)
    : locally_generated_controller_(false),
      controller_(controller),
      user_agent_(user_agent->GetWeakPtr()),
      weak_factory_(this) {
  Init(isolate);

  description_ =
      ConferenceDescriptionBinding::Create(isolate, controller_.get());
  v8_description_.Reset(isolate, description_.ToV8());

  view_ = ConferenceViewBinding::Create(isolate, controller_.get());
  v8_view_.Reset(isolate, view_.ToV8());

  state_ = ConferenceStateBinding::Create(isolate, controller_.get());
  v8_state_.Reset(isolate, state_.ToV8());

  users_ = ConferenceUsersBinding::Create(isolate, controller_.get());
  v8_users_.Reset(isolate, users_.ToV8());

  rtmp_ = ConferenceRtmpBinding::Create(isolate, controller_.get());
  v8_rtmp_.Reset(isolate, rtmp_.ToV8());

  record_ = ConferenceRecordBinding::Create(isolate, controller_.get());
  v8_record_.Reset(isolate, record_.ToV8());

  chat_ = ConferenceChatBinding::Create(isolate, controller_.get());
  v8_chat_.Reset(isolate, chat_.ToV8());

  if (controller_ && !chat_controller_) {
    std::unique_ptr<yealink::ChatManager> manager(
        new yealink::ChatManager(*controller_, 2000));

    chat_controller_ = std::move(manager);
    chat_controller_->AddObserver(this);
    chat_->UpdateChatController(chat_controller_.get());
  }
}

ConferenceBinding::~ConferenceBinding() {
  if (!locally_generated_controller_)
    controller_.release();
}

void ConferenceBinding::SetController(RoomController* controller) {
  locally_generated_controller_ = false;

  if (controller_)
    controller_->RemoveObserver(this);

  if (controller)
    controller_ = std::make_unique<RoomController>(*controller);
  else
    controller_.reset();

  if (controller_)
    controller_->AddObserver(this);

  if (controller_ && !chat_controller_) {
    std::unique_ptr<yealink::ChatManager> manager(
        new yealink::ChatManager(*controller_, 2000));

    chat_controller_ = std::move(manager);
    chat_controller_->AddObserver(this);
    chat_->UpdateChatController(chat_controller_.get());
  }

  state_->UpdateRoomController(controller_.get());
  description_->UpdateRoomController(controller_.get());
  users_->UpdateRoomController(controller_.get());
  view_->UpdateRoomController(controller_.get());
  rtmp_->UpdateRoomController(controller_.get());
  record_->UpdateRoomController(controller_.get());
  chat_->UpdateRoomController(controller_.get());

  description_->UpdatePendingHandler(&pending_requests_);
  users_->UpdateStatsPendingHandler(&stats_pending_requests_);
}

void ConferenceBinding::SetController(
    std::unique_ptr<RoomController> controller) {
  if (controller_)
    controller_->RemoveObserver(this);

  controller_ = std::move(controller);

  if (controller_)
    controller_->AddObserver(this);

  if (controller_ && !chat_controller_) {
    std::unique_ptr<yealink::ChatManager> manager(
        new yealink::ChatManager(*controller_, 2000));

    chat_controller_ = std::move(manager);
    chat_controller_->AddObserver(this);
    chat_->UpdateChatController(chat_controller_.get());
  }

  state_->UpdateRoomController(controller_.get());
  description_->UpdateRoomController(controller_.get());
  users_->UpdateRoomController(controller_.get());
  view_->UpdateRoomController(controller_.get());
  rtmp_->UpdateRoomController(controller_.get());
  record_->UpdateRoomController(controller_.get());
  chat_->UpdateRoomController(controller_.get());

  description_->UpdatePendingHandler(&pending_requests_);
  users_->UpdateStatsPendingHandler(&stats_pending_requests_);
}

void ConferenceBinding::Connect(mate::Dictionary dict, mate::Arguments* args) {
  DCHECK(sip_client_);

  std::string uri;
  std::string entity;
  std::string conversation_id = base::UnguessableToken::Create().ToString();

  if (!dict.Get("uri", &uri) || !dict.Get("entity", &entity)) {
    args->ThrowError("Conference uri & entitiy is required.");
    return;
  }
  dict.Get("conversationId", &conversation_id);

  yealink::RoomController::ConferenceParam params;
  params.conferenceUri = uri.c_str();
  params.conferenceEntity = entity.c_str();

  std::unique_ptr<yealink::RoomController> controller(
      new yealink::RoomController());

  if (user_agent_.get())
    controller->SetAccessAgent(user_agent_->GetAccessAgent());

  controller->Join(sip_client_.get(), params);

  SetController(std::move(controller));
  conversation_id_ = conversation_id;
}

void ConferenceBinding::Disconnect(mate::Arguments* args) {
  bool endnow = false;
  args->GetNext(&endnow);

  if (endnow)
    controller_->Close();
  else
    controller_->Leave("");
}

void ConferenceBinding::CreateConference(mate::Dictionary dict,
                                         mate::Arguments* args) {
  DCHECK(sip_client_);

  std::string conversation_id = base::UnguessableToken::Create().ToString();
  std::string subject;

  if (!dict.Get("subject", &subject)) {
    args->ThrowError("Conference subject & type is required.");
    return;
  }
  dict.Get("conversationId", &conversation_id);

  yealink::RequestResult result;
  // yealink::rtvc::ResponseInfo response;
  yealink::Array<yealink::SStringA> params;

  std::unique_ptr<yealink::RoomController> controller(
      new yealink::RoomController());

  ConferenceResult ret;

  controller->Init();
  controller->SetConversationId(conversation_id.c_str());

  if (user_agent_.get())
    controller->SetAccessAgent(user_agent_->GetAccessAgent());

  ret =
      controller->CreateTempMeeting(sip_client_.get(), subject.c_str(), params);

  SetController(std::move(controller));
  conversation_id_ = conversation_id;
}

bool ConferenceBinding::isInProgress() {
  return false;
}
bool ConferenceBinding::isEstablished() {
  return false;
}
bool ConferenceBinding::isEnded() {
  return false;
}
bool ConferenceBinding::isChatChannelSupported() {
  return false;
}
bool ConferenceBinding::isChatChannelEstablished() {
  return false;
}

v8::Local<v8::Value> ConferenceBinding::description() {
  DCHECK(description_.get());
  if (v8_description_.IsEmpty()) {
    return v8::Null(isolate());
  }
  return v8::Local<v8::Value>::New(isolate(), v8_description_);
}
v8::Local<v8::Value> ConferenceBinding::view() {
  DCHECK(view_.get());
  if (v8_view_.IsEmpty()) {
    return v8::Null(isolate());
  }
  return v8::Local<v8::Value>::New(isolate(), v8_view_);
}
v8::Local<v8::Value> ConferenceBinding::state() {
  DCHECK(state_.get());
  if (v8_state_.IsEmpty()) {
    return v8::Null(isolate());
  }
  return v8::Local<v8::Value>::New(isolate(), v8_state_);
}
v8::Local<v8::Value> ConferenceBinding::users() {
  DCHECK(users_.get());
  if (v8_users_.IsEmpty()) {
    return v8::Null(isolate());
  }
  return v8::Local<v8::Value>::New(isolate(), v8_users_);
}
v8::Local<v8::Value> ConferenceBinding::rtmp() {
  DCHECK(rtmp_.get());
  if (v8_rtmp_.IsEmpty()) {
    return v8::Null(isolate());
  }
  return v8::Local<v8::Value>::New(isolate(), v8_rtmp_);
}
v8::Local<v8::Value> ConferenceBinding::record() {
  DCHECK(record_.get());
  if (v8_record_.IsEmpty()) {
    return v8::Null(isolate());
  }
  return v8::Local<v8::Value>::New(isolate(), v8_record_);
}

v8::Local<v8::Value> ConferenceBinding::chat() {
  DCHECK(chat_.get());
  if (v8_chat_.IsEmpty()) {
    return v8::Null(isolate());
  }
  return v8::Local<v8::Value>::New(isolate(), v8_chat_);
}

void ConferenceBinding::OnConnectSuccess() {
  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    context->PostTask(FROM_HERE,
                      base::BindOnce(&ConferenceBinding::OnConnectSuccess,
                                     weak_factory_.GetWeakPtr()));
    return;
  }

  // First Information Update
  Array<RoomMember> empty;
  users_->UpdateUsers(empty, empty, empty, true);

  Emit("connected");

  Emit("descriptionUpdated", description());
  Emit("stateUpdated", state());
  Emit("viewUpdated", view());
  Emit("rtmpUpdated", rtmp());
  Emit("recordUpdated", record());
}
void ConferenceBinding::OnConnectFailure(const char* c_reason) {
  conversation_id_ = "";

  std::string reason(c_reason);
  if (reason.size() != 0) {
    Emit("connectFailed");
  } else {
    Emit("disconnected");
    Emit("finished");
  }
}
void ConferenceBinding::OnResponse(const yealink::ResponseResult& response) {
  // int64_t request_id = response.requestId;
  // ResponseResult::Status request_status = response.status;

  // auto it = pending_requests_.find(request_id);

  // if (it == pending_requests_.end())
  //   return;

  // switch (request_status) {
  //   case ResponseResult::Status::SUCCESS:
  //     std::move(it->second).Resolve();
  //     break;
  //   case ResponseResult::Status::FAILURE:
  //     std::move(it->second).Reject();
  //     break;
  //   case ResponseResult::Status::PENDING:
  //   case ResponseResult::Status::INVALID:
  //   default:
  //     return;
  // }

  // pending_requests_.erase(it);
}
void ConferenceBinding::OnSubscriptionDisconnect() {
  controller_->ReconnectSubscriptionForce();
}
void ConferenceBinding::OnConferenceDescriptionChange(
    const yealink::ConferenceDescription&) {
  Emit("descriptionUpdated", description());
}
void ConferenceBinding::OnConferenceStateChange(
    const yealink::ConferenceState&) {
  Emit("stateUpdated", state());
}
void ConferenceBinding::OnConferenceViewChange(const yealink::ConferenceView&) {
  Emit("viewUpdated", view());
}
void ConferenceBinding::OnRtmpStateChange(const RoomRtmpState&) {
  Emit("rtmpUpdated", rtmp());
}
void ConferenceBinding::OnRecordUsersChange(const RoomRecordUsers&) {
  Emit("recordUpdated", record());
}

void ConferenceBinding::OnUserChange(
    const Array<RoomMember>& newMemberList,
    const Array<RoomMember>& modifyMemberList,
    const Array<RoomMember>& deleteMemberList) {
  users_->UpdateUsers(newMemberList, modifyMemberList, deleteMemberList, false);

  Emit("usersUpdated", users());

  if ((int)newMemberList.Size() > 0)
    Emit("user:added", users_->addedUser());

  if ((int)modifyMemberList.Size() > 0)
    Emit("user:updated", users_->updatedUser());

  if ((int)deleteMemberList.Size() > 0)
    Emit("user:removed", users_->deletedUser());
}
void ConferenceBinding::OnGetUserCallStats(
    const RoomMember& member,
    const Array<yealink::UserMediaInfo>& info) {
  std::vector<UserStatisticsInfo> stats;

  ConvertFrom(stats, info);

  auto it = stats_pending_requests_.find(
      std::string(member.GetMemberInfo().entity.ConstData()));

  if (it == stats_pending_requests_.end())
    return;

  std::move(it->second).Resolve(mate::ConvertToV8(isolate(), stats));

  stats_pending_requests_.erase(it);

  // Emit("callStatsUpdated", member.GetMemberInfo().entity.ConstData(),
  //      mate::ConvertToV8(isolate(), stats));
}
void ConferenceBinding::OnGetShareInfo(int64_t requestId,
                                       const char* shareInfo) {
  auto it = pending_requests_.find(requestId);

  if (it == pending_requests_.end())
    return;

  std::move(it->second).Resolve(std::string(shareInfo));

  pending_requests_.erase(it);

  // Emit("shareInfoUpdated", requestId, std::string(shareInfo));
}

void ConferenceBinding::OnImRecord(const char* messageBody) {}

void ConferenceBinding::OnReceiveMessage(const ChatMessageItem& message) {
  ChatMessageItem item = message;
  mate::Handle<ConferenceMessageBinding> new_message =
      ConferenceMessageBinding::Create(isolate(), item);
  v8::Global<v8::Value> v8_new_message;
  v8_new_message.Reset(isolate(), new_message.ToV8());

  Emit("messageUpdated", v8::Local<v8::Value>::New(isolate(), v8_new_message));
}

void ConferenceBinding::OnDialogChange() {
  Emit("dialogUpdated");
}

}  // namespace rtvc

}  // namespace yealink
