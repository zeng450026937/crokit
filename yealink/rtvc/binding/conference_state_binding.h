#ifndef YEALINK_RTVC_BINDING_CONFERENCE_STATE_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_STATE_BINDING_H_

#include "yealink/native_mate/wrappable.h"

namespace yealink {

namespace rtvc {

class ConferenceStateBinding
    : public mate::Wrappable<ConferenceStateBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  ConferenceStateBinding(v8::Isolate* isolate,
                               v8::Local<v8::Object> wrapper);
  ~ConferenceStateBinding() override;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_STATE_BINDING_H_
