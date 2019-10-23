#ifndef YEALINK_RTVC_BINDING_CONFERENCE_RECORD_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_RECORD_BINDING_H_

#include "yealink/libvc/include/room/room_controller.h"
#include "yealink/libvc/include/room/room_observer.h"
#include "yealink/libvc/include/room/room_rtmp_component.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/api/conference_record.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"

namespace yealink {

namespace rtvc {

class ConferenceRecordBinding
    : public mate::EventEmitter<ConferenceRecordBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ConferenceRecordBinding> Create(
      v8::Isolate* isolate,
      yealink::RoomController* controller);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateRoomController(RoomController* handler);

 protected:
  ConferenceRecordBinding(v8::Isolate* isolate,
                          yealink::RoomController* controller);
  ConferenceRecordBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~ConferenceRecordBinding() override;

  RecordUsers GetRecordStatus();
  v8::Local<v8::Promise> SetRecordStatus(RecordStatusType status);

 private:
  void DoSetRecordStatus(RecordStatusType status, HttpResponseInfo* response);
  void OnProcessCompeleted(Promise promise, HttpResponseInfo* response);

  RoomController* room_controller_;
  base::WeakPtrFactory<ConferenceRecordBinding> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_RECORD_BINDING_H_
