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
      .SetProperty("currentUser", &ConferenceUsersBinding::currentUser)
      .SetProperty("userList", &ConferenceUsersBinding::userList)
      .SetProperty("addedUser", &ConferenceUsersBinding::addedUser)
      .SetProperty("deletedUser", &ConferenceUsersBinding::deletedUser)
      .SetProperty("updatedUser", &ConferenceUsersBinding::updatedUser)
      .SetProperty("presenters", &ConferenceUsersBinding::presenters)
      .SetProperty("attendees", &ConferenceUsersBinding::attendees)
      .SetProperty("onHoldUsers", &ConferenceUsersBinding::onHoldUsers)
      .SetProperty("demonstrators", &ConferenceUsersBinding::demonstrators)
      .SetProperty("castviewers", &ConferenceUsersBinding::castviewers)
      .SetMethod("invite", &ConferenceUsersBinding::Invite)
      .SetMethod("inviteThird", &ConferenceUsersBinding::InviteThird)
      .SetMethod("inviteBatch", &ConferenceUsersBinding::InviteBatch)
      .SetMethod("allow", &ConferenceUsersBinding::Allow)
      .SetMethod("handUp", &ConferenceUsersBinding::HandUp);
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

  v8_added_list_.clear();
  v8_updated_list_.clear();
  v8_deleted_list_.clear();

  if (force == true) {
    Array<RoomMember> memberList =
        room_controller_->GetMemberManager().GetMemberList();
    RoomMember owner = room_controller_->GetMemberManager().GetOwner();

    // v8::HandleScope handle_scope(isolate());
    for (i = 0; i < memberList.Size(); i++) {
      std::string entity;
      ConvertFrom(entity, memberList[i].GetMemberInfo().entity);

      mate::Handle<ConferenceUserBinding> new_user =
          ConferenceUserBinding::Create(isolate(), memberList[i],
                                        stats_pending_requests_);
      v8::Global<v8::Value> v8_new_user;
      v8_new_user.Reset(isolate(), new_user.ToV8());

      user_list_.emplace(entity, new_user);
      v8_user_list_.emplace(entity, std::move(v8_new_user));

      v8::Global<v8::Value> v8_add_user;
      v8_add_user.Reset(isolate(), new_user.ToV8());
      v8_added_list_.emplace(entity, std::move(v8_add_user));
    }
  } else {
    if (newMemberList.Size() > 0) {
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

        v8::Global<v8::Value> v8_add_user;
        v8_add_user.Reset(isolate(), new_user.ToV8());
        v8_added_list_.emplace(entity, std::move(v8_add_user));
      }
    }

    if (modifyMemberList.Size() > 0) {
      for (i = 0; i < modifyMemberList.Size(); i++) {
        std::string entity;
        yealink::RoomMember member = modifyMemberList[i];

        ConvertFrom(entity, modifyMemberList[i].GetMemberInfo().entity);

        mate::Handle<ConferenceUserBinding> update_user =
            ConferenceUserBinding::Create(isolate(), member,
                                          stats_pending_requests_);
        v8::Global<v8::Value> v8_update_user;
        v8_update_user.Reset(isolate(), update_user.ToV8());

        v8_updated_list_.emplace(entity, std::move(v8_update_user));
      }
    }

    if (deleteMemberList.Size() > 0) {
      for (i = 0; i < deleteMemberList.Size(); i++) {
        std::string entity;
        ConvertFrom(entity, deleteMemberList[i].GetMemberInfo().entity);

        yealink::RoomMember member = deleteMemberList[i];
        mate::Handle<ConferenceUserBinding> delete_user =
            ConferenceUserBinding::Create(isolate(), member,
                                          stats_pending_requests_);
        v8::Global<v8::Value> v8_delete_user;
        v8_delete_user.Reset(isolate(), delete_user.ToV8());
        v8_deleted_list_.emplace(entity, std::move(v8_delete_user));

        auto iter = user_list_.find(entity);

        if (iter != user_list_.end()) {
          user_list_.erase(entity);
          v8_user_list_.erase(entity);
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

v8::Local<v8::Value> ConferenceUsersBinding::currentUser() {
  std::string entity;
  v8::Global<v8::Value> value;

  if (room_controller_) {
    ConvertFrom(
        entity,
        room_controller_->GetMemberManager().GetOwner().GetMemberInfo().entity);
  }

  auto iter = v8_user_list_.find(entity);

  if (iter != v8_user_list_.end()) {
    return v8::Local<v8::Value>::New(isolate(), iter->second);
  }

  return v8::Local<v8::Value>::New(isolate(), value);
}

std::vector<v8::Local<v8::Value>> ConferenceUsersBinding::userList() {
  std::vector<v8::Local<v8::Value>> userlist;

  auto iter = v8_user_list_.begin();

  while (iter != v8_user_list_.end()) {
    userlist.push_back(v8::Local<v8::Value>::New(isolate(), iter->second));
    ++iter;
  }

  return userlist;
}

std::vector<v8::Local<v8::Value>> ConferenceUsersBinding::addedUser() {
  std::vector<v8::Local<v8::Value>> userlist;

  auto iter = v8_added_list_.begin();

  while (iter != v8_added_list_.end()) {
    userlist.push_back(v8::Local<v8::Value>::New(isolate(), iter->second));
    ++iter;
  }

  return userlist;
}

std::vector<v8::Local<v8::Value>> ConferenceUsersBinding::deletedUser() {
  std::vector<v8::Local<v8::Value>> userlist;

  auto iter = v8_deleted_list_.begin();

  while (iter != v8_deleted_list_.end()) {
    userlist.push_back(v8::Local<v8::Value>::New(isolate(), iter->second));
    ++iter;
  }

  return userlist;
}

std::vector<v8::Local<v8::Value>> ConferenceUsersBinding::updatedUser() {
  std::vector<v8::Local<v8::Value>> userlist;

  auto iter = v8_updated_list_.begin();

  while (iter != v8_updated_list_.end()) {
    userlist.push_back(v8::Local<v8::Value>::New(isolate(), iter->second));
    ++iter;
  }

  return userlist;
}

std::vector<v8::Local<v8::Value>> ConferenceUsersBinding::presenters() {
  std::vector<v8::Local<v8::Value>> userlist;

  auto iter = user_list_.begin();

  while (iter != user_list_.end()) {
    mate::Handle<ConferenceUserBinding> user = iter->second;

    if (user->IsPresenter() == true && user->IsOnHold() == false) {
      auto v8_iter = v8_user_list_.find(user->entity());

      if (v8_iter != v8_user_list_.end()) {
        userlist.push_back(
            v8::Local<v8::Value>::New(isolate(), v8_iter->second));
      }
    }
    ++iter;
  }

  return userlist;
}

std::vector<v8::Local<v8::Value>> ConferenceUsersBinding::attendees() {
  std::vector<v8::Local<v8::Value>> userlist;

  auto iter = user_list_.begin();

  while (iter != user_list_.end()) {
    mate::Handle<ConferenceUserBinding> user = iter->second;

    if (user->IsAttendee() == true && user->IsOnHold() == false) {
      auto v8_iter = v8_user_list_.find(user->entity());

      if (v8_iter != v8_user_list_.end()) {
        userlist.push_back(
            v8::Local<v8::Value>::New(isolate(), v8_iter->second));
      }
    }
    ++iter;
  }

  return userlist;
}

std::vector<v8::Local<v8::Value>> ConferenceUsersBinding::onHoldUsers() {
  std::vector<v8::Local<v8::Value>> userlist;

  auto iter = user_list_.begin();

  while (iter != user_list_.end()) {
    mate::Handle<ConferenceUserBinding> user = iter->second;

    if (user->IsOnHold() == true) {
      auto v8_iter = v8_user_list_.find(user->entity());

      if (v8_iter != v8_user_list_.end()) {
        userlist.push_back(
            v8::Local<v8::Value>::New(isolate(), v8_iter->second));
      }
    }
    ++iter;
  }

  return userlist;
}

std::vector<v8::Local<v8::Value>> ConferenceUsersBinding::demonstrators() {
  std::vector<v8::Local<v8::Value>> userlist;

  auto iter = user_list_.begin();

  while (iter != user_list_.end()) {
    mate::Handle<ConferenceUserBinding> user = iter->second;

    if (user->IsDemonstrator() == true && user->IsOnHold() == false) {
      auto v8_iter = v8_user_list_.find(user->entity());

      if (v8_iter != v8_user_list_.end()) {
        userlist.push_back(
            v8::Local<v8::Value>::New(isolate(), v8_iter->second));
      }
    }
    ++iter;
  }

  return userlist;
}

std::vector<v8::Local<v8::Value>> ConferenceUsersBinding::castviewers() {
  std::vector<v8::Local<v8::Value>> userlist;

  auto iter = user_list_.begin();

  while (iter != user_list_.end()) {
    mate::Handle<ConferenceUserBinding> user = iter->second;

    if (user->IsCastViewer() == true && user->IsOnHold() == false) {
      auto v8_iter = v8_user_list_.find(user->entity());

      if (v8_iter != v8_user_list_.end()) {
        userlist.push_back(
            v8::Local<v8::Value>::New(isolate(), v8_iter->second));
      }
    }
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
  yealink::Array<RoomMember> params;

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

v8::Local<v8::Promise> ConferenceUsersBinding::HandUp(bool agreed) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  if (room_controller_) {
    if (agreed == true) {
      // do nothing, server not support
      std::move(promise).Resolve();
    } else {
      HttpResponseInfo* response = new HttpResponseInfo();
      base::PostTaskAndReply(
          FROM_HERE,
          base::BindOnce(&ConferenceUsersBinding::DoHandUpAll,
                         base::Unretained(this), response),
          base::BindOnce(&ConferenceUsersBinding::OnProcessCompeleted,
                         weak_factory_.GetWeakPtr(), std::move(promise),
                         response));
    }
  } else {
    std::move(promise).Reject();
  }

  return handle;
}

void ConferenceUsersBinding::DoHandUpAll(HttpResponseInfo* response) {
  if (response != nullptr && room_controller_ != nullptr)
    ConvertFrom(*response,
                room_controller_->GetMemberManager().RejectAllHandUp());
}

void ConferenceUsersBinding::OnProcessCompeleted(Promise promise,
                                                 HttpResponseInfo* response) {
  if (response != nullptr) {
    std::move(promise).Resolve(*response);
    delete response;
  } else {
    std::move(promise).Reject();
  }
}

void ConferenceUsersBinding::OnCommandCompeleted(Promise promise) {
  std::move(promise).Resolve(true);
}

}  // namespace rtvc

}  // namespace yealink
