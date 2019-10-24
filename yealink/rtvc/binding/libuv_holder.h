#ifndef YEALINK_RTVC_BINDING_LIBUV_HOLDER_H_
#define YEALINK_RTVC_BINDING_LIBUV_HOLDER_H_

#include "base/memory/ref_counted.h"
#include "uv.h"

namespace rtvc {

class LibUVHolder : public base::RefCounted<LibUVHolder> {
 public:
  LibUVHolder(uv_loop_t* loop = ::uv_default_loop()) {
    handle_ = new uv_async_t;
    ::uv_async_init(loop, handle_, [](uv_async_t* handle) {});
  }
  ~LibUVHolder() {
    ::uv_unref((uv_handle_t*)handle_);
    ::uv_close(reinterpret_cast<uv_handle_t*>(handle_),
               [](uv_handle_t* handle) {
                 delete reinterpret_cast<uv_async_t*>(handle);
               });
  }

 private:
  uv_async_t* handle_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_LIBUV_HOLDER_H_
