#ifndef YEALINK_RTVC_BINDING_CONFERENCE_RTMP_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_RTMP_BINDING_H_

#include "yealink/libvc/include/room/room_controller.h"
#include "yealink/libvc/include/room/room_observer.h"
#include "yealink/libvc/include/room/room_rtmp_component.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/api/conference_rtmp.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"

namespace yealink {

namespace rtvc {

class ConferenceRtmpBinding : public mate::EventEmitter<ConferenceRtmpBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ConferenceRtmpBinding> Create(
      v8::Isolate* isolate,
      yealink::RoomController* controller);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateRoomController(RoomController* handler);

 protected:
  ConferenceRtmpBinding(v8::Isolate* isolate,
                        yealink::RoomController* controller);
  ConferenceRtmpBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~ConferenceRtmpBinding() override;

  RtmpInfo GetRtmpStatus();
  v8::Local<v8::Promise> SetRtmpStatus(RtmpStatusType status);

 private:
  RoomController* room_controller_;
  base::WeakPtrFactory<ConferenceRtmpBinding> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_RTMP_BINDING_H_
