#ifndef YEALINK_RTVC_BINDING_CONFERENCE_VIEW_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_VIEW_BINDING_H_

#include "yealink/libvc/include/room/room_controller.h"
#include "yealink/libvc/include/room/room_observer.h"
#include "yealink/libvc/include/room/room_view_component.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/conference.h"
#include "yealink/rtvc/api/conference_view.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"

namespace yealink {

namespace rtvc {

class ConferenceViewBinding : public mate::EventEmitter<ConferenceViewBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ConferenceViewBinding> Create(
      v8::Isolate* isolate,
      yealink::RoomController* controller);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateRoomController(RoomController* handler);

 protected:
  ConferenceViewBinding(v8::Isolate* isolate,
                        yealink::RoomController* controller);
  ConferenceViewBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~ConferenceViewBinding() override;

  v8::Local<v8::Value> SetLayout(SetLayoutInfo params);
  v8::Local<v8::Value> GetLayout();

  v8::Local<v8::Value> SetInitialFilters(ViewFilterRuleInfo params);
  v8::Local<v8::Value> GetInitialFilters();

 private:
  void OnCommandCompeleted(Promise promise);
  void DoSetLayout(SetLayoutInfo params);
  void DoSetInitialFilters(ViewFilterRuleInfo params);

 private:
  RoomController* room_controller_;
  base::WeakPtrFactory<ConferenceViewBinding> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_VIEW_BINDING_H_
