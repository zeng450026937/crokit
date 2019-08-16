#ifndef YEALINK_RTVC_BINDING_SCHEDULE_BINDING_H_
#define YEALINK_RTVC_BINDING_SCHEDULE_BINDING_H_

#include "yealink/native_mate/handle.h"
#include "yealink/rtvc/binding/event_emitter.h"

namespace yealink {

namespace rtvc {

class ScheduleBinding : public mate::EventEmitter<ScheduleBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  ScheduleBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~ScheduleBinding() override;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_SCHEDULE_BINDING_H_
