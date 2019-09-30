#include "yealink/rtvc/binding/conference_dialog_binding.h"

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

namespace rtvc {

namespace {
static std::unordered_map<std::string, int32_t> g_uid_map_;
}  // namespace

// static
mate::WrappableBase* ConferenceDialogBinding::New(mate::Arguments* args) {
  return new ConferenceDialogBinding(args->isolate(), args->GetThis());
}

mate::Handle<ConferenceDialogBinding> ConferenceDialogBinding::Create(
    v8::Isolate* isolate,
    yealink::ChatDialog& controller) {
  auto iter = g_uid_map_.find(
      controller.GetTargetMember().GetMemberInfo().entity.ConstData());

  if (iter == g_uid_map_.end()) {
    return mate::CreateHandle(isolate,
                              new ConferenceDialogBinding(isolate, controller));
  }

  int32_t weak_map_id = iter->second;

  auto binding = mate::TrackableObject<ConferenceDialogBinding>::FromWeakMapID(
      isolate, weak_map_id);

  if (binding) {
    binding->UpdateUserController(controller);
    return mate::CreateHandle(isolate, binding);
  }

  return mate::CreateHandle(isolate,
                            new ConferenceDialogBinding(isolate, controller));
}

// static
void ConferenceDialogBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "conferenceDialog"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("entity", &ConferenceDialogBinding::entity)
      .SetProperty("isPrivate", &ConferenceDialogBinding::isPrivate)
      .SetProperty("messages", &ConferenceDialogBinding::messages)
      .SetProperty("unreadCount", &ConferenceDialogBinding::unreadCount)
      .SetMethod("clearUnread", &ConferenceDialogBinding::ClearUnread);
}

void ConferenceDialogBinding::UpdateUserController(ChatDialog& handler) {
  dialog_controller_ = handler;
}

ConferenceDialogBinding::ConferenceDialogBinding(
    v8::Isolate* isolate,
    yealink::ChatDialog& controller)
    : weak_factory_(this) {
  Init(isolate);
  dialog_controller_ = controller;

  g_uid_map_.emplace(
      dialog_controller_.GetTargetMember().GetMemberInfo().entity.ConstData(),
      weak_map_id_);
}
ConferenceDialogBinding::ConferenceDialogBinding(v8::Isolate* isolate,
                                                 v8::Local<v8::Object> wrapper)
    : weak_factory_(this) {
  InitWith(isolate, wrapper);
}
ConferenceDialogBinding::~ConferenceDialogBinding() {
  LOG(INFO) << __FUNCTIONW__;
  g_uid_map_.erase(
      dialog_controller_.GetTargetMember().GetMemberInfo().entity.ConstData());
};

std::string ConferenceDialogBinding::entity() {
  yealink::RoomMember member = dialog_controller_.GetTargetMember();

  return std::string(member.GetUserEntity().ConstData());
}

bool ConferenceDialogBinding::isPrivate() {
  return dialog_controller_.IsPrivate();
}

int64_t ConferenceDialogBinding::unreadCount() {
  return dialog_controller_.GetUnreadCount();
}

std::vector<v8::Local<v8::Value>> ConferenceDialogBinding::messages() {
  Array<ChatMessageItem> items;
  std::vector<v8::Local<v8::Value>> message_list;
  size_t i = 0;

  items = dialog_controller_.GetMessageList();

  for (i = 0; i < items.Size(); i++) {
    mate::Handle<ConferenceMessageBinding> history_message =
        ConferenceMessageBinding::Create(isolate(), items[i]);
    v8::Global<v8::Value> v8_history_message;
    v8_history_message.Reset(isolate(), history_message.ToV8());

    message_list.push_back(
        v8::Local<v8::Value>::New(isolate(), v8_history_message));
  }

  return message_list;
}

bool ConferenceDialogBinding::ClearUnread() {
  return dialog_controller_.ClearUnread();
}

}  // namespace rtvc

}  // namespace yealink
