// Copyright (c) 2015 GitHub, Inc.
// Use of this source code is governed by the MIT license that can be
// found in the LICENSE file.

#include <utility>

#include "yealink/rtvc/binding/uv_task_runner.h"

#include "base/stl_util.h"

namespace yealink {

namespace rtvc {

UvTaskRunner::UvTaskRunner(uv_loop_t* loop) : loop_(loop) {}

UvTaskRunner::~UvTaskRunner() {
  for (auto& iter : timer_tasks_) {
    uv_unref(reinterpret_cast<uv_handle_t*>(iter.first));
    delete iter.first;
  }
  for (auto& iter : idle_tasks_) {
    uv_unref(reinterpret_cast<uv_handle_t*>(iter.first));
    delete iter.first;
  }
  for (auto& iter : async_tasks_) {
    uv_unref(reinterpret_cast<uv_handle_t*>(iter.first));
    delete iter.first;
  }
}

bool UvTaskRunner::PostDelayedTask(const base::Location& from_here,
                                   base::OnceClosure task,
                                   base::TimeDelta delay) {
  int type = 0;
  if (type == 0) {
    auto* timer = new uv_timer_t;
    timer->data = this;
    uv_timer_init(loop_, timer);
    uv_timer_start(timer, UvTaskRunner::OnTimeout, delay.InMilliseconds(),
                   0);
    timer_tasks_[timer] = std::move(task);
  }
  if (type == 1) {
    auto* idle = new uv_idle_t;
    idle->data = this;
    uv_idle_init(loop_, idle);
    uv_idle_start(idle, UvTaskRunner::OnIdle);
    idle_tasks_[idle] = std::move(task);
  }
  if (type == 2) {
    auto* async = new uv_async_t;
    async->data = this;
    uv_async_init(loop_, async, UvTaskRunner::OnAsync);
    uv_async_send(async);
    async_tasks_[async] = std::move(task);
  }
  return true;
}

bool UvTaskRunner::RunsTasksInCurrentSequence() const {
  return true;
}

bool UvTaskRunner::PostNonNestableDelayedTask(const base::Location& from_here,
                                              base::OnceClosure task,
                                              base::TimeDelta delay) {
  return PostDelayedTask(from_here, std::move(task), delay);
}

// static
void UvTaskRunner::OnTimeout(uv_timer_t* timer) {
  UvTaskRunner* self = static_cast<UvTaskRunner*>(timer->data);
  if (!ContainsKey(self->timer_tasks_, timer))
    return;

  std::move(self->timer_tasks_[timer]).Run();
  self->timer_tasks_.erase(timer);
  uv_timer_stop(timer);
  uv_close(reinterpret_cast<uv_handle_t*>(timer), UvTaskRunner::OnClose);
}

// static
void UvTaskRunner::OnIdle(uv_idle_t* idle) {
  UvTaskRunner* self = static_cast<UvTaskRunner*>(idle->data);
  if (!ContainsKey(self->idle_tasks_, idle))
    return;

  std::move(self->idle_tasks_[idle]).Run();
  self->idle_tasks_.erase(idle);
  uv_idle_stop(idle);
  uv_close(reinterpret_cast<uv_handle_t*>(idle), UvTaskRunner::OnIdleClose);
}
// static
void UvTaskRunner::OnAsync(uv_async_t* async) {
  UvTaskRunner* self = static_cast<UvTaskRunner*>(async->data);
  if (!ContainsKey(self->async_tasks_, async))
    return;

  std::move(self->async_tasks_[async]).Run();
  self->async_tasks_.erase(async);
  // uv_unref(reinterpret_cast<uv_handle_t*>(async));
  uv_close(reinterpret_cast<uv_handle_t*>(async), UvTaskRunner::OnAsyncClose);
}

// static
void UvTaskRunner::OnClose(uv_handle_t* handle) {
  delete reinterpret_cast<uv_timer_t*>(handle);
}
// static
void UvTaskRunner::OnIdleClose(uv_handle_t* handle) {
  delete reinterpret_cast<uv_idle_t*>(handle);
}// static
void UvTaskRunner::OnAsyncClose(uv_handle_t* handle) {
  delete reinterpret_cast<uv_async_t*>(handle);
}


}  // namespace rtvc

}  // namespace yealink
