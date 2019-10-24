#ifndef YEALINK_RTVC_BINDING_CONNECTOR_BINDING_H_
#define YEALINK_RTVC_BINDING_CONNECTOR_BINDING_H_

#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/libvc/include/access/access_agent_api.h"

namespace rtvc {

class ConnectorBinding : public mate::Wrappable<ConnectorBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ConnectorBinding> Create(
      v8::Isolate* isolate,
      yealink::AccessAgent* access_agent);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  yealink::AccessAgent* GetAccessAgent() { return access_agent_; }

 protected:
  ConnectorBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ConnectorBinding(v8::Isolate* isolate, yealink::AccessAgent* access_agent);
  ~ConnectorBinding() override;

 private:
  yealink::AccessAgent* access_agent_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_CONNECTOR_BINDING_H_
