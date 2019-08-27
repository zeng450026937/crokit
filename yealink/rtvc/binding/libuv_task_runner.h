#ifndef YEALINK_RTVC_BINDING_LIBUV_TASK_RUNNER_H_
#define YEALINK_RTVC_BINDING_LIBUV_TASK_RUNNER_H_

#include <queue>

#include "base/bind.h"
#include "base/macros.h"
#include "base/single_thread_task_runner.h"
#include "base/synchronization/lock.h"
#include "uv.h"

namespace yealink {

namespace rtvc {

class LibuvTaskRunner : public base::SingleThreadTaskRunner {
 public:
  enum LibuvRunnerType {
    kLibuvAsyncRunner,
    kLibuvIdleRunner,
    kLibuvTimerRunner
  };

  // node.js use default loop as its main loop
  LibuvTaskRunner(uv_loop_t* loop = ::uv_default_loop(),
                  LibuvRunnerType task_type = kLibuvAsyncRunner);
  ~LibuvTaskRunner() override;

  // SingleThreadTaskRunner implementation.
  bool PostDelayedTask(const base::Location& from_here,
                       base::OnceClosure task,
                       base::TimeDelta delay) override;

  bool PostNonNestableDelayedTask(const base::Location& from_here,
                                  base::OnceClosure task,
                                  base::TimeDelta delay) override;

  bool RunsTasksInCurrentSequence() const override { return true; }


 private:
  struct DeferredTask {
    DeferredTask();
    DeferredTask(DeferredTask&& other);
    ~DeferredTask();
    DeferredTask& operator=(DeferredTask&& other);

    base::Location posted_from;
    base::OnceClosure task;
    // The delay this task was initially posted with.
    base::TimeDelta delay;
    bool is_non_nestable;
  };

  class Runner {
   public:
    virtual ~Runner() {}
  };
  class AsyncRunner;
  class IdleRunner;
  class TimerRunner;

  void EnsureTaskRunner();

  void QueueDeferredTask(const base::Location& from_here,
                         base::OnceClosure task,
                         base::TimeDelta delay,
                         bool is_non_nestable);

  void RunPendingTasks();

  mutable base::Lock lock_;

  uv_loop_t* loop_;
  LibuvRunnerType runner_type_;
  std::unique_ptr<Runner> runner_;
  std::queue<DeferredTask> deferred_tasks_queue_;

  DISALLOW_COPY_AND_ASSIGN(LibuvTaskRunner);
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_LIBUV_TASK_RUNNER_H_
