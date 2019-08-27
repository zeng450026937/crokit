#ifndef YEALINK_RTVC_BINDING_UV_TASK_RUNNER_H_
#define YEALINK_RTVC_BINDING_UV_TASK_RUNNER_H_

#include <map>

#include "base/callback.h"
#include "base/location.h"
#include "base/single_thread_task_runner.h"
#include "uv.h"  // NOLINT(build/include)

namespace yealink {

namespace rtvc {

// TaskRunner implementation that posts tasks into libuv's default loop.
class UvTaskRunner : public base::SingleThreadTaskRunner {
 public:
  explicit UvTaskRunner(uv_loop_t* loop = ::uv_default_loop());

  // base::SingleThreadTaskRunner:
  bool PostDelayedTask(const base::Location& from_here,
                       base::OnceClosure task,
                       base::TimeDelta delay) override;
  bool RunsTasksInCurrentSequence() const override;
  bool PostNonNestableDelayedTask(const base::Location& from_here,
                                  base::OnceClosure task,
                                  base::TimeDelta delay) override;

 private:
  ~UvTaskRunner() override;
  static void OnTimeout(uv_timer_t* timer);
  static void OnClose(uv_handle_t* handle);

  uv_loop_t* uv_loop_;

  std::map<uv_timer_t*, base::OnceClosure> tasks_;

  DISALLOW_COPY_AND_ASSIGN(UvTaskRunner);
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_UV_TASK_RUNNER_H_
