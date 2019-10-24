#ifndef YEALINK_RTVC_BINDING_CONFERENCE_MESSAGE_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_MESSAGE_BINDING_H_

#include <unordered_map>
#include "yealink/libvc/include/chat/chat_manager.h"
#include "yealink/libvc/include/chat/chat_message_item.h"
#include "yealink/libvc/include/chat/chat_observer.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/binding/trackable_object.h"

namespace rtvc {

class ConferenceMessageBinding
    : public mate::TrackableObject<ConferenceMessageBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ConferenceMessageBinding> Create(
      v8::Isolate* isolate,
      yealink::ChatMessageItem& controller);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateMessageController(yealink::ChatMessageItem& handler);
  yealink::ChatMessageItem GetMessageItem();

 protected:
  ConferenceMessageBinding(v8::Isolate* isolate,
                           yealink::ChatMessageItem& controller);
  ConferenceMessageBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~ConferenceMessageBinding() override;

  bool isPrivate();
  bool isRead();
  int32_t bizCode();
  int64_t index();
  int64_t timestamp();
  std::string text();
  std::string status();
  std::string senderEntity();
  std::string senderName();
  std::string direction();

  v8::Local<v8::Promise> SetStatus(bool isRead);

 private:
  yealink::ChatMessageItem message_controller_;
  base::WeakPtrFactory<ConferenceMessageBinding> weak_factory_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_MESSAGE_BINDING_H_
