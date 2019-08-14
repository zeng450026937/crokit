#ifndef YEALINK_RTVC_BINDING_SCOPED_WRAPPER_H_
#define YEALINK_RTVC_BINDING_SCOPED_WRAPPER_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_refptr.h"

namespace yealink {

namespace rtvc {

template <typename T>
struct DefaultRefCountedTraits {
  template <typename... Args>
  static void Construct(T* x, Args&&... args) {
    RefCounted<T, DefaultRefCountedTraits>::ConstructInternal(
        x, std::forward<Args>(args)...);
  }
  static void Destruct(const T* x) {
    RefCounted<T, DefaultRefCountedTraits>::DeleteInternal(x);
  }
};

template <typename T, typename Traits = DefaultRefCountedTraits<T>>
class RefCounted : public base::RefCounted<RefCounted<T, Traits>> {
 public:
  RefCounted() = default;
  RefCounted(T* ptr) : ptr_(ptr) {}

  T* get() const { return ptr_; }
  void swap(T* ptr) { ptr_ = ptr; }

  T& operator*() const { return *get(); }
  T* operator->() const { return get(); }

 public:
  friend class base::RefCounted<RefCounted<T, Traits>>;

  ~RefCounted() {
    if (ptr_)
      Traits::Destruct(ptr_);
  };

 private:
  T* ptr_ = nullptr;

  friend struct DefaultRefCountedTraits<T>;
  template <typename U, typename... Args>
  static void ConstructInternal(U* x, Args&&... args) {
    new (x) U(std::forward<Args>(args)...);
  }
  template <typename U>
  static void DeleteInternal(const U* x) {
    delete x;
  }

  DISALLOW_COPY_AND_ASSIGN(RefCounted);
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_SCOPED_WRAPPER_H_
