#include "yealink/rtvc/binding/conference_record_binding.h"

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* ConferenceRecordBinding::New(mate::Arguments* args) {
  return new ConferenceRecordBinding(args->isolate(), args->GetThis());
}

mate::Handle<ConferenceRecordBinding> ConferenceRecordBinding::Create(
    v8::Isolate* isolate,
    yealink::RoomController* controller) {
  return mate::CreateHandle(isolate,
                            new ConferenceRecordBinding(isolate, controller));
}

// static
void ConferenceRecordBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "ConferenceRecord"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetMethod("getRecordStatus", &ConferenceRecordBinding::GetRecordStatus)
      .SetMethod("setRecordStatus", &ConferenceRecordBinding::SetRecordStatus);
}

void ConferenceRecordBinding::UpdateRoomController(RoomController* handler) {
  room_controller_ = handler;
}

ConferenceRecordBinding::ConferenceRecordBinding(
    v8::Isolate* isolate,
    yealink::RoomController* controller)
    : weak_factory_(this) {
  Init(isolate);
  room_controller_ = controller;
}

ConferenceRecordBinding::ConferenceRecordBinding(v8::Isolate* isolate,
                                                 v8::Local<v8::Object> wrapper)
    : weak_factory_(this) {}
ConferenceRecordBinding::~ConferenceRecordBinding() = default;

RecordUsers ConferenceRecordBinding::GetRecordStatus() {
  RecordUsers value;

  if (room_controller_) {
    ConvertFrom(value, room_controller_->GetRecordComponent().GetRecordUsers());
  }

  return value;
}

v8::Local<v8::Promise> ConferenceRecordBinding::SetRecordStatus(
    RecordStatusType status) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  HttpResponseInfo* response = new HttpResponseInfo();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ConferenceRecordBinding::DoSetRecordStatus,
                     base::Unretained(this), status, response),
      base::BindOnce(&ConferenceRecordBinding::OnProcessCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise), response));

  return handle;
}

void ConferenceRecordBinding::DoSetRecordStatus(RecordStatusType status,
                                                HttpResponseInfo* response) {
  if (response != nullptr && room_controller_ != nullptr)
    ConvertFrom(*response,
                room_controller_->GetRecordComponent().SetRecordStatus(
                    (RoomRecordStatus)status));
}

void ConferenceRecordBinding::OnProcessCompeleted(Promise promise,
                                                  HttpResponseInfo* response) {
  if (response != nullptr) {
    std::move(promise).Resolve(*response);
    delete response;
  } else {
    std::move(promise).Reject();
  }
}
}  // namespace rtvc

}  // namespace yealink
