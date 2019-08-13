#ifndef YEALINK_RTVC_BINDING_CONFERENCE_DESCRIPTION_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_DESCRIPTION_BINDING_H_

#include "yealink/native_mate/wrappable.h"

namespace yealink {

namespace rtvc {

class ConferenceDescriptionBinding
    : public mate::Wrappable<ConferenceDescriptionBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  ConferenceDescriptionBinding(v8::Isolate* isolate,
                               v8::Local<v8::Object> wrapper);
  ~ConferenceDescriptionBinding() override;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_DESCRIPTION_BINDING_H_
