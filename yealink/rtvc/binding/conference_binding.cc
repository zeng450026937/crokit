#include "yealink/rtvc/binding/conference_binding.h"

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/conference_state_binding.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* ConferenceBinding::New(mate::Arguments* args) {
  return new ConferenceBinding(args->isolate(), args->GetThis());
}

mate::Handle<ConferenceBinding> ConferenceBinding::Create(
    v8::Isolate* isolate,
    yealink::RoomController* controller) {
  return mate::CreateHandle(isolate,
                            new ConferenceBinding(isolate, controller));
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
      .SetProperty("description", &ConferenceBinding::Description)
      .SetProperty("view", &ConferenceBinding::View)
      .SetProperty("state", &ConferenceBinding::State)
      .SetProperty("users", &ConferenceBinding::Users)
      .SetProperty("isInProgress", &ConferenceBinding::isInProgress)
      .SetProperty("isEstablished", &ConferenceBinding::isEstablished)
      .SetProperty("isEnded", &ConferenceBinding::isEnded)
      .SetProperty("isChatChannelSupported",
                   &ConferenceBinding::isChatChannelSupported)
      .SetProperty("isChatChannelEstablished",
                   &ConferenceBinding::isChatChannelEstablished);
}

void ConferenceBinding::SetController(RoomController* controller) {
  controller_ = controller;
  controller_->AddObserver(this);
  state_->UpdateRoomController(controller);
  description_->UpdateRoomController(controller);
  users_->UpdateRoomController(controller);
  view_->UpdateRoomController(controller);
}

ConferenceBinding::ConferenceBinding(v8::Isolate* isolate,
                                     v8::Local<v8::Object> wrapper)
    : controller_(nullptr), weak_factory_(this) {
  InitWith(isolate, wrapper);
}
ConferenceBinding::ConferenceBinding(v8::Isolate* isolate,
                                     yealink::RoomController* controller)
    : controller_(controller), weak_factory_(this) {
  Init(isolate);

  description_ = ConferenceDescriptionBinding::Create(isolate, controller_);
  v8_description_.Reset(isolate, description_.ToV8());
  view_ = ConferenceViewBinding::Create(isolate, controller_);
  v8_view_.Reset(isolate, view_.ToV8());
  state_ = ConferenceStateBinding::Create(isolate, controller_);
  v8_state_.Reset(isolate, state_.ToV8());
  users_ = ConferenceUsersBinding::Create(isolate, controller_);
  v8_users_.Reset(isolate, users_.ToV8());
}

ConferenceBinding::~ConferenceBinding() {
  LOG(INFO) << __FUNCTIONW__;
}

void ConferenceBinding::Connect() {}
void ConferenceBinding::Disconnect() {}

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

v8::Local<v8::Value> ConferenceBinding::Description() {
  DCHECK(description_.get());
  if (v8_description_.IsEmpty()) {
    v8_description_.Reset(isolate(), description_.ToV8());
  }
  return v8::Local<v8::Value>::New(isolate(), v8_description_);
}
v8::Local<v8::Value> ConferenceBinding::View() {
  DCHECK(view_.get());
  if (v8_view_.IsEmpty()) {
    v8_view_.Reset(isolate(), view_.ToV8());
  }
  return v8::Local<v8::Value>::New(isolate(), v8_view_);
}
v8::Local<v8::Value> ConferenceBinding::State() {
  DCHECK(state_.get());
  if (v8_state_.IsEmpty()) {
    v8_state_.Reset(isolate(), state_.ToV8());
  }
  return v8::Local<v8::Value>::New(isolate(), v8_state_);
}
v8::Local<v8::Value> ConferenceBinding::Users() {
  DCHECK(users_.get());
  if (v8_users_.IsEmpty()) {
    v8_users_.Reset(isolate(), users_.ToV8());
  }
  return v8::Local<v8::Value>::New(isolate(), v8_users_);
}

void ConferenceBinding::OnConnectSuccess() {
  LOG(INFO) << __FUNCTIONW__;
}
void ConferenceBinding::OnConnectFailure(const char* reason) {
  LOG(INFO) << __FUNCTIONW__;
}
void ConferenceBinding::OnResponse(const ResponseResult& response) {
  LOG(INFO) << __FUNCTIONW__;
}
void ConferenceBinding::OnSubscriptionDisconnect() {
  LOG(INFO) << __FUNCTIONW__;
}
void ConferenceBinding::OnConferenceDescriptionChange(
    const yealink::ConferenceDescription& desc) {
  LOG(INFO) << __FUNCTIONW__;

  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    context->PostTask(
        FROM_HERE,
        base::BindOnce(&ConferenceBinding::OnConferenceDescriptionChange,
                       weak_factory_.GetWeakPtr(), desc));
    return;
  }

  Emit("descriptionUpdated");
}
void ConferenceBinding::OnConferenceStateChange(
    const yealink::ConferenceState& state) {
  LOG(INFO) << __FUNCTIONW__;

  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    context->PostTask(
        FROM_HERE, base::BindOnce(&ConferenceBinding::OnConferenceStateChange,
                                  weak_factory_.GetWeakPtr(), state));
    return;
  }

  Emit("stateUpdated");
}
void ConferenceBinding::OnConferenceViewChange(
    const yealink::ConferenceView& view) {
  LOG(INFO) << __FUNCTIONW__;

  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    context->PostTask(FROM_HERE,
                      base::BindOnce(&ConferenceBinding::OnConferenceViewChange,
                                     weak_factory_.GetWeakPtr(), view));
    return;
  }

  Emit("viewUpdated");
}

void ConferenceBinding::OnUserChange(
    const Array<RoomMember>& newMemberList,
    const Array<RoomMember>& modifyMemberList,
    const Array<RoomMember>& deleteMemberList) {
  LOG(INFO) << __FUNCTIONW__;
}
void ConferenceBinding::OnGetUserCallStats(
    const RoomMember& member,
    const Array<yealink::UserMediaInfo>& info) {
  LOG(INFO) << __FUNCTIONW__;
}
void ConferenceBinding::OnGetShareInfo(int64_t requestId,
                                       const char* shareInfo) {
  LOG(INFO) << __FUNCTIONW__;

  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    std::string data = shareInfo;
    char* param = new char[data.size() + 1];
    strcpy(param, shareInfo);

    context->PostTask(
        FROM_HERE,
        base::BindOnce(&ConferenceBinding::OnGetShareInfo,
                       weak_factory_.GetWeakPtr(), requestId, param));
    return;
  }

  if (shareInfo) {
    Emit("shareInfoUpdated", requestId, shareInfo);
    delete[] shareInfo;
    shareInfo = nullptr;
  } else {
    Emit("shareInfoUpdated", requestId, "");
  }
}

}  // namespace rtvc

}  // namespace yealink
