#ifndef YEALINK_RTVC_BINDING_TASK_RUNNER_LIBUV_H_
#define YEALINK_RTVC_BINDING_TASK_RUNNER_LIBUV_H_

#include <map>

#include "base/callback.h"
#include "base/location.h"
#include "base/single_thread_task_runner.h"
#include "uv.h"  // NOLINT(build/include)

namespace yealink {

namespace rtvc {

// TaskRunner implementation that posts tasks into libuv's default loop.
class TaskRunnerLibuv : public base::SingleThreadTaskRunner {
 public:
  explicit TaskRunnerLibuv(uv_loop_t* loop = ::uv_default_loop());

  // base::SingleThreadTaskRunner:
  bool PostDelayedTask(const base::Location& from_here,
                       base::OnceClosure task,
                       base::TimeDelta delay) override;
  bool RunsTasksInCurrentSequence() const override;
  bool PostNonNestableDelayedTask(const base::Location& from_here,
                                  base::OnceClosure task,
                                  base::TimeDelta delay) override;

 private:
  ~TaskRunnerLibuv() override;
  static void OnTimeout(uv_timer_t* timer);
  static void OnIdle(uv_idle_t* idle);
  static void OnAsync(uv_async_t* async);
  static void OnClose(uv_handle_t* handle);
  static void OnIdleClose(uv_handle_t* handle);
  static void OnAsyncClose(uv_handle_t* handle);

  uv_loop_t* loop_;

  std::map<uv_timer_t*, base::OnceClosure> timer_tasks_;
  std::map<uv_idle_t*, base::OnceClosure> idle_tasks_;
  std::map<uv_async_t*, base::OnceClosure> async_tasks_;

  DISALLOW_COPY_AND_ASSIGN(TaskRunnerLibuv);
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_TASK_RUNNER_LIBUV_H_
