#ifndef YEALINK_RTVC_BINDING_DESKTOP_DRAWER_H_
#define YEALINK_RTVC_BINDING_DESKTOP_DRAWER_H_

#include "base/timer/timer.h"
#include "base/memory/weak_ptr.h"
#include "third_party/webrtc/modules/desktop_capture/screen_drawer.h"

namespace rtvc {

class DesktopDrawer {
 public:
  static std::unique_ptr<DesktopDrawer> Create();

  explicit DesktopDrawer(std::unique_ptr<webrtc::ScreenDrawer> drawer);
  ~DesktopDrawer();

  void SetTrackedWindow(intptr_t window_id);

 protected:
  void DrawRectangle();

 private:
  std::unique_ptr<webrtc::ScreenDrawer> drawer_;
  intptr_t window_id_;

  base::RepeatingTimer timer_;
  base::WeakPtrFactory<DesktopDrawer> weak_factory_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_DESKTOP_DRAWER_H_
