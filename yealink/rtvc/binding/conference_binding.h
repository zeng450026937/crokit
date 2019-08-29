#ifndef YEALINK_RTVC_BINDING_CONFERENCE_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_BINDING_H_

#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/rtvc/binding/event_emitter.h"

#include "yealink/libvc/include/room/room_controller.h"
#include "yealink/libvc/include/room/room_observer.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/api/conference_state.h"
#include "yealink/rtvc/binding/conference_state_binding.h"

namespace yealink {

namespace rtvc {

class ConferenceBinding : public mate::EventEmitter<ConferenceBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ConferenceBinding> Create(
      v8::Isolate* isolate,
      yealink::RoomController* controller);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateRoomController(RoomController* handler);

 protected:
  ConferenceBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ConferenceBinding(v8::Isolate* isolate, yealink::RoomController* controller);
  ~ConferenceBinding() override;

  void Connect();
  void Disconnect();

  bool isInProgress();
  bool isEstablished();
  bool isEnded();
  bool isChatChannelSupported();
  bool isChatChannelEstablished();

  // room observer impl
  // void OnConnectSuccess() override;
  // void OnConnectFailure(const char* reason) override;
  // void OnReceiveInviteMessage(const char* message) override;
  // void OnReceiveSubscriptionMessage(const char* message) override;
  // void OnResponse(const ResponseResult& response) override;
  // void OnSubscriptionDisconnect() override;
  // void OnUsersLoadAll(const Array<RoomMember>& memberList) override;
  // void OnUserChange(const Array<RoomMember>& newMemberList, const
  // Array<RoomMember>& modifyMemberList, const Array<RoomMember>&
  // deleteMemberList) override; void OnGetUserCallStats(const RoomMember&
  // member, const Array<UserMediaInfo>& info) override; void
  // OnGetShareInfo(int64_t requestId, const char* shareInfo) override;

  //v8::Local<v8::Value> State();

 private:
  //v8::Global<v8::Value> state_controller_;
  //mate::Handle<ConferenceStateBinding> state_;

  RoomController* room_controller_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_BINDING_H_
