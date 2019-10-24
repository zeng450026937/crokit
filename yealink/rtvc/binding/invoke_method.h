#ifndef YEALINK_RTVC_BINDING_INVOKE_METHOD_H_
#define YEALINK_RTVC_BINDING_INVOKE_METHOD_H_

#include <v8.h>
#include <vector>

namespace rtvc {

v8::Local<v8::Value> CallMethodWithArgs(
    v8::Isolate* isolate,
    v8::Local<v8::Object> obj,
    const char* method,
    std::vector<v8::Local<v8::Value>>* args);
}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_INVOKE_METHOD_H_
