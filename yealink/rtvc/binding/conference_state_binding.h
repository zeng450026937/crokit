#ifndef YEALINK_RTVC_BINDING_CONFERENCE_STATE_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_STATE_BINDING_H_

#include "yealink/libvc/include/room/room_controller.h"
#include "yealink/libvc/include/room/room_observer.h"
#include "yealink/libvc/include/room/room_state_component.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/api/conference_state.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"

namespace yealink {

namespace rtvc {

class ConferenceStateBinding
    : public mate::EventEmitter<ConferenceStateBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ConferenceStateBinding> Create(
      v8::Isolate* isolate,
      yealink::RoomController* controller);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateRoomController(RoomController* handler);

 protected:
  ConferenceStateBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ConferenceStateBinding(v8::Isolate* isolate,
                         yealink::RoomController* controller);
  ~ConferenceStateBinding() override;

  v8::Local<v8::Value> Active();
  v8::Local<v8::Value> Locked();
  v8::Local<v8::Value> RollCallStatus();

 private:

 private:
  RoomController* room_controller_;
  base::WeakPtrFactory<ConferenceStateBinding> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_STATE_BINDING_H_
