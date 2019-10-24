#ifndef YEALINK_RTVC_BINDING_NATIVE_DESKTOP_MEDIA_LIST_H_
#define YEALINK_RTVC_BINDING_NATIVE_DESKTOP_MEDIA_LIST_H_

#include <memory>

#include "base/memory/weak_ptr.h"
#include "base/threading/thread.h"
#include "yealink/rtvc/binding/desktop_media_id.h"
#include "yealink/rtvc/binding/desktop_media_list_base.h"

namespace webrtc {
class DesktopCapturer;
}

namespace rtvc {

// Implementation of DesktopMediaList that shows native screens and
// native windows.
class NativeDesktopMediaList : public DesktopMediaListBase {
 public:
  NativeDesktopMediaList(DesktopMediaID::Type type,
                         std::unique_ptr<webrtc::DesktopCapturer> capturer);
  ~NativeDesktopMediaList() override;

 private:
  typedef std::map<DesktopMediaID, uint32_t> ImageHashesMap;

  class Worker;
  friend class Worker;

  // Refresh() posts a task for the |worker_| to update list of windows, get
  // thumbnails and schedule next refresh.
  void Refresh() override;

  void RefreshForAuraWindows(std::vector<SourceDescription> sources);
  void UpdateNativeThumbnailsFinished();

  base::Thread thread_;
  std::unique_ptr<Worker> worker_;

  base::WeakPtrFactory<NativeDesktopMediaList> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(NativeDesktopMediaList);
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_NATIVE_DESKTOP_MEDIA_LIST_H_
