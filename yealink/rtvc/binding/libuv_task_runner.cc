#include "yealink/rtvc/binding/libuv_task_runner.h"

namespace yealink {

namespace node {

namespace {
void async_callback(uv_async_t* handle) {
  reinterpret_cast<LibuvTaskRunner*>(handle->data)->RunPendingTasks();
}
void idle_callback(uv_idle_t* handle) {
  reinterpret_cast<LibuvTaskRunner*>(handle->data)->RunPendingTasks();
}
}  // namespace

LibuvTaskRunner::LibuvTaskRunner(uv_loop_t* loop, LibuvRunnerType runner_type)
    : loop_(loop), runner_type_(runner_type) {
  DCHECK(loop);
  if (runner_type_ == kLibuvAsyncRunner) {
    ::uv_async_init(loop, &asyncer_, async_callback);
    asyncer_.data = this;
  } else if (runner_type_ == kLibuvIdleRunner) {
    ::uv_idle_init(loop, &idler_);
    idler_.data = this;
    ::uv_idle_start(&idler_, idle_callback);
  }
}
LibuvTaskRunner::~LibuvTaskRunner() {
  if (runner_type_ == kLibuvAsyncRunner) {
    ::uv_close((uv_handle_t*)(&asyncer_),
               [](uv_handle_t* handle) { free(handle); });
  } else if (runner_type_ == kLibuvIdleRunner) {
    ::uv_idle_stop(&idler_);
  }
}

bool LibuvTaskRunner::PostDelayedTask(const base::Location& location,
                                      base::OnceClosure callback,
                                      base::TimeDelta delay) {
  // if (runner_type_ == kLibuvAsyncRunner) {
  //   ::uv_async_send(&asyncer_);
  // }
  return false;
}
bool LibuvTaskRunner::PostNonNestableDelayedTask(
    const base::Location& from_here,
    base::OnceClosure task,
    base::TimeDelta delay) {
  // if (runner_type_ == kLibuvAsyncRunner) {
  //   ::uv_async_send(&asyncer_);
  // }
  return false;
}

void LibuvTaskRunner::RunPendingTasks() {}

}  // namespace node

}  // namespace yealink
