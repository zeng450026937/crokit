#ifndef YEALINK_RTVC_BINDING_CONFERENCE_CHAT_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_CHAT_BINDING_H_

#include "yealink/libvc/include/chat/chat_dialog.h"
#include "yealink/libvc/include/chat/chat_manager.h"
#include "yealink/libvc/include/chat/chat_message_item.h"
#include "yealink/libvc/include/room/room_controller.h"
#include "yealink/libvc/include/room/room_observer.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/binding/conference_dialog_binding.h"
#include "yealink/rtvc/binding/conference_message_binding.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"

namespace rtvc {

class ConferenceChatBinding : public mate::EventEmitter<ConferenceChatBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ConferenceChatBinding> Create(
      v8::Isolate* isolate,
      yealink::RoomController* controller);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateRoomController(yealink::RoomController* handler);
  void UpdateChatController(yealink::ChatManager* handler);

 protected:
  ConferenceChatBinding(v8::Isolate* isolate,
                        yealink::RoomController* controller);
  ConferenceChatBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~ConferenceChatBinding() override;

  v8::Local<v8::Promise> SendChatMessage(std::string message,
                                         std::vector<std::string> entities);
  v8::Local<v8::Promise> RetrySendChatMessage(
      mate::Handle<ConferenceMessageBinding> handler);

  v8::Local<v8::Value> publicDialog();
  std::vector<v8::Local<v8::Value>> dialogList();

 private:
  void DoSendChatMessage(bool isSingle,
                         std::string message,
                         yealink::RoomMember member,
                         yealink::ChatMessageItem* item);
  void OnMessageCompeleted(Promise promise, yealink::ChatMessageItem* item);

  void DoRetrySendMessage(mate::Handle<ConferenceMessageBinding> handler,
                          bool* res);
  void OnRetryMessageCompeleted(Promise promise, bool* res);

  yealink::RoomController* room_controller_;
  yealink::ChatManager* chat_controller_;
  base::WeakPtrFactory<ConferenceChatBinding> weak_factory_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_CHAT_BINDING_H_
