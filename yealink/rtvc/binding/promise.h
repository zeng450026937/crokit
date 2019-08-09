#ifndef YEALINK_RTVC_BINDING_PROMISE_H_
#define YEALINK_RTVC_BINDING_PROMISE_H_

#include <string>
#include <utility>

#include "yealink/native_mate/converter.h"
#include "yealink/native_mate/converters/callback.h"
#include "yealink/native_mate/converters/once_callback.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/libuv_holder.h"

namespace yealink {

namespace rtvc {

// A wrapper around the v8::Promise.
//
// This is a move-only type that should always be `std::move`d when passed to
// callbacks, and it should be destroyed on the same thread of creation.
class Promise {
 public:
  // Create a new promise.
  explicit Promise(v8::Isolate* isolate);

  // Wrap an existing v8 promise.
  Promise(v8::Isolate* isolate, v8::Local<v8::Promise::Resolver> handle);

  ~Promise();

  // Support moving.
  Promise(Promise&&);
  Promise& operator=(Promise&&);

  v8::Isolate* isolate() const { return isolate_; }
  v8::Local<v8::Context> GetContext() {
    return v8::Local<v8::Context>::New(isolate_, context_);
  }

  // helpers for promise resolution and rejection

  template <typename T>
  static void ResolvePromise(Promise promise, T result) {
    if (!Context::Instance()->CalledOnValidThread()) {
      Context::Instance()->PostTask(
          FROM_HERE, base::BindOnce([](Promise promise,
                                       T result) { promise.Resolve(result); },
                                    std::move(promise), std::move(result)));
    } else {
      promise.Resolve(result);
    }
  }

  static void ResolveEmptyPromise(Promise promise) {
    if (!Context::Instance()->CalledOnValidThread()) {
      Context::Instance()->PostTask(
          FROM_HERE, base::BindOnce([](Promise promise) { promise.Resolve(); },
                                    std::move(promise)));
    } else {
      promise.Resolve();
    }
  }

  static void RejectPromise(Promise promise, std::string errmsg) {
    if (!Context::Instance()->CalledOnValidThread()) {
      Context::Instance()->PostTask(
          FROM_HERE, base::BindOnce(
                         [](Promise promise, std::string errmsg) {
                           promise.RejectWithErrorMessage(errmsg);
                         },
                         std::move(promise), std::move(errmsg)));
    } else {
      promise.RejectWithErrorMessage(errmsg);
    }
  }

  // Returns an already-resolved promise.
  template <typename T>
  static v8::Local<v8::Promise> ResolvedPromise(v8::Isolate* isolate,
                                                T result) {
    Promise resolved(isolate);
    resolved.Resolve(result);
    return resolved.GetHandle();
  }

  static v8::Local<v8::Promise> ResolvedPromise(v8::Isolate* isolate) {
    Promise resolved(isolate);
    resolved.Resolve();
    return resolved.GetHandle();
  }

  v8::Local<v8::Promise> GetHandle() const;

  v8::Maybe<bool> Resolve() {
    v8::HandleScope handle_scope(isolate());
    v8::MicrotasksScope script_scope(isolate(),
                                     v8::MicrotasksScope::kRunMicrotasks);
    v8::Context::Scope context_scope(
        v8::Local<v8::Context>::New(isolate(), GetContext()));

    return GetInner()->Resolve(GetContext(), v8::Undefined(isolate()));
  }

  v8::Maybe<bool> Reject() {
    v8::HandleScope handle_scope(isolate());
    v8::MicrotasksScope script_scope(isolate(),
                                     v8::MicrotasksScope::kRunMicrotasks);
    v8::Context::Scope context_scope(
        v8::Local<v8::Context>::New(isolate(), GetContext()));

    return GetInner()->Reject(GetContext(), v8::Undefined(isolate()));
  }

  // Please note that using Then is effectively the same as calling .then
  // in javascript.  This means (a) it is not type safe and (b) please note
  // it is NOT type safe.
  // If the base::Callback you provide here is of type void(boolean) and you
  // resolve the promise with a string, Electron will compile successfully and
  // then that promise will be rejected as soon as you try to use it as the
  // mate converters doing work behind the scenes will throw an error for you.
  // This can be really hard to trace so until either
  //   * This helper becomes typesafe (by templating the class instead of each
  //   method)
  //   * or the world goes mad
  // Please try your hardest not to use this method
  // The world thanks you
  template <typename... ResolveType>
  v8::MaybeLocal<v8::Promise> Then(
      base::OnceCallback<void(ResolveType...)> cb) {
    static_assert(sizeof...(ResolveType) <= 1,
                  "A promise's 'Then' callback should only receive at most one "
                  "parameter");
    v8::HandleScope handle_scope(isolate());
    v8::Context::Scope context_scope(
        v8::Local<v8::Context>::New(isolate(), GetContext()));

    v8::Local<v8::Value> value = mate::ConvertToV8(isolate(), cb);
    v8::Local<v8::Function> handler = v8::Local<v8::Function>::Cast(value);

    return GetHandle()->Then(GetContext(), handler);
  }

  // Promise resolution is a microtask
  // We use the MicrotasksRunner to trigger the running of pending microtasks
  template <typename T>
  v8::Maybe<bool> Resolve(const T& value) {
    v8::HandleScope handle_scope(isolate());
    v8::MicrotasksScope script_scope(isolate(),
                                     v8::MicrotasksScope::kRunMicrotasks);
    v8::Context::Scope context_scope(
        v8::Local<v8::Context>::New(isolate(), GetContext()));

    return GetInner()->Resolve(GetContext(),
                               mate::ConvertToV8(isolate(), value));
  }

  template <typename T>
  v8::Maybe<bool> Reject(const T& value) {
    v8::HandleScope handle_scope(isolate());
    v8::MicrotasksScope script_scope(isolate(),
                                     v8::MicrotasksScope::kRunMicrotasks);
    v8::Context::Scope context_scope(
        v8::Local<v8::Context>::New(isolate(), GetContext()));

    return GetInner()->Reject(GetContext(),
                              mate::ConvertToV8(isolate(), value));
  }

  v8::Maybe<bool> RejectWithErrorMessage(const std::string& error);

 private:
  friend class CopyablePromise;

  v8::Local<v8::Promise::Resolver> GetInner() const {
    return resolver_.Get(isolate());
  }

  v8::Isolate* isolate_;
  v8::Global<v8::Context> context_;
  v8::Global<v8::Promise::Resolver> resolver_;

#if defined(NODE_BUILD)
  scoped_refptr<LibUVHolder> holder_;
#endif

  DISALLOW_COPY_AND_ASSIGN(Promise);
};

// A wrapper of Promise that can be copied.
//
// This class should only be used when we have to pass Promise to a Chromium API
// that does not take OnceCallback.
class CopyablePromise {
 public:
  explicit CopyablePromise(const Promise& promise);
  CopyablePromise(const CopyablePromise&);
  ~CopyablePromise();

  template <typename T>
  static void ResolveCopyablePromise(const CopyablePromise& promise, T result) {
    if (!Context::Instance()->CalledOnValidThread()) {
      Context::Instance()->PostTask(
          FROM_HERE, {content::BrowserThread::UI},
          base::BindOnce(Promise::ResolvePromise<T>, promise.GetPromise(),
                         std::move(result)));
    } else {
      promise.GetPromise().Resolve(result);
    }
  }

  static void ResolveEmptyCopyablePromise(const CopyablePromise& promise) {
    if (!Context::Instance()->CalledOnValidThread()) {
      Context::Instance()->PostTask(
          FROM_HERE,
          base::BindOnce(Promise::ResolveEmptyPromise, promise.GetPromise()));
    } else {
      promise.GetPromise().Resolve();
    }
  }

  static void RejectCopyablePromise(const CopyablePromise& promise,
                                    std::string errmsg) {
    if (!Context::Instance()->CalledOnValidThread()) {
      Context::Instance()->PostTask(
          FROM_HERE, base::BindOnce(Promise::RejectPromise,
                                    promise.GetPromise(), std::move(errmsg)));
    } else {
      promise.GetPromise().RejectWithErrorMessage(errmsg);
    }
    promise.GetPromise().RejectWithErrorMessage(errmsg);
  }

  Promise GetPromise() const;

 private:
  using CopyablePersistent =
      v8::CopyablePersistentTraits<v8::Promise::Resolver>::CopyablePersistent;

  v8::Isolate* isolate_;
  CopyablePersistent handle_;
};

}  // namespace rtvc

}  // namespace yealink

namespace mate {

template <>
struct Converter<yealink::rtvc::Promise> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::Promise& val);
  // TODO(MarshallOfSound): Implement FromV8 to allow promise chaining
  //                        in native land
  // static bool FromV8(v8::Isolate* isolate,
  //                    v8::Local<v8::Value> val,
  //                    Promise* out);
};

}  // namespace mate

#endif  // YEALINK_RTVC_BINDING_PROMISE_H_
