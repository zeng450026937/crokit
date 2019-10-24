#include "yealink/rtvc/binding/conference_message_binding.h"

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace rtvc {

namespace {
static std::unordered_map<int64_t, int32_t> g_uid_map_;
}  // namespace

// static
mate::WrappableBase* ConferenceMessageBinding::New(mate::Arguments* args) {
  return new ConferenceMessageBinding(args->isolate(), args->GetThis());
}

mate::Handle<ConferenceMessageBinding> ConferenceMessageBinding::Create(
    v8::Isolate* isolate,
    yealink::ChatMessageItem& controller) {
  auto iter = g_uid_map_.find(controller.GetEntity());

  if (iter == g_uid_map_.end()) {
    return mate::CreateHandle(
        isolate, new ConferenceMessageBinding(isolate, controller));
  }

  int32_t weak_map_id = iter->second;

  auto binding = mate::TrackableObject<ConferenceMessageBinding>::FromWeakMapID(
      isolate, weak_map_id);

  if (binding) {
    binding->UpdateMessageController(controller);
    return mate::CreateHandle(isolate, binding);
  }

  return mate::CreateHandle(isolate,
                            new ConferenceMessageBinding(isolate, controller));
}

// static
void ConferenceMessageBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "conferenceMessage"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("isPrivate", &ConferenceMessageBinding::isPrivate)
      .SetProperty("isRead", &ConferenceMessageBinding::isRead)
      .SetProperty("bizCode", &ConferenceMessageBinding::bizCode)
      .SetProperty("index", &ConferenceMessageBinding::index)
      .SetProperty("timestamp", &ConferenceMessageBinding::timestamp)
      .SetProperty("text", &ConferenceMessageBinding::text)
      .SetProperty("status", &ConferenceMessageBinding::status)
      .SetProperty("senderEntity", &ConferenceMessageBinding::senderEntity)
      .SetProperty("senderName", &ConferenceMessageBinding::senderName)
      .SetProperty("direction", &ConferenceMessageBinding::direction)
      .SetMethod("setStatus", &ConferenceMessageBinding::SetStatus);
}

void ConferenceMessageBinding::UpdateMessageController(
    yealink::ChatMessageItem& handler) {
  message_controller_ = handler;
}

yealink::ChatMessageItem ConferenceMessageBinding::GetMessageItem() {
  return message_controller_;
}

ConferenceMessageBinding::ConferenceMessageBinding(
    v8::Isolate* isolate,
    yealink::ChatMessageItem& controller)
    : weak_factory_(this) {
  Init(isolate);
  message_controller_ = controller;

  g_uid_map_.emplace(message_controller_.GetEntity(), weak_map_id_);
}
ConferenceMessageBinding::ConferenceMessageBinding(
    v8::Isolate* isolate,
    v8::Local<v8::Object> wrapper)
    : weak_factory_(this) {
  InitWith(isolate, wrapper);
}
ConferenceMessageBinding::~ConferenceMessageBinding() {
  LOG(INFO) << __FUNCTIONW__;
  g_uid_map_.erase(message_controller_.GetEntity());
};

bool ConferenceMessageBinding::isPrivate() {
  return message_controller_.IsPrivate();
}
bool ConferenceMessageBinding::isRead() {
  return message_controller_.IsRead();
}
int32_t ConferenceMessageBinding::bizCode() {
  return message_controller_.GetLastBizCode();
}
int64_t ConferenceMessageBinding::index() {
  return message_controller_.GetEntity();
}
int64_t ConferenceMessageBinding::timestamp() {
  return message_controller_.GetTimestamp();
}
std::string ConferenceMessageBinding::text() {
  return std::string(message_controller_.GetContext());
}
std::string ConferenceMessageBinding::status() {
  yealink::ChatItemStatus status = message_controller_.GetStatus();

  if (status == yealink::ChatItemStatus::CHAT_ITEM_STATUS_PENDING) {
    return std::string("pending");
  } else if (status == yealink::ChatItemStatus::CHAT_ITEM_STATUS_SUCCESS) {
    return std::string("success");
  } else if (status == yealink::ChatItemStatus::CHAT_ITEM_STATUS_FAILURE) {
    return std::string("failure");
  } else {
    return std::string("invalid");
  }
}
std::string ConferenceMessageBinding::senderEntity() {
  return std::string(message_controller_.GetSenderEntity());
}
std::string ConferenceMessageBinding::senderName() {
  return std::string(message_controller_.GetSenderDisplayText());
}

std::string ConferenceMessageBinding::direction() {
  if (message_controller_.IsFromCurrentUser()) {
    return std::string("send");
  } else {
    return std::string("recv");
  }
}

v8::Local<v8::Promise> ConferenceMessageBinding::SetStatus(bool isRead) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  message_controller_.SetReadStatus(isRead);

  std::move(promise).Resolve();

  return handle;
}

}  // namespace rtvc
