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

LibuvTaskRunner::DeferredTask::DeferredTask() : is_non_nestable(false) {}

LibuvTaskRunner::DeferredTask::DeferredTask(DeferredTask&& other) = default;

LibuvTaskRunner::DeferredTask::~DeferredTask() = default;

LibuvTaskRunner::DeferredTask& LibuvTaskRunner::DeferredTask::operator=(
    DeferredTask&& other) = default;

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

bool LibuvTaskRunner::PostDelayedTask(const base::Location& from_here,
                                      base::OnceClosure task,
                                      base::TimeDelta delay) {
  if (runner_type_ == kLibuvAsyncRunner) {
    base::AutoLock lock(lock_);

    QueueDeferredTask(from_here, std::move(task), delay,
                      false /* is_non_nestable */);

    ::uv_async_send(&asyncer_);
  }
  return false;
}
bool LibuvTaskRunner::PostNonNestableDelayedTask(
    const base::Location& from_here,
    base::OnceClosure task,
    base::TimeDelta delay) {
  if (runner_type_ == kLibuvAsyncRunner) {
    base::AutoLock lock(lock_);

    QueueDeferredTask(from_here, std::move(task), delay,
                      true /* is_non_nestable */);

    ::uv_async_send(&asyncer_);
  }
  return false;
}

void LibuvTaskRunner::RunPendingTasks() {
  base::AutoLock lock(lock_);

  for (auto& task : deferred_tasks_queue_) {
    std::move(task.task).Run();
  }
  
  deferred_tasks_queue_.clear();
}

void LibuvTaskRunner::QueueDeferredTask(const base::Location& from_here,
                                        base::OnceClosure task,
                                        base::TimeDelta delay,
                                        bool is_non_nestable) {
  lock_.AssertAcquired();

  // Use CHECK instead of DCHECK to crash earlier. See http://crbug.com/711167
  // for details.
  CHECK(task);

  DeferredTask deferred_task;
  deferred_task.posted_from = from_here;
  deferred_task.task = std::move(task);
  deferred_task.delay = delay;
  deferred_task.is_non_nestable = is_non_nestable;
  deferred_tasks_queue_.push_back(std::move(deferred_task));
}

}  // namespace node

}  // namespace yealink
