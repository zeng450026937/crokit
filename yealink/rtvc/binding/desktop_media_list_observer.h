#ifndef YEALINK_RTVC_BINDING_DESKTOP_MEDIA_LIST_OBSERVER_H_
#define YEALINK_RTVC_BINDING_DESKTOP_MEDIA_LIST_OBSERVER_H_

namespace yealink {

namespace rtvc {

class DesktopMediaList;

// Interface implemented by the desktop media picker dialog to receive
// notifications about changes in DesktopMediaList.
class DesktopMediaListObserver {
 public:
  virtual void OnSourceAdded(DesktopMediaList* list, int index) = 0;
  virtual void OnSourceRemoved(DesktopMediaList* list, int index) = 0;
  virtual void OnSourceMoved(DesktopMediaList* list,
                             int old_index,
                             int new_index) = 0;
  virtual void OnSourceNameChanged(DesktopMediaList* list, int index) = 0;
  virtual void OnSourceThumbnailChanged(DesktopMediaList* list, int index) = 0;

 protected:
  virtual ~DesktopMediaListObserver() {}
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_DESKTOP_MEDIA_LIST_OBSERVER_H_
