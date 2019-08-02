#ifndef YEALINK_RTVC_BINDING_LIBUV_TASK_RUNNER_H_
#define YEALINK_RTVC_BINDING_LIBUV_TASK_RUNNER_H_

#include <vector>

#include "base/bind.h"
#include "base/macros.h"
#include "base/single_thread_task_runner.h"
#include "base/synchronization/lock.h"
#include "uv.h"

namespace yealink {

namespace node {

class LibuvTaskRunner : public base::SingleThreadTaskRunner {
 public:
  enum LibuvRunnerType { kLibuvIdleRunner, kLibuvAsyncRunner };

  // node.js use default loop as its main loop
  LibuvTaskRunner(uv_loop_t* loop = ::uv_default_loop(),
                  LibuvRunnerType task_type = kLibuvAsyncRunner);
  ~LibuvTaskRunner();

  // SingleThreadTaskRunner implementation.
  bool PostDelayedTask(const base::Location& from_here,
                       base::OnceClosure task,
                       base::TimeDelta delay) override;

  bool PostNonNestableDelayedTask(const base::Location& from_here,
                                  base::OnceClosure task,
                                  base::TimeDelta delay) override;

  bool RunsTasksInCurrentSequence() const override { return true; }

  void RunPendingTasks();

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

  void QueueDeferredTask(const base::Location& from_here,
                         base::OnceClosure task,
                         base::TimeDelta delay,
                         bool is_non_nestable);

  mutable base::Lock lock_;

  uv_loop_t* loop_;
  uv_async_t asyncer_;
  uv_idle_t idler_;
  LibuvRunnerType runner_type_;

  std::vector<DeferredTask> deferred_tasks_queue_;

  DISALLOW_COPY_AND_ASSIGN(LibuvTaskRunner);
};

}  // namespace node
}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_LIBUV_TASK_RUNNER_H_
