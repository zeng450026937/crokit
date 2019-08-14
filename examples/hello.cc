#include <iostream>
#include <string>

#include "base/memory/ref_counted.h"
#include "yealink/rtvc/binding/weakable.h"
#include "yealink/rtvc/binding/refcounted_wrapper.h"

class Dummy {
 public:
  Dummy() { std::cout << "Dummy" << std::endl; }
  Dummy(std::string name) { std::cout << "Dummy:" << name << std::endl; }
  ~Dummy() { std::cout << "~Dummy" << std::endl; }
};

template <typename... T>
void dummy_wrapper(T... t){};

template <class T>
T unpacker(const T t) {
  std::cout << '[' << t << ']';
  return t;
}

template <typename... Args>
void write_line(const Args&... data) {
  dummy_wrapper(unpacker(data)...);
  std::cout << '\n';
}

using WeakableDummy = yealink::rtvc::Weakable<Dummy>;
using RefCountedDummy = yealink::rtvc::RefCounted<Dummy>;

int main() {
  std::cout << "hello gn." << std::endl;

  base::WeakPtr<Dummy> weak_dummy;

  {
    WeakableDummy* dummy = yealink::rtvc::WrapWeakable<Dummy>(new Dummy());
    weak_dummy = dummy->GetWeakPtr();

    std::cout << "valid: " << weak_dummy.MaybeValid() << std::endl;

    delete dummy;
  }

  std::cout << "valid: " << weak_dummy.MaybeValid() << std::endl;

  scoped_refptr<RefCountedDummy> scoped_dummy = base::MakeRefCounted<RefCountedDummy>();

  scoped_dummy->

  write_line(1, "--", "2.2.2", "--", 3.0);
}
