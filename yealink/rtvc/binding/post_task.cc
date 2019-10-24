#include "yealink/rtvc/binding/post_task.h"

#include "uv.h"

namespace rtvc {

namespace {
uv_async_t handle;
}

void PostTask(base::OnceClosure task) {
  uv_loop_t* loop = ::uv_default_loop();
  handle.data = task;
  handle.
  ::uv_async_init(loop, &handle, [](uv_async_t* handle) {
    reinterpret_cast<base::OnceClosure>(handle->data).Run();
  });
}

}  // namespace rtvc
