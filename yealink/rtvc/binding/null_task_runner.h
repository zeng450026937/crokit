#ifndef YEALINK_RTVC_BINDING_NULL_TASK_RUNNER_H_
#define YEALINK_RTVC_BINDING_NULL_TASK_RUNNER_H_

#include "base/single_thread_task_runner.h"

namespace yealink {

namespace node {

class NullTaskRunner final : public base::SingleThreadTaskRunner {
 public:
  NullTaskRunner() {}
  ~NullTaskRunner() override = default;

  bool PostDelayedTask(const base::Location& location,
                       base::OnceClosure callback,
                       base::TimeDelta delay) override {
    return false;
  }

  bool PostNonNestableDelayedTask(const base::Location& location,
                                  base::OnceClosure callback,
                                  base::TimeDelta delay) override {
    return false;
  }

  bool RunsTasksInCurrentSequence() const override { return true; }
};

}  // namespace node

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_NULL_TASK_RUNNER_H_
