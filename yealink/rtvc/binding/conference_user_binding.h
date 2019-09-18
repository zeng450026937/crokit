#ifndef YEALINK_RTVC_BINDING_CONFERENCE_USER_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_USER_BINDING_H_

#include <unordered_map>
#include "yealink/libvc/include/room/room_controller.h"
#include "yealink/libvc/include/room/room_member.h"
#include "yealink/libvc/include/room/room_member_manager.h"
#include "yealink/libvc/include/room/room_observer.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/api/conference_user.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/binding/trackable_object.h"

namespace yealink {

namespace rtvc {

class ConferenceUserBinding
    : public mate::TrackableObject<ConferenceUserBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ConferenceUserBinding> Create(
      v8::Isolate* isolate,
      yealink::RoomMember& controller,
      std::unordered_map<std::string, Promise>* handler);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateUserController(RoomMember& handler);
  RoomMember GetUserController();
  void UpdateStatsPendingHandler(
      std::unordered_map<std::string, Promise>* handler);

 protected:
  ConferenceUserBinding(v8::Isolate* isolate,
                        yealink::RoomMember& controller,
                        std::unordered_map<std::string, Promise>* handler);
  ConferenceUserBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~ConferenceUserBinding() override;

  std::string entity();
  std::string displayText();
  std::string displayNumber();
  std::string displayTextPinyin();
  std::string uid();
  UserProtocolType protocol();
  std::string mediumServerType();
  std::string ip();
  std::string phone();
  std::string requestUri();
  std::string userAgent();
  UserRolesInfo roles();
  std::vector<UserEndpointInfo> endpoint();

  bool IsCurrentUser();
  bool IsRtmp();
  bool IsSIP();
  bool IsOrganizer();
  bool IsPresenter();
  bool IsAttendee();
  bool IsCastViewer();
  bool IsDemonstrator();
  bool IsPresenterDemonstrator();
  bool IsOnHold();
  bool IsSharing();
  bool IsFocus();
  bool HasFECC();
  bool IsConnected();

  UserMediaFilterInfo GetAudioFilter();
  UserMediaFilterInfo GetVideoFilter();
  v8::Local<v8::Promise> GetStats();

  v8::Local<v8::Promise> SetAudioIngressFilter(bool isOpen);
  v8::Local<v8::Promise> SetAudioEgressFilter(bool isOpen);
  v8::Local<v8::Promise> SetVideoIngressFilter(bool isOpen);
  v8::Local<v8::Promise> SetPermission(UserPermissionType params);
  v8::Local<v8::Promise> SetDemonstrator(UserDemoStateType params);
  v8::Local<v8::Promise> SetPresenterDemonstrator(
      PresenterDemoStateType params);

  v8::Local<v8::Promise> Hold();
  v8::Local<v8::Promise> UnHold();
  v8::Local<v8::Promise> Kick();
  v8::Local<v8::Promise> SetDisplayName(mate::Arguments* args);
  v8::Local<v8::Promise> SetFocus(bool isFocus);

 private:
  void DoGetStats();
  void DoSetAudioIngressFilter(bool isOpen);
  void DoSetAudioEgressFilter(bool isOpen);
  void DoSetVideoIngressFilter(bool isOpen);
  void DoSetPermission(UserPermissionType params);
  void DoSetDemonstrator(UserDemoStateType params);
  void DoSetPresenterDemonstrator(PresenterDemoStateType params);
  void DoHold();
  void DoUnHold();
  void DoKick();
  void DoSetDisplayName(std::string name);
  void DoSetFocus(bool isFocus);
  void OnCommandCompeleted(Promise promise);

 private:
  RoomMember user_controller_;
  base::WeakPtrFactory<ConferenceUserBinding> weak_factory_;
  std::unordered_map<std::string, Promise>* stats_pending_requests_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_USER_BINDING_H_
