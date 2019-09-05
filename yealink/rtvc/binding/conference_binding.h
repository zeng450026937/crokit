#ifndef YEALINK_RTVC_BINDING_CONFERENCE_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_BINDING_H_

#include "yealink/libvc/include/room/room_controller.h"
#include "yealink/libvc/include/room/room_data.h"
#include "yealink/libvc/include/room/room_member.h"
#include "yealink/libvc/include/room/room_observer.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/api/conference_state.h"
#include "yealink/rtvc/binding/conference_description_binding.h"
#include "yealink/rtvc/binding/conference_state_binding.h"
#include "yealink/rtvc/binding/conference_user_binding.h"
#include "yealink/rtvc/binding/conference_users_binding.h"
#include "yealink/rtvc/binding/conference_view_binding.h"
#include "yealink/rtvc/binding/event_emitter.h"

namespace yealink {

namespace rtvc {

class ConferenceBinding : public mate::EventEmitter<ConferenceBinding>,
                          public yealink::RoomObserver {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ConferenceBinding> Create(
      v8::Isolate* isolate,
      yealink::RoomController* controller);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void SetController(RoomController* handler);

 protected:
  friend class CallBinding;

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
  void OnConnectSuccess() override;
  void OnConnectFailure(const char* reason) override;
  void OnResponse(const ResponseResult& response) override;
  void OnSubscriptionDisconnect() override;
  void OnConferenceDescriptionChange(
      const yealink::ConferenceDescription& desc) override;
  void OnConferenceStateChange(const yealink::ConferenceState& state) override;
  void OnConferenceViewChange(const yealink::ConferenceView& view) override;
  void OnUserChange(const Array<RoomMember>& newMemberList,
                    const Array<RoomMember>& modifyMemberList,
                    const Array<RoomMember>& deleteMemberList) override;
  void OnGetUserCallStats(const RoomMember& member,
                          const Array<yealink::UserMediaInfo>& info) override;
  void OnGetShareInfo(int64_t requestId, const char* shareInfo) override;

  v8::Local<v8::Value> Description();
  v8::Local<v8::Value> View();
  v8::Local<v8::Value> State();
  v8::Local<v8::Value> Users();

 private:
  RoomController* controller_;

  v8::Global<v8::Value> v8_description_;
  mate::Handle<ConferenceDescriptionBinding> description_;

  v8::Global<v8::Value> v8_view_;
  mate::Handle<ConferenceViewBinding> view_;

  v8::Global<v8::Value> v8_state_;
  mate::Handle<ConferenceStateBinding> state_;

  v8::Global<v8::Value> v8_users_;
  mate::Handle<ConferenceUsersBinding> users_;

  base::WeakPtrFactory<ConferenceBinding> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_BINDING_H_
