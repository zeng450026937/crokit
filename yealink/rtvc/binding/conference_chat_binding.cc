#include "yealink/rtvc/binding/conference_chat_binding.h"

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* ConferenceChatBinding::New(mate::Arguments* args) {
  return new ConferenceChatBinding(args->isolate(), args->GetThis());
}

mate::Handle<ConferenceChatBinding> ConferenceChatBinding::Create(
    v8::Isolate* isolate,
    yealink::RoomController* controller) {
  return mate::CreateHandle(isolate,
                            new ConferenceChatBinding(isolate, controller));
}

// static
void ConferenceChatBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "ConferenceChat"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("publicDialog", &ConferenceChatBinding::publicDialog)
      .SetProperty("dialogList", &ConferenceChatBinding::dialogList)
      .SetMethod("sendChatMessage", &ConferenceChatBinding::SendChatMessage)
      .SetMethod("retrySendMessage",
                 &ConferenceChatBinding::RetrySendChatMessage);
}

void ConferenceChatBinding::UpdateRoomController(RoomController* handler) {
  room_controller_ = handler;
}

void ConferenceChatBinding::UpdateChatController(ChatManager* handler) {
  chat_controller_ = handler;
}

ConferenceChatBinding::ConferenceChatBinding(
    v8::Isolate* isolate,
    yealink::RoomController* controller)
    : weak_factory_(this) {
  Init(isolate);
  room_controller_ = controller;
}

ConferenceChatBinding::ConferenceChatBinding(v8::Isolate* isolate,
                                             v8::Local<v8::Object> wrapper)
    : weak_factory_(this) {}
ConferenceChatBinding::~ConferenceChatBinding() = default;

v8::Local<v8::Promise> ConferenceChatBinding::SendChatMessage(
    std::string message,
    std::vector<std::string> entities) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  yealink::Array<RoomMember> sendUsers;

  for (int i = 0; i < (int)entities.size(); i++) {
    yealink::RoomMember sendUser;
    sendUser =
        room_controller_->GetMemberManager().FindUser(entities[i].c_str());

    sendUsers.Append(sendUser);
  }

  if (room_controller_) {
    if ((int)entities.size() == 0) {
      ChatMessageItem item =
          chat_controller_->SendMessageToAll(message.c_str());

      mate::Handle<ConferenceMessageBinding> new_message =
          ConferenceMessageBinding::Create(isolate(), item);
      v8::Global<v8::Value> v8_new_message;
      v8_new_message.Reset(isolate(), new_message.ToV8());

      std::move(promise).Resolve(
          v8::Local<v8::Value>::New(isolate(), v8_new_message));
    } else {
      if ((int)sendUsers.Size() > 0) {
        // only send to first member
        ChatMessageItem item = chat_controller_->SendMessageToMember(
            (yealink::RoomMember)sendUsers[0], message.c_str());

        mate::Handle<ConferenceMessageBinding> new_message =
            ConferenceMessageBinding::Create(isolate(), item);
        v8::Global<v8::Value> v8_new_message;
        v8_new_message.Reset(isolate(), new_message.ToV8());

        std::move(promise).Resolve(
            v8::Local<v8::Value>::New(isolate(), v8_new_message));
      } else {
        // if no find any member
        std::move(promise).Reject();
      }
    }
  } else {
    std::move(promise).Reject();
  }

  return handle;
}

v8::Local<v8::Promise> ConferenceChatBinding::RetrySendChatMessage(
    mate::Handle<ConferenceMessageBinding> handler) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  bool res = false;

  if (chat_controller_ && !handler.IsEmpty()) {

    ChatMessageItem test = handler->GetMessageItem();

    ChatItemStatus status = test.GetStatus();
    char* text = (char *)test.GetContext();

    res = chat_controller_->RetryMessage(test);

    if (res == true)
      std::move(promise).Resolve();
    else
      std::move(promise).Reject();
  } else {
    std::move(promise).Reject();
  }

  return handle;
}

v8::Local<v8::Value> ConferenceChatBinding::publicDialog() {
  ChatDialog dlgControl = chat_controller_->GetPublicDialog();

  mate::Handle<ConferenceDialogBinding> dlg =
      ConferenceDialogBinding::Create(isolate(), dlgControl);
  v8::Global<v8::Value> v8_dlg;
  v8_dlg.Reset(isolate(), dlg.ToV8());

  return v8::Local<v8::Value>::New(isolate(), v8_dlg);
}

std::vector<v8::Local<v8::Value>> ConferenceChatBinding::dialogList() {
  std::vector<v8::Local<v8::Value>> value;

  Array<ChatDialog> dlgControlList = chat_controller_->GetPrivateDialogList();

  for (size_t i = 0; i < dlgControlList.Size(); i++) {
    mate::Handle<ConferenceDialogBinding> dlg =
        ConferenceDialogBinding::Create(isolate(), dlgControlList[i]);
    v8::Global<v8::Value> v8_dlg;
    v8_dlg.Reset(isolate(), dlg.ToV8());

    value.push_back(v8::Local<v8::Value>::New(isolate(), v8_dlg));
  }

  return value;
}

}  // namespace rtvc

}  // namespace yealink
