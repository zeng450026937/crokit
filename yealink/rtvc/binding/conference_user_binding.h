#ifndef YEALINK_RTVC_BINDING_CONFERENCE_USER_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_USER_BINDING_H_

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

class ConferenceUserBinding : public mate::EventEmitter<ConferenceUserBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ConferenceUserBinding> Create(
      v8::Isolate* isolate,
      yealink::RoomMember* controller);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateUserController(RoomMember* handler);

 protected:
  ConferenceUserBinding(v8::Isolate* isolate, yealink::RoomMember* controller);
  ConferenceUserBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~ConferenceUserBinding() override;

  v8::Local<v8::Value> Entity();
  v8::Local<v8::Value> DisplayText();
  v8::Local<v8::Value> DisplayNumber();
  v8::Local<v8::Value> DisplayTextPinyin();
  v8::Local<v8::Value> Uid();
  v8::Local<v8::Value> Protocol();
  v8::Local<v8::Value> MediumServerType();
  v8::Local<v8::Value> Ip();
  v8::Local<v8::Value> Phone();
  v8::Local<v8::Value> RequestUri();
  v8::Local<v8::Value> UserAgent();
  v8::Local<v8::Value> Roles();
  v8::Local<v8::Value> Endpoint();

  v8::Local<v8::Value> IsCurrentUser();
  v8::Local<v8::Value> IsRtmp();
  v8::Local<v8::Value> IsSIP();
  v8::Local<v8::Value> IsOrganizer();
  v8::Local<v8::Value> IsPresenter();
  v8::Local<v8::Value> IsAttendee();
  v8::Local<v8::Value> IsCastViewer();
  v8::Local<v8::Value> IsDemonstrator();
  v8::Local<v8::Value> IsPresenterDemonstrator();
  v8::Local<v8::Value> IsOnHold();
  v8::Local<v8::Value> IsSharing();
  v8::Local<v8::Value> IsFocus();
  v8::Local<v8::Value> hasFECC();

  v8::Local<v8::Value> GetAudioFilter();
  v8::Local<v8::Value> GetVideoFilter();
  v8::Local<v8::Promise> GetStats();

  v8::Local<v8::Promise> SetAudioFilter(UserMediafilterType params);
  v8::Local<v8::Promise> SetVideoFilter(UserMediafilterType params);
  v8::Local<v8::Promise> SetPermission(UserPermissionType params);
  v8::Local<v8::Promise> SetDemonstrator(UserDemoStateType params);
  v8::Local<v8::Promise> SetPresenterDemonstrator(
      PresenterDemoStateType params);

  v8::Local<v8::Promise> Hold();
  v8::Local<v8::Promise> UnHold();
  v8::Local<v8::Promise> Kick();
  v8::Local<v8::Promise> SetDisplayName(mate::Arguments* args);

 private:
  void DoGetStats();
  void DoSetAudioFilter(UserMediafilterType params);
  void DoSetVideoFilter(UserMediafilterType params);
  void DoSetPermission(UserPermissionType params);
  void DoSetDemonstrator(UserDemoStateType params);
  void DoSetPresenterDemonstrator(PresenterDemoStateType params);
  void DoHold();
  void DoUnHold();
  void DoKick();
  void DoSetDisplayName(std::string name);
  void OnCommandCompeleted(Promise promise);

 private:
  RoomMember* user_controller_;
  base::WeakPtrFactory<ConferenceUserBinding> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_USER_BINDING_H_
