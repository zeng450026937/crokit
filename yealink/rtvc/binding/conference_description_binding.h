#ifndef YEALINK_RTVC_BINDING_CONFERENCE_DESCRIPTION_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_DESCRIPTION_BINDING_H_

#include "yealink/libvc/include/room/room_controller.h"
#include "yealink/libvc/include/room/room_description_component.h"
#include "yealink/libvc/include/room/room_observer.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/api/conference_state.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"

namespace yealink {

namespace rtvc {

class ConferenceDescriptionBinding
    : public mate::Wrappable<ConferenceDescriptionBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ConferenceDescriptionBinding> Create(
      v8::Isolate* isolate,
      yealink::RoomController* controller);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateRoomController(RoomController* handler);

 protected:
  ConferenceDescriptionBinding(v8::Isolate* isolate,
                               v8::Local<v8::Object> wrapper);
  ConferenceDescriptionBinding(v8::Isolate* isolate,
                               yealink::RoomController* controller);
  ~ConferenceDescriptionBinding() override;

  int Profile();

 private:
  RoomController* room_controller_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_DESCRIPTION_BINDING_H_
