#ifndef YEALINK_RTVC_BINDING_CONFERENCE_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_BINDING_H_

#include <unordered_map>
#include "yealink/libvc/include/meeting/meeting_api.h"
#include "yealink/libvc/include/room/room_controller.h"
#include "yealink/libvc/include/room/room_data.h"
#include "yealink/libvc/include/room/room_member.h"
#include "yealink/libvc/include/room/room_observer.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/rtvc/api/channel.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/api/conference_state.h"
#include "yealink/rtvc/binding/conference_description_binding.h"
#include "yealink/rtvc/binding/conference_state_binding.h"
#include "yealink/rtvc/binding/conference_user_binding.h"
#include "yealink/rtvc/binding/conference_users_binding.h"
#include "yealink/rtvc/binding/conference_view_binding.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/binding/user_agent_binding.h"

namespace yealink {

namespace rtvc {

class ConferenceBinding : public mate::EventEmitter<ConferenceBinding>,
                          public yealink::RoomObserver {
 public:
  static mate::WrappableBase* New(mate::Handle<UserAgentBinding> user_agent,
                                  mate::Arguments* args);

  static mate::Handle<ConferenceBinding> Create(
      v8::Isolate* isolate,
      yealink::RoomController* controller);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void SetController(RoomController* controller);
  void SetController(std::unique_ptr<RoomController> controller);

 protected:
  friend class CallBinding;

  ConferenceBinding(v8::Isolate* isolate,
                    v8::Local<v8::Object> wrapper,
                    mate::Handle<UserAgentBinding> user_agent);
  ConferenceBinding(v8::Isolate* isolate, yealink::RoomController* controller);
  ~ConferenceBinding() override;

  void Connect(mate::Dictionary dict, mate::Arguments* args);
  void Disconnect(mate::Arguments* args);

  bool isInProgress();
  bool isEstablished();
  bool isEnded();
  bool isChatChannelSupported();
  bool isChatChannelEstablished();

  v8::Local<v8::Value> description();
  v8::Local<v8::Value> view();
  v8::Local<v8::Value> state();
  v8::Local<v8::Value> users();

  // room observer impl
  void OnConnectSuccess() override;
  void OnConnectFailure(const char* reason) override;
  void OnResponse(const yealink::ResponseResult& response) override;
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

 private:
  bool locally_generated_controller_ = true;
  std::unique_ptr<RoomController> controller_;
  std::string conversation_id_;

  v8::Global<v8::Value> v8_description_;
  mate::Handle<ConferenceDescriptionBinding> description_;

  v8::Global<v8::Value> v8_view_;
  mate::Handle<ConferenceViewBinding> view_;

  v8::Global<v8::Value> v8_state_;
  mate::Handle<ConferenceStateBinding> state_;

  v8::Global<v8::Value> v8_users_;
  mate::Handle<ConferenceUsersBinding> users_;

  base::WeakPtr<UserAgentBinding> user_agent_;
  base::WeakPtr<yealink::SIPClient> sip_client_;
  base::WeakPtrFactory<ConferenceBinding> weak_factory_;

  std::unordered_map<int64_t, Promise> pending_requests_;
  std::unordered_map<std::string, Promise> stats_pending_requests_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_BINDING_H_
