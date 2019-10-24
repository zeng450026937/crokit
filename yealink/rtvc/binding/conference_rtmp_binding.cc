#include "yealink/rtvc/binding/conference_rtmp_binding.h"

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace rtvc {

// static
mate::WrappableBase* ConferenceRtmpBinding::New(mate::Arguments* args) {
  return new ConferenceRtmpBinding(args->isolate(), args->GetThis());
}

mate::Handle<ConferenceRtmpBinding> ConferenceRtmpBinding::Create(
    v8::Isolate* isolate,
    yealink::RoomController* controller) {
  return mate::CreateHandle(isolate,
                            new ConferenceRtmpBinding(isolate, controller));
}

// static
void ConferenceRtmpBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "ConferenceRtmp"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetMethod("getRtmpStatus", &ConferenceRtmpBinding::GetRtmpStatus)
      .SetMethod("setRtmpStatus", &ConferenceRtmpBinding::SetRtmpStatus);
}

void ConferenceRtmpBinding::UpdateRoomController(
    yealink::RoomController* handler) {
  room_controller_ = handler;
}

ConferenceRtmpBinding::ConferenceRtmpBinding(
    v8::Isolate* isolate,
    yealink::RoomController* controller)
    : weak_factory_(this) {
  Init(isolate);
  room_controller_ = controller;
}

ConferenceRtmpBinding::ConferenceRtmpBinding(v8::Isolate* isolate,
                                             v8::Local<v8::Object> wrapper)
    : weak_factory_(this) {}
ConferenceRtmpBinding::~ConferenceRtmpBinding() = default;

RtmpInfo ConferenceRtmpBinding::GetRtmpStatus() {
  RtmpInfo value;

  if (room_controller_) {
    ConvertFrom(value, room_controller_->GetRtmpComponent().GetRtmpState());
  }

  return value;
}

v8::Local<v8::Promise> ConferenceRtmpBinding::SetRtmpStatus(
    RtmpStatusType status) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  HttpResponseInfo* response = new HttpResponseInfo();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceRtmpBinding::DoSetRtmpStatus,
                     base::Unretained(this), status, response),
      base::BindOnce(&ConferenceRtmpBinding::OnProcessCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise), response));

  return handle;
}

void ConferenceRtmpBinding::DoSetRtmpStatus(RtmpStatusType status,
                                            HttpResponseInfo* response) {
  if (response != nullptr && room_controller_ != nullptr)
    ConvertFrom(*response, room_controller_->GetRtmpComponent().SetRtmpState(
                               yealink::RoomRtmpStatus(status)));
}

void ConferenceRtmpBinding::OnProcessCompeleted(Promise promise,
                                                HttpResponseInfo* response) {
  if (response != nullptr) {
    std::move(promise).Resolve(*response);
    delete response;
  } else {
    std::move(promise).Reject();
  }
}
}  // namespace rtvc
