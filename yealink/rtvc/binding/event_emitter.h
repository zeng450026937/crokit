// Copyright (c) 2014 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#ifndef YEALINK_RTVC_BINDING_EVENT_EMITTER_H_
#define YEALINK_RTVC_BINDING_EVENT_EMITTER_H_

#include <utility>
#include <vector>

#include "base/optional.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/event_emitter_caller.h"

namespace mate {

namespace internal {

v8::Local<v8::Object> CreateJSEvent(v8::Isolate* isolate,
                                    v8::Local<v8::Object> object);
v8::Local<v8::Object> CreateCustomEvent(v8::Isolate* isolate,
                                        v8::Local<v8::Object> object,
                                        v8::Local<v8::Object> event);

}  // namespace internal

// Provide helperers to emit event in JavaScript.
template <typename T>
class EventEmitter : public Wrappable<T> {
 public:
  typedef std::vector<v8::Local<v8::Value>> ValueArray;

  // Make the convinient methods visible:
  // https://isocpp.org/wiki/faq/templates#nondependent-name-lookup-members
  v8::Isolate* isolate() const { return Wrappable<T>::isolate(); }
  v8::Local<v8::Object> GetWrapper() const {
    return Wrappable<T>::GetWrapper();
  }
  v8::MaybeLocal<v8::Object> GetWrapper(v8::Isolate* isolate) const {
    return Wrappable<T>::GetWrapper(isolate);
  }

  // this.emit(name, event, args...);
  template <typename... Args>
  bool EmitCustomEvent(const base::StringPiece& name,
                       v8::Local<v8::Object> event,
                       Args&&... args) {
    return EmitWithEvent(
        name, internal::CreateCustomEvent(isolate(), GetWrapper(), event),
        std::forward<Args>(args)...);
  }

  // this.emit(name, new Event(), args...);
  template <typename... Args>
  bool Emit(const base::StringPiece& name, Args&&... args) {
    // v8::Locker locker(isolate());
    v8::HandleScope handle_scope(isolate());
    v8::Local<v8::Object> wrapper = GetWrapper();
    if (wrapper.IsEmpty()) {
      return false;
    }
    v8::Local<v8::Object> event = internal::CreateJSEvent(isolate(), wrapper);
    return EmitWithEvent(name, event, std::forward<Args>(args)...);
  }

 protected:
  EventEmitter() {}

 private:
  // this.emit(name, event, args...);
  template <typename... Args>
  bool EmitWithEvent(const base::StringPiece& name,
                     v8::Local<v8::Object> event,
                     Args&&... args) {
    DCHECK(yealink::rtvc::Context::Instance()->CalledOnValidThread());
    // v8::Locker locker(isolate());
    v8::HandleScope handle_scope(isolate());
    EmitEvent(isolate(), GetWrapper(), name, event,
              std::forward<Args>(args)...);
    auto context = isolate()->GetCurrentContext();
    v8::Local<v8::Value> defaultPrevented;
    if (event->Get(context, StringToV8(isolate(), "defaultPrevented"))
            .ToLocal(&defaultPrevented)) {
      return defaultPrevented->BooleanValue(isolate());
    }
    return false;
  }

  DISALLOW_COPY_AND_ASSIGN(EventEmitter);
};

}  // namespace mate

#endif  // YEALINK_RTVC_BINDING_EVENT_EMITTER_H_
