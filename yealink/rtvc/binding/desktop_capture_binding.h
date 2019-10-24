#ifndef YEALINK_RTVC_BINDING_DESKTOP_CAPTURE_BINDING_H_
#define YEALINK_RTVC_BINDING_DESKTOP_CAPTURE_BINDING_H_

#include "base/macros.h"
#include "yealink/native_mate/dictionary.h"
#include "yealink/native_mate/handle.h"
#include "yealink/rtvc/binding/desktop_media_list_observer.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/native_desktop_media_list.h"
#include "yealink/rtvc/binding/promise.h"

namespace rtvc {

class DesktopCaptureBinding
    : public mate::EventEmitter<DesktopCaptureBinding>,
      public DesktopMediaListObserver {
 public:
  struct Source {
    DesktopMediaList::Source media_list_source;
    // Will be an empty string if not available.
    std::string display_id;

    // Whether or not this source should provide an icon.
    bool fetch_icon = false;
  };

  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<DesktopCaptureBinding> Create(v8::Isolate* isolate);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  DesktopCaptureBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  DesktopCaptureBinding(v8::Isolate* isolate);
  ~DesktopCaptureBinding() override;

  v8::Local<v8::Promise> GetSources(mate::Dictionary options);

  void StartHandling(bool capture_window,
                     bool capture_screen,
                     const ThumbnailSize& thumbnail_size,
                     bool fetch_window_icons);

  // DesktopMediaListObserver overrides.
  void OnSourceAdded(DesktopMediaList* list, int index) override;
  void OnSourceRemoved(DesktopMediaList* list, int index) override;
  void OnSourceMoved(DesktopMediaList* list,
                     int old_index,
                     int new_index) override;
  void OnSourceNameChanged(DesktopMediaList* list, int index) override;
  void OnSourceThumbnailChanged(DesktopMediaList* list, int index) override;
  void OnSourceUnchanged(DesktopMediaList* list) override;
  bool ShouldScheduleNextRefresh(DesktopMediaList* list) override;

 private:
  void UpdateSourcesList(DesktopMediaList* list);

  std::unique_ptr<DesktopMediaList> window_capturer_;
  std::unique_ptr<DesktopMediaList> screen_capturer_;
  std::vector<DesktopCaptureBinding::Source> captured_sources_;
  bool capture_window_ = false;
  bool capture_screen_ = false;
  bool fetch_window_icons_ = false;
#if defined(OS_WIN)
  bool using_directx_capturer_ = false;
#endif  // defined(OS_WIN)

  std::unique_ptr<Promise> getsources_promise_;

  DISALLOW_COPY_AND_ASSIGN(DesktopCaptureBinding);
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_DESKTOP_CAPTURE_BINDING_H_
