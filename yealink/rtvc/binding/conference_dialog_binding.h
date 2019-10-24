#ifndef YEALINK_RTVC_BINDING_CONFERENCE_DIALOG_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_DIALOG_BINDING_H_

#include <unordered_map>
#include "yealink/libvc/include/chat/chat_dialog.h"
#include "yealink/libvc/include/chat/chat_manager.h"
#include "yealink/libvc/include/chat/chat_message_item.h"
#include "yealink/libvc/include/chat/chat_observer.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/binding/conference_message_binding.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/binding/trackable_object.h"

namespace rtvc {

class ConferenceDialogBinding
    : public mate::TrackableObject<ConferenceDialogBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ConferenceDialogBinding> Create(
      v8::Isolate* isolate,
      yealink::ChatDialog& controller);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateDialogController(yealink::ChatDialog& handler);

 protected:
  ConferenceDialogBinding(v8::Isolate* isolate,
                          yealink::ChatDialog& controller);
  ConferenceDialogBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~ConferenceDialogBinding() override;

  std::string entity();
  bool isPrivate();
  int64_t unreadCount();
  std::vector<v8::Local<v8::Value>> messages();

  bool ClearUnread();

 private:
  yealink::ChatDialog dialog_controller_;
  base::WeakPtrFactory<ConferenceDialogBinding> weak_factory_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_DIALOG_BINDING_H_
