#ifndef YEALINK_RTVC_BINDING_YTMS_BINDING_H_
#define YEALINK_RTVC_BINDING_YTMS_BINDING_H_

#include "yealink/native_mate/handle.h"
#include "yealink/rtvc/binding/event_emitter.h"

namespace yealink {

namespace rtvc {

class YTMSBinding : public mate::EventEmitter<YTMSBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  YTMSBinding();
  ~YTMSBinding() override;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_YTMS_BINDING_H_
