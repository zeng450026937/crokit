#include "yealink/rtvc/binding/conference_users_binding.h"

#include "base/logging.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* ConferenceUsersBinding::New(mate::Arguments* args) {
  return new ConferenceUsersBinding(args->isolate(), args->GetThis());
}

mate::Handle<ConferenceUsersBinding> ConferenceUsersBinding::Create(
    v8::Isolate* isolate,
    yealink::RoomController* controller) {
  return mate::CreateHandle(isolate,
                            new ConferenceUsersBinding(isolate, controller));
}

// static
void ConferenceUsersBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "ConferenceUsers"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("currentUser", &ConferenceUsersBinding::CurrentUser)
      .SetMethod("invite", &ConferenceUsersBinding::Invite)
      .SetMethod("inviteThird", &ConferenceUsersBinding::InviteThird)
      .SetMethod("inviteBatch", &ConferenceUsersBinding::InviteBatch)
      .SetMethod("allow", &ConferenceUsersBinding::Allow);
}

void ConferenceUsersBinding::UpdateRoomController(RoomController* handler) {
  room_controller_ = handler;
}

ConferenceUsersBinding::ConferenceUsersBinding(
    v8::Isolate* isolate,
    yealink::RoomController* controller)
    : weak_factory_(this) {
  Init(isolate);
  room_controller_ = controller;
}
ConferenceUsersBinding::ConferenceUsersBinding(v8::Isolate* isolate,
                                               v8::Local<v8::Object> wrapper)
    : weak_factory_(this) {}
ConferenceUsersBinding::~ConferenceUsersBinding() = default;

v8::Local<v8::Value> ConferenceUsersBinding::CurrentUser() {
  UserInfo value;

  if (room_controller_)
    ConvertFrom(
        value, room_controller_->GetMemberManager().GetOwner().GetMemberInfo());

  return mate::ConvertToV8(isolate(), value);
}

v8::Local<v8::Promise> ConferenceUsersBinding::Invite(mate::Arguments* args) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  std::string uri;

  if (!args->GetNext(&uri)) {
    args->ThrowError("uri is required");
  }

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUsersBinding::DoInvite,
                     weak_factory_.GetWeakPtr(), uri),
      base::BindOnce(&ConferenceUsersBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUsersBinding::DoInvite(std::string uri) {
  if (room_controller_) {
    room_controller_->GetMemberManager().InviteUser(uri.c_str());
  }
}

v8::Local<v8::Promise> ConferenceUsersBinding::InviteThird(std::string uri,
                                                           std::string uid) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUsersBinding::DoInviteThird,
                     weak_factory_.GetWeakPtr(), uri, uid),
      base::BindOnce(&ConferenceUsersBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUsersBinding::DoInviteThird(std::string uri, std::string uid) {
  if (room_controller_) {
    room_controller_->GetMemberManager().InviteUserWithUuid(uri.c_str(),
                                                            uid.c_str());
  }
}

v8::Local<v8::Promise> ConferenceUsersBinding::InviteBatch(
    std::vector<std::string> uri) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUsersBinding::DoInviteBatch,
                     weak_factory_.GetWeakPtr(), uri),
      base::BindOnce(&ConferenceUsersBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUsersBinding::DoInviteBatch(std::vector<std::string> uri) {
  yealink::Array<yealink::SStringA> params;

  if (room_controller_) {
    ConvertTo(uri, params);
    room_controller_->GetMemberManager().InviteUserList(params);
  }
}

v8::Local<v8::Promise> ConferenceUsersBinding::Allow(
    std::vector<std::string> entities,
    bool granted) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceUsersBinding::DoAllow,
                     weak_factory_.GetWeakPtr(), entities, granted),
      base::BindOnce(&ConferenceUsersBinding::OnCommandCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}

void ConferenceUsersBinding::DoAllow(std::vector<std::string> entities,
                                     bool granted) {
  yealink::Array<RoomMember> params;  // todo get member control

  if (room_controller_) {
    if (granted) {
      if (entities.size() > 0)
        room_controller_->GetMemberManager().GrantedLobby(params);
      else
        room_controller_->GetMemberManager().GrantedLobbyAll();
    } else {
      if (entities.size() > 0)
        room_controller_->GetMemberManager().DeleteLobby(params);
      else
        room_controller_->GetMemberManager().DeleteLobbyAll();
    }
  }
}

void ConferenceUsersBinding::OnCommandCompeleted(Promise promise) {
  std::move(promise).Resolve(true);
}

}  // namespace rtvc

}  // namespace yealink
