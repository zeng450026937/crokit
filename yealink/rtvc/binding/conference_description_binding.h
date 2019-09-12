#ifndef YEALINK_RTVC_BINDING_CONFERENCE_DESCRIPTION_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_DESCRIPTION_BINDING_H_

#include <unordered_map>
#include "yealink/libvc/include/room/room_controller.h"
#include "yealink/libvc/include/room/room_data.h"
#include "yealink/libvc/include/room/room_description_component.h"
#include "yealink/libvc/include/room/room_observer.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/api/conference_desc.h"
#include "yealink/rtvc/binding/promise.h"

namespace yealink {

namespace rtvc {

class ConferenceDescriptionBinding
    : public mate::Wrappable<ConferenceDescriptionBinding> {
 public:
  static mate::Handle<ConferenceDescriptionBinding> Create(
      v8::Isolate* isolate,
      yealink::RoomController* controller);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateRoomController(RoomController* handler);
  void UpdatePendingHandler(std::unordered_map<int64_t, Promise>* handler);

 protected:
  ConferenceDescriptionBinding(v8::Isolate* isolate,
                               v8::Local<v8::Object> wrapper);
  ConferenceDescriptionBinding(v8::Isolate* isolate,
                               yealink::RoomController* controller);
  ~ConferenceDescriptionBinding() override;

  std::string subject();
  int64_t startTime();
  DescBanner banner();
  DescDefaultRtmp defaultRtmp();
  DescProfile profile();
  std::string recordId();
  std::vector<DescConfUriInfo> confUris();
  DescOrganizerInfo organizer();
  std::string conferenceId();
  std::string conferenceNumber();
  DescConferenceType conferenceType();
  DescNumberType conferenceNumberType();
  int64_t bookStartTime();
  int64_t bookExpiryTime();
  std::string presenterPin();
  std::string attendeePin();
  uint32_t maximumUserCount();
  DescAdmissionPolicy admissionPolicy();
  bool lobbyCapable();
  bool attendeeByPass();
  DescAutoPromote autoPromote();
  std::string serverMode();
  bool interactiveBroadcastEnabled();
  std::string enterpriseId();
  bool videoEnable();
  bool ipcallEnable();
  bool webrtcEnable();
  DescRecordType recordServerType();
  DescRecordPrivilege recordPrivilege();
  std::string confInfoUrl();

  DescDefaultRtmp GetDefaultRtmp();
  DescGetLockInfo GetLock();
  v8::Local<v8::Promise> SetLock(DescSetLockInfo params);
  v8::Local<v8::Promise> GetShareInfo(mate::Arguments* args);

 private:
  void OnCommandCompeleted(Promise promise);
  void DoSetLock(DescSetLockInfo params);
  void DoGetShareInfo(std::string lang);

 private:
  RoomController* room_controller_;
  base::WeakPtrFactory<ConferenceDescriptionBinding> weak_factory_;
  std::unordered_map<int64_t, Promise>* pending_requests_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_DESCRIPTION_BINDING_H_
