#ifndef YEALINK_RTVC_BINDING_CONFERENCE_BINDING_H_
#define YEALINK_RTVC_BINDING_CONFERENCE_BINDING_H_

#include "yealink/rtvc/binding/event_emitter.h"

namespace yealink {

namespace rtvc {

class ConferenceBinding : public mate::EventEmitter<ConferenceBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  ConferenceBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~ConferenceBinding() override;

  void Connect();
  void Disconnect();

  bool isInProgress();
  bool isEstablished();
  bool isEnded();
  bool isChatChannelSupported();
  bool isChatChannelEstablished();
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_CONFERENCE_BINDING_H_
