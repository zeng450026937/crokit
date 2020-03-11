#ifndef YEALINK_RTVC_BINDING_WEAKABLE_H_
#define YEALINK_RTVC_BINDING_WEAKABLE_H_

#include "base/memory/weak_ptr.h"

namespace rtvc {

template <typename T>
struct DefaultWeakableTraits {
  template <typename... Args>
  static void Destruct(const T* x) {
    Weakable<T, DefaultWeakableTraits>::DeleteInternal(x);
  }
};

template <typename T, typename Traits = DefaultWeakableTraits<T>>
class Weakable {
 public:
  Weakable(T* ptr) : ptr_(ptr), weak_factory_(ptr) { DCHECK(ptr_); }
  ~Weakable() { Traits::Destruct(ptr_); };

  T* get() const { return ptr_; }
  base::WeakPtr<T> GetWeakPtr() { return weak_factory_.GetWeakPtr(); }

  T& operator*() const { return *get(); }
  T* operator->() const { return get(); }

 private:
  T* ptr_ = nullptr;
  base::WeakPtrFactory<T> weak_factory_;

  friend struct DefaultWeakableTraits<T>;
  template <typename U>
  static void DeleteInternal(const U* x) {
    delete x;
    x = nullptr;
  }

  DISALLOW_COPY_AND_ASSIGN(Weakable);
};

template <typename T, typename... Args>
Weakable<T>* MakeWeakable(Args&&... args) {
  return new Weakable<T>(new T(std::forward<Args>(args)...));
}

template <typename T>
Weakable<T>* WrapWeakable(T* ptr) {
  return new Weakable<T>(ptr);
}

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_WEAKABLE_H_
