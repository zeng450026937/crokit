#ifndef YEALINK_RTVC_BINDING_DESKTOP_MEDIA_LIST_H_
#define YEALINK_RTVC_BINDING_DESKTOP_MEDIA_LIST_H_

#include "base/strings/string16.h"
#include "base/strings/stringprintf.h"
#include "base/time/time.h"
#include "yealink/rtvc/binding/desktop_media_id.h"

namespace rtvc {

class DesktopMediaListObserver;

class ThumbnailSize {
 public:
  ThumbnailSize() : width_(0), height_(0) {}
  ThumbnailSize(int width, int height)
      : width_(width < 0 ? 0 : width), height_(height < 0 ? 0 : height) {}

  constexpr int width() const { return width_; }
  constexpr int height() const { return height_; }

  void set_width(int width) { width_ = width < 0 ? 0 : width; }
  void set_height(int height) { height_ = height < 0 ? 0 : height; }

  void SetSize(int width, int height) {
    set_width(width);
    set_height(height);
  }

  bool IsEmpty() const { return !width() || !height(); }

  std::string ToString() const {
    return base::StringPrintf("%dx%d", width(), height());
  }

 private:
  int width_;
  int height_;
};

// DesktopMediaList provides the list of desktop media source (screens, windows,
// tabs), and their thumbnails, to the desktop media picker dialog. It
// transparently updates the list in the background, and notifies the desktop
// media picker when something changes.
class DesktopMediaList {
 public:
  // Struct used to represent each entry in the list.
  struct Source {
    // Id of the source.
    DesktopMediaID id;

    // Name of the source that should be shown to the user.
    base::string16 name;

    // The thumbnail for the source.
    // gfx::ImageSkia thumbnail;
  };

  virtual ~DesktopMediaList() {}

  // Sets time interval between updates. By default list of sources and their
  // thumbnail are updated once per second. If called after StartUpdating() then
  // it will take effect only after the next update.
  virtual void SetUpdatePeriod(base::TimeDelta period) = 0;

  // Sets size to which the thumbnails should be scaled. If called after
  // StartUpdating() then some thumbnails may be still scaled to the old size
  // until they are updated.
  virtual void SetThumbnailSize(const ThumbnailSize& thumbnail_size) = 0;

  // Sets ID of the hosting desktop picker dialog. The window with this ID will
  // be filtered out from the list of sources.
  virtual void SetViewDialogWindowId(DesktopMediaID dialog_id) = 0;

  // Starts updating the model. The model is initially empty, so OnSourceAdded()
  // notifications will be generated for each existing source as it is
  // enumerated. After the initial enumeration the model will be refreshed based
  // on the update period, and notifications generated only for changes in the
  // model.
  virtual void StartUpdating(DesktopMediaListObserver* observer) = 0;

  virtual int GetSourceCount() const = 0;
  virtual const Source& GetSource(int index) const = 0;
  virtual const std::vector<Source>& GetSources() const = 0;

  virtual DesktopMediaID::Type GetMediaListType() const = 0;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_DESKTOP_MEDIA_LIST_H_
