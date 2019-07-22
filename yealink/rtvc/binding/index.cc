#include <node.h>

#include "yealink/native_mate/dictionary.h"

namespace {

void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
  mate::Dictionary dict(context->GetIsolate(), exports);
}

}  // namespace

NODE_MODULE_CONTEXT_AWARE(yealink_rtvc, Initialize)
