#ifndef YEALINK_RTVC_BINDING_CONFERENCE_DESCRIPTION_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_DESCRIPTION_BINDING_H_

#include "yealink/libvc/include/room/room_controller.h"
#include "yealink/libvc/include/room/room_data.h"
#include "yealink/libvc/include/room/room_description_component.h"
#include "yealink/libvc/include/room/room_observer.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/api/conference_desc.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"
namespace yealink {

namespace rtvc {

class ConferenceDescriptionBinding
    : public mate::Wrappable<ConferenceDescriptionBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ConferenceDescriptionBinding> Create(
      v8::Isolate* isolate,
      yealink::RoomController* controller);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateRoomController(RoomController* handler);

 protected:
  ConferenceDescriptionBinding(v8::Isolate* isolate,
                               v8::Local<v8::Object> wrapper);
  ConferenceDescriptionBinding(v8::Isolate* isolate,
                               yealink::RoomController* controller);
  ~ConferenceDescriptionBinding() override;

  v8::Local<v8::Value> Subject();
  v8::Local<v8::Value> StartTime();
  v8::Local<v8::Value> Banner();
  v8::Local<v8::Value> DefaultRtmp();
  v8::Local<v8::Value> Profile();
  v8::Local<v8::Value> RecordId();
  v8::Local<v8::Value> ConfUris();
  v8::Local<v8::Value> Organizer();
  v8::Local<v8::Value> ConferenceId();
  v8::Local<v8::Value> ConferenceNumber();
  v8::Local<v8::Value> ConferenceType();
  v8::Local<v8::Value> ConferenceNumberType();
  v8::Local<v8::Value> BookStartTime();
  v8::Local<v8::Value> BookExpiryTime();
  v8::Local<v8::Value> PresenterPin();
  v8::Local<v8::Value> AttendeePin();
  v8::Local<v8::Value> MaximumUserCount();
  v8::Local<v8::Value> AdmissionPolicy();
  v8::Local<v8::Value> LobbyCapable();
  v8::Local<v8::Value> AttendeeByPass();
  v8::Local<v8::Value> AutoPromote();
  v8::Local<v8::Value> ServerMode();
  v8::Local<v8::Value> InteractiveBroadcastEnabled();
  v8::Local<v8::Value> EnterpriseId();
  v8::Local<v8::Value> VideoEnable();
  v8::Local<v8::Value> IpcallEnable();
  v8::Local<v8::Value> WebrtcEnable();
  v8::Local<v8::Value> RecordServerType();
  v8::Local<v8::Value> RecordPrivilege();
  v8::Local<v8::Value> ConfInfoUrl();

  v8::Local<v8::Value> GetDefaultRtmp();
  v8::Local<v8::Value> GetLock();
  v8::Local<v8::Promise> SetLock(DescSetLockInfo params);
  v8::Local<v8::Promise> GetShareInfo(mate::Arguments* args);

 private:
  void OnCommandCompeleted(Promise promise);
  void DoSetLock(DescSetLockInfo params);
  void DoGetShareInfo(std::string lang);

 private:
  RoomController* room_controller_;
  base::WeakPtrFactory<ConferenceDescriptionBinding> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_DESCRIPTION_BINDING_H_
