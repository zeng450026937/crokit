#include "yealink/rtvc/binding/libuv_task_runner.h"

namespace rtvc {

class LibuvTaskRunner::AsyncRunner : public LibuvTaskRunner::Runner {
 public:
  AsyncRunner(LibuvTaskRunner* delegate, uv_loop_t* loop = ::uv_default_loop())
      : delegate_(delegate), loop_(loop), async_(nullptr) {
    delegate_ = nullptr;
    async_ = new uv_async_t;
    async_->data = delegate;
    uv_async_init(loop_, async_, [](uv_async_t* handle) {
      reinterpret_cast<LibuvTaskRunner*>(handle->data)->RunPendingTasks();
    });
    ::uv_async_send(async_);
  }
  ~AsyncRunner() override {
    ::uv_close(reinterpret_cast<uv_handle_t*>(async_), [](uv_handle_t* handle) {
      delete reinterpret_cast<uv_async_t*>(handle);
    });
  }

 private:
  LibuvTaskRunner* delegate_;
  uv_loop_t* loop_;
  uv_async_t* async_;
};

class LibuvTaskRunner::IdleRunner : public LibuvTaskRunner::Runner {
 public:
  IdleRunner(LibuvTaskRunner* delegate, uv_loop_t* loop = ::uv_default_loop())
      : delegate_(delegate), loop_(loop), idle_(nullptr) {
    delegate_ = nullptr;
    idle_ = new uv_idle_t;
    idle_->data = delegate;
    uv_idle_init(loop_, idle_);
    ::uv_idle_start(idle_, [](uv_idle_t* handle) {
      reinterpret_cast<LibuvTaskRunner*>(handle->data)->RunPendingTasks();
    });
  }
  ~IdleRunner() override {
    ::uv_idle_stop(idle_);
    ::uv_close(reinterpret_cast<uv_handle_t*>(idle_), [](uv_handle_t* handle) {
      delete reinterpret_cast<uv_idle_t*>(handle);
    });
  }

 private:
  LibuvTaskRunner* delegate_;
  uv_loop_t* loop_;
  uv_idle_t* idle_;
};

class LibuvTaskRunner::TimerRunner : public LibuvTaskRunner::Runner {
 public:
  TimerRunner(LibuvTaskRunner* delegate, uv_loop_t* loop = ::uv_default_loop())
      : delegate_(delegate), loop_(loop), timer_(nullptr) {
    delegate_ = nullptr;
    timer_ = new uv_timer_t;
    timer_->data = delegate;
    uv_timer_init(loop_, timer_);
    ::uv_timer_start(
        timer_,
        [](uv_timer_t* handle) {
          reinterpret_cast<LibuvTaskRunner*>(handle->data)->RunPendingTasks();
        },
        0, 0);
  }
  ~TimerRunner() override {
    ::uv_timer_stop(timer_);
    uv_close(reinterpret_cast<uv_handle_t*>(timer_), [](uv_handle_t* handle) {
      delete reinterpret_cast<uv_timer_t*>(handle);
    });
  }

 private:
  LibuvTaskRunner* delegate_;
  uv_loop_t* loop_;
  uv_timer_t* timer_;
};

LibuvTaskRunner::DeferredTask::DeferredTask() : is_non_nestable(false) {}

LibuvTaskRunner::DeferredTask::DeferredTask(DeferredTask&& other) = default;

LibuvTaskRunner::DeferredTask::~DeferredTask() = default;

LibuvTaskRunner::DeferredTask& LibuvTaskRunner::DeferredTask::operator=(
    DeferredTask&& other) = default;

LibuvTaskRunner::LibuvTaskRunner(uv_loop_t* loop, LibuvRunnerType runner_type)
    : loop_(loop), runner_type_(runner_type) {
  DCHECK(loop);
}
LibuvTaskRunner::~LibuvTaskRunner() = default;

bool LibuvTaskRunner::PostDelayedTask(const base::Location& from_here,
                                      base::OnceClosure task,
                                      base::TimeDelta delay) {
  base::AutoLock lock(lock_);

  QueueDeferredTask(from_here, std::move(task), delay,
                    false /* is_non_nestable */);
  EnsureTaskRunner();
  
  return true;
}
bool LibuvTaskRunner::PostNonNestableDelayedTask(
    const base::Location& from_here,
    base::OnceClosure task,
    base::TimeDelta delay) {
  base::AutoLock lock(lock_);

  QueueDeferredTask(from_here, std::move(task), delay,
                    true /* is_non_nestable */);
  EnsureTaskRunner();

  return true;
}

void LibuvTaskRunner::RunPendingTasks() {
  while (true) {
    base::AutoLock lock(lock_);
    if (deferred_tasks_queue_.empty())
      break;
    std::move(deferred_tasks_queue_.front().task).Run();
    deferred_tasks_queue_.pop();
  }

  runner_.reset();
}

void LibuvTaskRunner::EnsureTaskRunner() {
  if (runner_.get())
    return;

  if (runner_type_ == kLibuvAsyncRunner) {
    runner_.reset(new AsyncRunner(this, loop_));
  } else if (runner_type_ == kLibuvIdleRunner) {
    runner_.reset(new IdleRunner(this, loop_));
  } else if (runner_type_ == kLibuvTimerRunner) {
    runner_.reset(new TimerRunner(this, loop_));
  }
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
  deferred_tasks_queue_.push(std::move(deferred_task));
}

}  // namespace rtvc

