#include <node.h>
#include <iostream>
#include <string>

#include "yealink/native_mate/dictionary.h"

namespace yealink {

void Hello(const std::string& msg){
  std::cout << msg << std::endl;
};

}  // namespace yealink

namespace {

void Initialize(v8::Local<v8::Object> exports,
                v8::Local<v8::Value> unused,
                v8::Local<v8::Context> context,
                void* priv) {
  mate::Dictionary dict(context->GetIsolate(), exports);

  dict.SetMethod("hello", &yealink::Hello);
}

}  // namespace

NODE_MODULE_CONTEXT_AWARE(yealink_hello, Initialize)

// #include <node.h>

// namespace demo {

// using v8::FunctionCallbackInfo;
// using v8::Isolate;
// using v8::Local;
// using v8::NewStringType;
// using v8::Object;
// using v8::String;
// using v8::Value;

// void Method(const FunctionCallbackInfo<Value>& args) {
//   Isolate* isolate = args.GetIsolate();
//   args.GetReturnValue().Set(
//       String::NewFromUtf8(isolate, "world world world, hello world!",
//                           NewStringType::kNormal)
//           .ToLocalChecked());
// }

// void Initialize(Local<Object> exports) {
//   NODE_SET_METHOD(exports, "hello", Method);
// }

// NODE_MODULE(NODE_GYP_MODULE_NAME, Initialize)

// }  // namespace demo
