#include "yealink/rtvc/binding/conference_chat_binding.h"

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/glue/struct_traits.h"

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

void ConferenceChatBinding::UpdateRoomController(
    yealink::RoomController* handler) {
  room_controller_ = handler;
}

void ConferenceChatBinding::UpdateChatController(
    yealink::ChatManager* handler) {
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
  yealink::Array<yealink::RoomMember> sendUsers;

  for (int i = 0; i < (int)entities.size(); i++) {
    yealink::RoomMember sendUser;
    sendUser =
        room_controller_->GetMemberManager().FindUser(entities[i].c_str());

    sendUsers.Append(sendUser);
  }

  if (room_controller_) {
    if ((int)entities.size() == 0) {
      yealink::ChatMessageItem* item = new yealink::ChatMessageItem();
      yealink::RoomMember tmpUser;
      base::PostTaskAndReply(
          FROM_HERE,
          base::BindOnce(&ConferenceChatBinding::DoSendChatMessage,
                         base::Unretained(this), false, message, tmpUser, item),
          base::BindOnce(&ConferenceChatBinding::OnMessageCompeleted,
                         weak_factory_.GetWeakPtr(), std::move(promise), item));

    } else {
      if ((int)sendUsers.Size() > 0) {
        // only send to first member
        yealink::ChatMessageItem* item = new yealink::ChatMessageItem();
        base::PostTaskAndReply(
            FROM_HERE,
            base::BindOnce(&ConferenceChatBinding::DoSendChatMessage,
                           base::Unretained(this), true, message, sendUsers[0],
                           item),
            base::BindOnce(&ConferenceChatBinding::OnMessageCompeleted,
                           weak_factory_.GetWeakPtr(), std::move(promise),
                           item));
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

  if (chat_controller_ && !handler.IsEmpty()) {
    bool* res = new bool();
    base::PostTaskAndReply(
        FROM_HERE,
        base::BindOnce(&ConferenceChatBinding::DoRetrySendMessage,
                       base::Unretained(this), handler, res),
        base::BindOnce(&ConferenceChatBinding::OnRetryMessageCompeleted,
                       weak_factory_.GetWeakPtr(), std::move(promise), res));
  } else {
    std::move(promise).Reject();
  }

  return handle;
}

v8::Local<v8::Value> ConferenceChatBinding::publicDialog() {
  yealink::ChatDialog dlgControl = chat_controller_->GetPublicDialog();

  mate::Handle<ConferenceDialogBinding> dlg =
      ConferenceDialogBinding::Create(isolate(), dlgControl);
  v8::Global<v8::Value> v8_dlg;
  v8_dlg.Reset(isolate(), dlg.ToV8());

  return v8::Local<v8::Value>::New(isolate(), v8_dlg);
}

std::vector<v8::Local<v8::Value>> ConferenceChatBinding::dialogList() {
  std::vector<v8::Local<v8::Value>> value;

  yealink::Array<yealink::ChatDialog> dlgControlList =
      chat_controller_->GetPrivateDialogList();

  for (size_t i = 0; i < dlgControlList.Size(); i++) {
    mate::Handle<ConferenceDialogBinding> dlg =
        ConferenceDialogBinding::Create(isolate(), dlgControlList[i]);
    v8::Global<v8::Value> v8_dlg;
    v8_dlg.Reset(isolate(), dlg.ToV8());

    value.push_back(v8::Local<v8::Value>::New(isolate(), v8_dlg));
  }

  return value;
}

void ConferenceChatBinding::DoSendChatMessage(bool isSingle,
                                              std::string message,
                                              yealink::RoomMember member,
                                              yealink::ChatMessageItem* item) {
  if (isSingle == false)
    *item = chat_controller_->SendMessageToAll(message.c_str());
  else
    *item = chat_controller_->SendMessageToMember(member, message.c_str());
}

void ConferenceChatBinding::OnMessageCompeleted(
    Promise promise,
    yealink::ChatMessageItem* item) {
  if (item != nullptr) {
    v8::HandleScope handle_scope(isolate());
    mate::Handle<ConferenceMessageBinding> new_message =
        ConferenceMessageBinding::Create(isolate(), *item);
    v8::Global<v8::Value> v8_new_message;
    v8_new_message.Reset(isolate(), new_message.ToV8());

    std::move(promise).Resolve(
        v8::Local<v8::Value>::New(isolate(), v8_new_message));

    delete item;
  } else {
    std::move(promise).Reject();
  }
}

void ConferenceChatBinding::DoRetrySendMessage(
    mate::Handle<ConferenceMessageBinding> handler,
    bool* res) {
  if (res != nullptr && chat_controller_ != nullptr)
    *res = chat_controller_->RetryMessage(handler->GetMessageItem());
}
void ConferenceChatBinding::OnRetryMessageCompeleted(Promise promise,
                                                     bool* res) {
  if (res != nullptr) {
    if (*res == true)
      std::move(promise).Resolve();
    else
      std::move(promise).Reject();
  } else {
    std::move(promise).Reject();
  }
}

}  // namespace rtvc
