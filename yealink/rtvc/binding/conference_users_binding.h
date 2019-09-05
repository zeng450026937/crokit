#ifndef YEALINK_RTVC_BINDING_CONFERENCE_USERS_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_USERS_BINDING_H_

#include "yealink/libvc/include/room/room_controller.h"
#include "yealink/libvc/include/room/room_member.h"
#include "yealink/libvc/include/room/room_member_manager.h"
#include "yealink/libvc/include/room/room_observer.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/conference_user.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"

namespace yealink {

namespace rtvc {

class ConferenceUsersBinding
    : public mate::EventEmitter<ConferenceUsersBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ConferenceUsersBinding> Create(
      v8::Isolate* isolate,
      yealink::RoomController* controller);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateRoomController(RoomController* handler);

 protected:
  ConferenceUsersBinding(v8::Isolate* isolate,
                         yealink::RoomController* controller);
  ConferenceUsersBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~ConferenceUsersBinding() override;

  v8::Local<v8::Value> CurrentUser();

  v8::Local<v8::Promise> Invite(mate::Arguments* args);
  v8::Local<v8::Promise> InviteThird(std::string uri, std::string uid);
  v8::Local<v8::Promise> InviteBatch(std::vector<std::string> uri);
  v8::Local<v8::Promise> Allow(std::vector<std::string> entities, bool granted);

 private:
  void OnCommandCompeleted(Promise promise);
  void DoInvite(std::string uri);
  void DoInviteThird(std::string uri, std::string uid);
  void DoInviteBatch(std::vector<std::string> uri);
  void DoAllow(std::vector<std::string> entities, bool granted);

  RoomController* room_controller_;

  base::WeakPtrFactory<ConferenceUsersBinding> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_USER_BINDING_H_
