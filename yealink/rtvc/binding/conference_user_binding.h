#ifndef YEALINK_RTVC_BINDING_CONFERENCE_USER_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_USER_BINDING_H_

#include "yealink/native_mate/wrappable.h"

namespace yealink {

namespace rtvc {

class ConferenceUserBinding
    : public mate::Wrappable<ConferenceUserBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  ConferenceUserBinding(v8::Isolate* isolate,
                               v8::Local<v8::Object> wrapper);
  ~ConferenceUserBinding() override;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_USER_BINDING_H_
