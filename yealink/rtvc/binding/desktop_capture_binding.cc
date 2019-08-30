#include "yealink/rtvc/binding/desktop_capture_binding.h"

#include "base/hash.h"
#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/utf_string_conversions.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/binding/desktop_capture.h"
#include "yealink/rtvc/binding/desktop_media_list.h"

#include "third_party/webrtc/modules/desktop_capture/desktop_capture_options.h"
#include "third_party/webrtc/modules/desktop_capture/desktop_capturer.h"

#if defined(OS_WIN)
#include "third_party/webrtc/modules/desktop_capture/win/dxgi_duplicator_controller.h"
#include "third_party/webrtc/modules/desktop_capture/win/screen_capturer_win_directx.h"
#endif  // defined(OS_WIN)

namespace {
int64_t DeviceIdFromDeviceName(const wchar_t* device_name) {
  return static_cast<int64_t>(base::Hash(base::WideToUTF8(device_name)));
}
}  // namespace

namespace mate {

template <>
struct Converter<yealink::rtvc::DesktopCaptureBinding::Source> {
  static v8::Local<v8::Value> ToV8(
      v8::Isolate* isolate,
      const yealink::rtvc::DesktopCaptureBinding::Source& source) {
    mate::Dictionary dict(isolate, v8::Object::New(isolate));
    yealink::rtvc::DesktopMediaID id = source.media_list_source.id;
    dict.Set("name", base::UTF16ToUTF8(source.media_list_source.name));
    dict.Set("id", id.ToString());
    dict.Set("display_id", source.display_id);
    return ConvertToV8(isolate, dict);
  }
};

template <>
struct Converter<yealink::rtvc::ThumbnailSize> {
  static bool FromV8(v8::Isolate* isolate,
                     v8::Local<v8::Value> val,
                     yealink::rtvc::ThumbnailSize* out) {
    Dictionary dict;
    if (!ConvertFromV8(isolate, val, &dict))
      return false;
    int64_t width;
    int64_t height;
    dict.Get("width", &width);
    dict.Get("height", &height);
    out->set_width(width);
    out->set_height(height);
    return true;
  }
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::rtvc::ThumbnailSize& size) {
    mate::Dictionary dict(isolate, v8::Object::New(isolate));
    dict.Set("width", size.width());
    dict.Set("height", size.height());
    return ConvertToV8(isolate, dict);
  }
};

}  // namespace mate

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* DesktopCaptureBinding::New(mate::Arguments* args) {
  return new DesktopCaptureBinding(args->isolate(), args->GetThis());
}

// static
mate::Handle<DesktopCaptureBinding> DesktopCaptureBinding::Create(
    v8::Isolate* isolate) {
  return mate::CreateHandle(isolate, new DesktopCaptureBinding(isolate));
}

// static
void DesktopCaptureBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "DesktopCapture"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetMethod("startHandling", &DesktopCaptureBinding::StartHandling)
      .SetMethod("getSources", &DesktopCaptureBinding::GetSources);
}

DesktopCaptureBinding::DesktopCaptureBinding(v8::Isolate* isolate,
                                             v8::Local<v8::Object> wrapper) {
  InitWith(isolate, wrapper);
}
DesktopCaptureBinding::DesktopCaptureBinding(v8::Isolate* isolate) {
  Init(isolate);
}
DesktopCaptureBinding::~DesktopCaptureBinding() {}

v8::Local<v8::Promise> DesktopCaptureBinding::GetSources(
    mate::Dictionary options) {
  bool capture_window = false;
  bool capture_screen = false;
  bool fetch_window_icons = false;
  ThumbnailSize thumbnail_size;

  options.Get("captureWindow", &capture_window);
  options.Get("captureScreen", &capture_screen);
  options.Get("fetchWindowIcons", &fetch_window_icons);
  options.Get("thumbnailSize", &thumbnail_size);

  if (!capture_screen && !capture_window)
    return Promise::ResolvedPromise(isolate());

  if (!getsources_promise_) {
    getsources_promise_.reset(new Promise(isolate()));

    StartHandling(capture_window, capture_screen, thumbnail_size,
                  fetch_window_icons);
  }

  return getsources_promise_->GetHandle();
}

void DesktopCaptureBinding::StartHandling(bool capture_window,
                                          bool capture_screen,
                                          const ThumbnailSize& thumbnail_size,
                                          bool fetch_window_icons) {
  fetch_window_icons_ = fetch_window_icons;
#if defined(OS_WIN)
  if (yealink::desktop_capture::CreateDesktopCaptureOptions()
          .allow_directx_capturer()) {
    // DxgiDuplicatorController should be alive in this scope according to
    // screen_capturer_win.cc.
    auto duplicator = webrtc::DxgiDuplicatorController::Instance();
    using_directx_capturer_ = webrtc::ScreenCapturerWinDirectx::IsSupported();
  }
#endif  // defined(OS_WIN)

  // clear any existing captured sources.
  captured_sources_.clear();

  // Start listening for captured sources.
  capture_window_ = capture_window;
  capture_screen_ = capture_screen;

  {
    // Initialize the source list.
    // Apply the new thumbnail size and restart capture.
    if (capture_window) {
      window_capturer_.reset(new NativeDesktopMediaList(
          DesktopMediaID::TYPE_WINDOW,
          yealink::desktop_capture::CreateWindowCapturer()));
      window_capturer_->SetThumbnailSize(thumbnail_size);
      window_capturer_->StartUpdating(this);
    }

    if (capture_screen) {
      screen_capturer_.reset(new NativeDesktopMediaList(
          DesktopMediaID::TYPE_SCREEN,
          yealink::desktop_capture::CreateScreenCapturer()));
      screen_capturer_->SetThumbnailSize(thumbnail_size);
      screen_capturer_->StartUpdating(this);
    }
  }
}

void DesktopCaptureBinding::OnSourceAdded(DesktopMediaList* list, int index) {}
void DesktopCaptureBinding::OnSourceRemoved(DesktopMediaList* list, int index) {
}
void DesktopCaptureBinding::OnSourceMoved(DesktopMediaList* list,
                                          int old_index,
                                          int new_index) {}
void DesktopCaptureBinding::OnSourceNameChanged(DesktopMediaList* list,
                                                int index) {}
void DesktopCaptureBinding::OnSourceThumbnailChanged(DesktopMediaList* list,
                                                     int index) {}

void DesktopCaptureBinding::OnSourceUnchanged(DesktopMediaList* list) {
  UpdateSourcesList(list);
}

bool DesktopCaptureBinding::ShouldScheduleNextRefresh(DesktopMediaList* list) {
  UpdateSourcesList(list);
  if (!capture_window_ && window_capturer_)
    window_capturer_.reset();
  if (!capture_screen_ && screen_capturer_)
    screen_capturer_.reset();
  return false;
}

void DesktopCaptureBinding::UpdateSourcesList(DesktopMediaList* list) {
  if (capture_window_ &&
      list->GetMediaListType() == DesktopMediaID::TYPE_WINDOW) {
    capture_window_ = false;
    const auto& media_list_sources = list->GetSources();
    std::vector<DesktopCaptureBinding::Source> window_sources;
    window_sources.reserve(media_list_sources.size());
    for (const auto& media_list_source : media_list_sources) {
      window_sources.emplace_back(DesktopCaptureBinding::Source{
          media_list_source, std::string(), fetch_window_icons_});
    }
    std::move(window_sources.begin(), window_sources.end(),
              std::back_inserter(captured_sources_));
  }

  if (capture_screen_ &&
      list->GetMediaListType() == DesktopMediaID::TYPE_SCREEN) {
    capture_screen_ = false;
    const auto& media_list_sources = list->GetSources();
    std::vector<DesktopCaptureBinding::Source> screen_sources;
    screen_sources.reserve(media_list_sources.size());
    for (const auto& media_list_source : media_list_sources) {
      screen_sources.emplace_back(
          DesktopCaptureBinding::Source{media_list_source, std::string()});
    }
#if defined(OS_WIN)
    // Gather the same unique screen IDs used by the electron.screen API in
    // order to provide an association between it and
    // DesktopCapture/getUserMedia. This is only required when using the
    // DirectX capturer, otherwise the IDs across the APIs already match.
    if (using_directx_capturer_) {
      std::vector<std::string> device_names;
      // Crucially, this list of device names will be in the same order as
      // |media_list_sources|.
      if (!webrtc::DxgiDuplicatorController::Instance()->GetDeviceNames(
              &device_names)) {
        Emit("error", "Failed to get sources.");
        if (getsources_promise_) {
          std::unique_ptr<Promise> promise(getsources_promise_.release());
          promise->Reject("Failed to get sources.");
        }
        return;
      }

      int device_name_index = 0;
      for (auto& source : screen_sources) {
        const auto& device_name = device_names[device_name_index++];
        std::wstring wide_device_name;
        base::UTF8ToWide(device_name.c_str(), device_name.size(),
                         &wide_device_name);
        const int64_t device_id =
            DeviceIdFromDeviceName(wide_device_name.c_str());
        source.display_id = base::NumberToString(device_id);
      }
    }
#elif defined(OS_MACOSX)
    // On Mac, the IDs across the APIs match.
    for (auto& source : screen_sources) {
      source.display_id = base::NumberToString(source.media_list_source.id.id);
    }
#endif  // defined(OS_WIN)
    // TODO(ajmacd): Add Linux support. The IDs across APIs differ but Chrome
    // only supports capturing the entire desktop on Linux. Revisit this if
    // individual screen support is added.
    std::move(screen_sources.begin(), screen_sources.end(),
              std::back_inserter(captured_sources_));
  }

  if (!capture_window_ && !capture_screen_) {
    Emit("finished", captured_sources_, fetch_window_icons_);
    if (getsources_promise_) {
      std::unique_ptr<Promise> promise(getsources_promise_.release());
      promise->Resolve(captured_sources_);
    }
  }
}

}  // namespace rtvc

}  // namespace yealink
