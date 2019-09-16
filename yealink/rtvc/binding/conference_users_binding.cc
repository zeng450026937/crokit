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
      .SetProperty("userList", &ConferenceUsersBinding::UserList)
      .SetMethod("invite", &ConferenceUsersBinding::Invite)
      .SetMethod("inviteThird", &ConferenceUsersBinding::InviteThird)
      .SetMethod("inviteBatch", &ConferenceUsersBinding::InviteBatch)
      .SetMethod("allow", &ConferenceUsersBinding::Allow);
}

void ConferenceUsersBinding::UpdateRoomController(RoomController* handler) {
  room_controller_ = handler;
}

void ConferenceUsersBinding::UpdateStatsPendingHandler(
    std::unordered_map<std::string, Promise>* handler) {
  stats_pending_requests_ = handler;
}

void ConferenceUsersBinding::UpdateUsers(
    const Array<RoomMember>& newMemberList,
    const Array<RoomMember>& modifyMemberList,
    const Array<RoomMember>& deleteMemberList,
    bool force) {
  uint32_t i;

  if (force == true) {
    Array<RoomMember> memberList =
        room_controller_->GetMemberManager().GetMemberList();
    RoomMember owner = room_controller_->GetMemberManager().GetOwner();

    // v8::HandleScope handle_scope(isolate());

    current_user_ = ConferenceUserBinding::Create(isolate(), owner,
                                                  stats_pending_requests_);
    v8_current_user_.Reset(isolate(), current_user_.ToV8());

    for (i = 0; i < memberList.Size(); i++) {
      std::string entity;
      ConvertFrom(entity, memberList[i].GetMemberInfo().entity);

      add_list_.push_back(entity);

      mate::Handle<ConferenceUserBinding> new_user =
          ConferenceUserBinding::Create(isolate(), memberList[i],
                                        stats_pending_requests_);
      v8::Global<v8::Value> v8_new_user;
      v8_new_user.Reset(isolate(), new_user.ToV8());

      user_list_.emplace(entity, new_user);
      v8_user_list_.emplace(entity, std::move(v8_new_user));
    }
  } else {
    if (newMemberList.Size() > 0) {
      add_list_.clear();

      for (i = 0; i < newMemberList.Size(); i++) {
        std::string entity;
        ConvertFrom(entity, newMemberList[i].GetMemberInfo().entity);
        yealink::RoomMember member = newMemberList[i];

        // v8::HandleScope handle_scope(isolate());
        mate::Handle<ConferenceUserBinding> new_user =
            ConferenceUserBinding::Create(isolate(), member,
                                          stats_pending_requests_);
        v8::Global<v8::Value> v8_new_user;
        v8_new_user.Reset(isolate(), new_user.ToV8());

        user_list_.emplace(entity, new_user);
        v8_user_list_.emplace(entity, std::move(v8_new_user));

        add_list_.push_back(entity);
      }
    }

    if (modifyMemberList.Size() > 0) {
      update_list_.clear();

      for (i = 0; i < modifyMemberList.Size(); i++) {
        std::string entity;
        ConvertFrom(entity, modifyMemberList[i].GetMemberInfo().entity);

        update_list_.push_back(entity);
      }
    }

    if (deleteMemberList.Size() > 0) {
      delete_list_.clear();

      for (i = 0; i < deleteMemberList.Size(); i++) {
        std::string entity;
        ConvertFrom(entity, deleteMemberList[i].GetMemberInfo().entity);

        auto iter = user_list_.find(entity);

        if (iter != user_list_.end()) {
          user_list_.erase(entity);
          v8_user_list_.erase(entity);

          delete_list_.push_back(entity);
        }
      }
    }
  }
}

ConferenceUsersBinding::ConferenceUsersBinding(
    v8::Isolate* isolate,
    yealink::RoomController* controller)
    : weak_factory_(this), stats_pending_requests_(nullptr) {
  Init(isolate);
  room_controller_ = controller;
}
ConferenceUsersBinding::ConferenceUsersBinding(v8::Isolate* isolate,
                                               v8::Local<v8::Object> wrapper)
    : weak_factory_(this), stats_pending_requests_(nullptr) {}
ConferenceUsersBinding::~ConferenceUsersBinding() = default;

v8::Local<v8::Value> ConferenceUsersBinding::CurrentUser() {
  DCHECK(current_user_.get());

  if (v8_current_user_.IsEmpty()) {
    v8_current_user_.Reset(isolate(), current_user_.ToV8());
  }
  return v8::Local<v8::Value>::New(isolate(), v8_current_user_);
}

std::vector<v8::Local<v8::Value>> ConferenceUsersBinding::UserList() {
  std::vector<v8::Local<v8::Value>> userlist;

  auto iter = v8_user_list_.begin();

  while (iter != v8_user_list_.end()) {
    userlist.push_back(v8::Local<v8::Value>::New(isolate(), iter->second));
    ++iter;
  }

  return userlist;
}

v8::Local<v8::Promise> ConferenceUsersBinding::Invite(mate::Arguments* args) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  std::string uri;

  if (!args->GetNext(&uri)) {
    args->ThrowError("uri is required");
  }

  if (room_controller_) {
    room_controller_->GetMemberManager().InviteUser(uri.c_str());
  }

  std::move(promise).Resolve();

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

  if (room_controller_) {
    room_controller_->GetMemberManager().InviteUserWithUuid(uri.c_str(),
                                                            uid.c_str());
  }

  std::move(promise).Resolve();

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
  yealink::Array<yealink::SStringA> params;

  if (room_controller_) {
    ConvertTo(uri, params);
    room_controller_->GetMemberManager().InviteUserList(params);
  }

  std::move(promise).Resolve();

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
  yealink::Array<RoomMember> params;  // todo get member control

  for (int i = 0; i < (int)entities.size(); i++) {
    auto iter = user_list_.find(entities[i]);

    if (iter != user_list_.end()) {
      params.Append(iter->second->GetUserController());
    }
  }

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
  std::move(promise).Resolve();

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
