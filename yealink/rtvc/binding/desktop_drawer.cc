#include "yealink/rtvc/binding/desktop_drawer.h"

#include "base/bind.h"
#include "base/logging.h"
#include "base/task/post_task.h"
#include "base/threading/thread_checker.h"
#include "base/threading/thread_restrictions.h"
#include "base/timer/timer.h"
#include "build/build_config.h"

namespace yealink {

namespace rtvc {

// static
std::unique_ptr<DesktopDrawer> DesktopDrawer::Create() {
  return std::unique_ptr<DesktopDrawer>(
      new DesktopDrawer(webrtc::ScreenDrawer::Create()));
}

DesktopDrawer::DesktopDrawer(std::unique_ptr<webrtc::ScreenDrawer> drawer)
    : drawer_(std::move(drawer)), window_id_(0), weak_factory_(this) {
      drawer_->window_id();
  // timer_.SetTaskRunner(
  //     base::CreateSequencedTaskRunnerWithTraits(base::TaskTraits()));
}
DesktopDrawer::~DesktopDrawer() {
  timer_.Stop();
}

void DesktopDrawer::SetTrackedWindow(intptr_t window_id) {
  window_id_ = window_id;
  if (!timer_.IsRunning()) {
    timer_.Start(FROM_HERE, base::TimeDelta::FromMilliseconds(500),
                 base::BindRepeating(&DesktopDrawer::DrawRectangle,
                                     weak_factory_.GetWeakPtr()));
  }
  DrawRectangle();
}

void DesktopDrawer::DrawRectangle() {
#ifdef OS_WIN
  if (!window_id_) {
    timer_.Stop();
    return;
  }

  HWND window = reinterpret_cast<HWND>(window_id_);

  if (!::IsWindow(window) || !::IsWindowVisible(window)) {
    timer_.Stop();
    return;
  }

  RECT window_rect;
  std::memset(&window_rect, 0, sizeof(RECT));
  ::GetWindowRect(window, &window_rect);

  webrtc::DesktopRect rectangle_rect = webrtc::DesktopRect::MakeLTRB(
      window_rect.left - 4, window_rect.top - 4, window_rect.right + 4,
      window_rect.bottom + 4);

  webrtc::RgbaColor rectangle_color(0, 0, 255);

  drawer_->DrawRectangle(rectangle_rect, rectangle_color);
#endif
}

}  // namespace rtvc

}  // namespace yealink
