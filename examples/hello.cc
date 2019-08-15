#include <iostream>
#include <string>

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

int main() {
  std::cout << "hello gn." << std::endl;

  write_line(1, "--", "2.2.2", "--", 3.0);
}
