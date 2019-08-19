#ifndef YEALINK_RTVC_BINDING_TRACKABLE_OBJECT_H_
#define YEALINK_RTVC_BINDING_TRACKABLE_OBJECT_H_

#include <vector>

#include "base/bind.h"
#include "base/memory/weak_ptr.h"
#include "yealink/rtvc/binding/key_weak_map.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/native_mate/wrappable.h"

namespace base {
class SupportsUserData;
}

namespace mate {

// Users should use TrackableObject instead.
class TrackableObjectBase {
 public:
  TrackableObjectBase();

  // The ID in weak map.
  int32_t weak_map_id() const { return weak_map_id_; }

  // Wrap TrackableObject into a class that SupportsUserData.
  void AttachAsUserData(base::SupportsUserData* wrapped);

  // Get the weak_map_id from SupportsUserData.
  static int32_t GetIDFromWrappedClass(base::SupportsUserData* wrapped);

 protected:
  virtual ~TrackableObjectBase();

  // Returns a closure that can destroy the native class.
  base::OnceClosure GetDestroyClosure();

  int32_t weak_map_id_ = 0;

 private:
  void Destroy();

  base::WeakPtrFactory<TrackableObjectBase> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(TrackableObjectBase);
};

// All instances of TrackableObject will be kept in a weak map and can be got
// from its ID.
template <typename T>
class TrackableObject : public TrackableObjectBase, public Wrappable<T> {
 public:
  // Mark the JS object as destroyed.
  void MarkDestroyed() {
    v8::Local<v8::Object> wrapper = Wrappable<T>::GetWrapper();
    if (!wrapper.IsEmpty()) {
      wrapper->SetAlignedPointerInInternalField(0, nullptr);
    }
  }

  bool IsDestroyed() {
    v8::Local<v8::Object> wrapper = Wrappable<T>::GetWrapper();
    return wrapper->InternalFieldCount() == 0 ||
           wrapper->GetAlignedPointerFromInternalField(0) == nullptr;
  }

  // Finds out the TrackableObject from its ID in weak map.
  static T* FromWeakMapID(v8::Isolate* isolate, int32_t id) {
    if (!weak_map_)
      return nullptr;

    v8::MaybeLocal<v8::Object> object = weak_map_->Get(isolate, id);
    if (object.IsEmpty())
      return nullptr;

    T* self = nullptr;
    mate::ConvertFromV8(isolate, object.ToLocalChecked(), &self);
    return self;
  }

  // Finds out the TrackableObject from the class it wraps.
  static T* FromWrappedClass(v8::Isolate* isolate,
                             base::SupportsUserData* wrapped) {
    int32_t id = GetIDFromWrappedClass(wrapped);
    if (!id)
      return nullptr;
    return FromWeakMapID(isolate, id);
  }

  // Returns all objects in this class's weak map.
  static std::vector<v8::Local<v8::Object>> GetAll(v8::Isolate* isolate) {
    if (weak_map_)
      return weak_map_->Values(isolate);
    else
      return std::vector<v8::Local<v8::Object>>();
  }

  // Removes this instance from the weak map.
  void RemoveFromWeakMap() {
    if (weak_map_ && weak_map_->Has(weak_map_id()))
      weak_map_->Remove(weak_map_id());
  }

 protected:
  TrackableObject() { weak_map_id_ = ++next_id_; }

  ~TrackableObject() override { RemoveFromWeakMap(); }

  void InitWith(v8::Isolate* isolate, v8::Local<v8::Object> wrapper) override {
    WrappableBase::InitWith(isolate, wrapper);
    if (!weak_map_) {
      weak_map_ = new KeyWeakMap<int32_t>;
    }
    weak_map_->Set(isolate, weak_map_id_, wrapper);
  }

 private:
  static int32_t next_id_;
  static KeyWeakMap<int32_t>* weak_map_;  // leaked on purpose

  DISALLOW_COPY_AND_ASSIGN(TrackableObject);
};

template <typename T>
int32_t TrackableObject<T>::next_id_ = 0;

template <typename T>
KeyWeakMap<int32_t>* TrackableObject<T>::weak_map_ = nullptr;

}  // namespace mate

#endif  // YEALINK_RTVC_BINDING_TRACKABLE_OBJECT_H_
