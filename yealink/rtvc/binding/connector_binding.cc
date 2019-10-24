#include "yealink/rtvc/binding/connector_binding.h"

namespace rtvc {

// static
mate::WrappableBase* ConnectorBinding::New(mate::Arguments* args) {
  return new ConnectorBinding(args->isolate(), args->GetThis());
}

// static
mate::Handle<ConnectorBinding> ConnectorBinding::Create(
    v8::Isolate* isolate,
    yealink::AccessAgent* access_agent) {
  return mate::CreateHandle(isolate,
                            new ConnectorBinding(isolate, access_agent));
}

// static
void ConnectorBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {}

ConnectorBinding::ConnectorBinding(v8::Isolate* isolate,
                                   v8::Local<v8::Object> wrapper) {
  NOTREACHED() << "Can not create Connector from javascript.";
  InitWith(isolate, wrapper);
}
ConnectorBinding::ConnectorBinding(v8::Isolate* isolate,
                                   yealink::AccessAgent* access_agent)
    : access_agent_(access_agent) {
  DCHECK(access_agent_);
  Init(isolate);
}
ConnectorBinding::~ConnectorBinding() = default;

}  // namespace rtvc
