#include "yealink/rtvc/binding/desktop_capture.h"

#include "base/feature_list.h"
#include "build/build_config.h"

namespace yealink {
namespace desktop_capture {

webrtc::DesktopCaptureOptions CreateDesktopCaptureOptions() {
  auto options = webrtc::DesktopCaptureOptions::CreateDefault();
  // Leave desktop effects enabled during WebRTC captures.
  options.set_disable_effects(false);
#if defined(OS_WIN)
  static constexpr base::Feature kDirectXCapturer{
      "DirectXCapturer", base::FEATURE_ENABLED_BY_DEFAULT};
  if (base::FeatureList::IsEnabled(kDirectXCapturer)) {
    options.set_allow_directx_capturer(true);
    options.set_allow_use_magnification_api(false);
  } else {
    options.set_allow_use_magnification_api(true);
  }
#elif defined(OS_MACOSX)
  static constexpr base::Feature kIOSurfaceCapturer{
      "IOSurfaceCapturer", base::FEATURE_ENABLED_BY_DEFAULT};
  if (base::FeatureList::IsEnabled(kIOSurfaceCapturer)) {
    options.set_allow_iosurface(true);
  }
#endif
#if defined(WEBRTC_USE_PIPEWIRE)
  static constexpr base::Feature kWebRtcPipeWireCapturer{
      "WebRTCPipeWireCapturer", base::FEATURE_DISABLED_BY_DEFAULT};
  if (base::FeatureList::IsEnabled(kWebRtcPipeWireCapturer)) {
    options.set_allow_pipewire(true);
  }
#endif  // defined(WEBRTC_USE_PIPEWIRE)
  return options;
}

std::unique_ptr<webrtc::DesktopCapturer> CreateScreenCapturer() {
  return webrtc::DesktopCapturer::CreateScreenCapturer(
      CreateDesktopCaptureOptions());
}

std::unique_ptr<webrtc::DesktopCapturer> CreateWindowCapturer() {
  return webrtc::DesktopCapturer::CreateWindowCapturer(
      CreateDesktopCaptureOptions());
}

}  // namespace desktop_capture
}  // namespace yealink
