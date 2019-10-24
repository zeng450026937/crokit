#ifndef YEALINK_RTVC_BINDING_DESKTOP_CAPTURE_H_
#define YEALINK_RTVC_BINDING_DESKTOP_CAPTURE_H_

#include "third_party/webrtc/modules/desktop_capture/desktop_capture_options.h"
#include "third_party/webrtc/modules/desktop_capture/desktop_capturer.h"

namespace desktop_capture {

// Creates a DesktopCaptureOptions with required settings.
webrtc::DesktopCaptureOptions CreateDesktopCaptureOptions();

// Creates specific DesktopCapturer with required settings.
std::unique_ptr<webrtc::DesktopCapturer> CreateScreenCapturer();
std::unique_ptr<webrtc::DesktopCapturer> CreateWindowCapturer();

}  // namespace desktop_capture

#endif  // YEALINK_RTVC_BINDING_DESKTOP_CAPTURE_H_
