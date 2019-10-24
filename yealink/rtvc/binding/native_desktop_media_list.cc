#include "yealink/rtvc/binding/native_desktop_media_list.h"

#include "base/bind.h"
#include "base/hash.h"
#include "base/single_thread_task_runner.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/utf_string_conversions.h"
#include "base/task/post_task.h"
#include "base/threading/thread_checker.h"
#include "base/threading/thread_restrictions.h"
#include "base/threading/thread_task_runner_handle.h"
#include "build/build_config.h"
#include "third_party/libyuv/include/libyuv/scale_argb.h"
#include "third_party/webrtc/modules/desktop_capture/desktop_capturer.h"
#include "third_party/webrtc/modules/desktop_capture/desktop_frame.h"
#include "yealink/rtvc/binding/desktop_media_list_observer.h"

namespace rtvc {

namespace {

// Update the list every second.
const int kDefaultNativeDesktopMediaListUpdatePeriod = 1000;

// Returns a hash of a DesktopFrame content to detect when image for a desktop
// media source has changed.
// uint32_t GetFrameHash(webrtc::DesktopFrame* frame) {
//   int data_size = frame->stride() * frame->size().height();
//   return base::Hash(frame->data(), data_size);
// }

// gfx::ImageSkia ScaleDesktopFrame(std::unique_ptr<webrtc::DesktopFrame> frame,
//                                  ThumbnailSize size) {
//   gfx::Rect scaled_rect = media::ComputeLetterboxRegion(
//       gfx::Rect(0, 0, size.width(), size.height()),
//       ThumbnailSize(frame->size().width(), frame->size().height()));

//   SkBitmap result;
//   result.allocN32Pixels(scaled_rect.width(), scaled_rect.height(), true);

//   uint8_t* pixels_data = reinterpret_cast<uint8_t*>(result.getPixels());
//   libyuv::ARGBScale(frame->data(), frame->stride(), frame->size().width(),
//                     frame->size().height(), pixels_data, result.rowBytes(),
//                     scaled_rect.width(), scaled_rect.height(),
//                     libyuv::kFilterBilinear);

//   // Set alpha channel values to 255 for all pixels.
//   // TODO(sergeyu): Fix screen/window capturers to capture alpha channel and
//   // remove this code. Currently screen/window capturers (at least some
//   // implementations) only capture R, G and B channels and set Alpha to 0.
//   // crbug.com/264424
//   for (int y = 0; y < result.height(); ++y) {
//     for (int x = 0; x < result.width(); ++x) {
//       pixels_data[result.rowBytes() * y + x * result.bytesPerPixel() + 3] =
//           0xff;
//     }
//   }

//   return gfx::ImageSkia::CreateFrom1xBitmap(result);
// }

}  // namespace

class NativeDesktopMediaList::Worker
    : public webrtc::DesktopCapturer::Callback {
 public:
  Worker(scoped_refptr<base::SingleThreadTaskRunner> task_runner,
         base::WeakPtr<NativeDesktopMediaList> media_list,
         DesktopMediaID::Type type,
         std::unique_ptr<webrtc::DesktopCapturer> capturer);
  ~Worker() override;

  void Start();
  void Refresh(const DesktopMediaID::Id& view_dialog_id);

  void RefreshThumbnails(const std::vector<DesktopMediaID>& native_ids,
                         const ThumbnailSize& thumbnail_size);

 private:
  typedef std::map<DesktopMediaID, uint32_t> ImageHashesMap;

  // webrtc::DesktopCapturer::Callback interface.
  void OnCaptureResult(webrtc::DesktopCapturer::Result result,
                       std::unique_ptr<webrtc::DesktopFrame> frame) override;

  // Task runner used for capturing operations.
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  THREAD_CHECKER(thread_checker_);

  base::WeakPtr<NativeDesktopMediaList> media_list_;

  DesktopMediaID::Type type_;
  std::unique_ptr<webrtc::DesktopCapturer> capturer_;

  std::unique_ptr<webrtc::DesktopFrame> current_frame_;

  ImageHashesMap image_hashes_;

  DISALLOW_COPY_AND_ASSIGN(Worker);
};

NativeDesktopMediaList::Worker::Worker(
    scoped_refptr<base::SingleThreadTaskRunner> task_runner,
    base::WeakPtr<NativeDesktopMediaList> media_list,
    DesktopMediaID::Type type,
    std::unique_ptr<webrtc::DesktopCapturer> capturer)
    : task_runner_(task_runner),
      media_list_(media_list),
      type_(type),
      capturer_(std::move(capturer)) {
  DETACH_FROM_THREAD(thread_checker_);
}

NativeDesktopMediaList::Worker::~Worker() {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
}

void NativeDesktopMediaList::Worker::Start() {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  capturer_->Start(this);
}

void NativeDesktopMediaList::Worker::Refresh(
    const DesktopMediaID::Id& view_dialog_id) {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  std::vector<SourceDescription> result;

  webrtc::DesktopCapturer::SourceList sources;
  if (!capturer_->GetSourceList(&sources)) {
    // Will pass empty results list to RefreshForAuraWindows().
    sources.clear();
  }

  static base::string16 DESKTOP_MEDIA_SCREEN_NAME =
      base::UTF8ToUTF16("Screen");

  bool mutiple_sources = sources.size() > 1;
  base::string16 title;
  for (size_t i = 0; i < sources.size(); ++i) {
    switch (type_) {
      case DesktopMediaID::TYPE_SCREEN:
        // Just in case 'Screen' is inflected depending on the screen number,
        // use plural formatter.
        title = mutiple_sources
                    ? DESKTOP_MEDIA_SCREEN_NAME + base::NumberToString16(i + 1)
                    : DESKTOP_MEDIA_SCREEN_NAME;
        break;

      case DesktopMediaID::TYPE_WINDOW:
        // Skip the picker dialog window.
        if (sources[i].id == view_dialog_id)
          continue;
        title = base::UTF8ToUTF16(sources[i].title);
        break;

      default:
        NOTREACHED();
    }
    result.push_back(
        SourceDescription(DesktopMediaID(type_, sources[i].id), title));
  }

  task_runner_->PostDelayedTask(
      FROM_HERE,
      base::BindOnce(&NativeDesktopMediaList::RefreshForAuraWindows,
                     media_list_, result),
      base::TimeDelta());
}

void NativeDesktopMediaList::Worker::RefreshThumbnails(
    const std::vector<DesktopMediaID>& native_ids,
    const ThumbnailSize& thumbnail_size) {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  ImageHashesMap new_image_hashes;

  // Get a thumbnail for each native source.
  for (const auto& id : native_ids) {
    if (!capturer_->SelectSource(id.id))
      continue;
    // capturer_->CaptureFrame();

    // // Expect that DesktopCapturer to always captures frames synchronously.
    // // |current_frame_| may be NULL if capture failed (e.g. because window
    // has
    // // been closed).
    // if (current_frame_) {
    //   uint32_t frame_hash = GetFrameHash(current_frame_.get());
    //   new_image_hashes[id] = frame_hash;

    //   // Scale the image only if it has changed.
    //   auto it = image_hashes_.find(id);
    //   if (it == image_hashes_.end() || it->second != frame_hash) {
    //     gfx::ImageSkia thumbnail =
    //         ScaleDesktopFrame(std::move(current_frame_), thumbnail_size);
    //     base::PostTaskWithTraits(
    //         FROM_HERE, {BrowserThread::UI},
    //         base::BindOnce(&NativeDesktopMediaList::UpdateSourceThumbnail,
    //                        media_list_, id, thumbnail));
    //   }
    // }
  }

  image_hashes_.swap(new_image_hashes);

  task_runner_->PostDelayedTask(
      FROM_HERE,
      base::BindOnce(&NativeDesktopMediaList::UpdateNativeThumbnailsFinished,
                     media_list_),
      base::TimeDelta());
}

void NativeDesktopMediaList::Worker::OnCaptureResult(
    webrtc::DesktopCapturer::Result result,
    std::unique_ptr<webrtc::DesktopFrame> frame) {
  current_frame_ = std::move(frame);
}

NativeDesktopMediaList::NativeDesktopMediaList(
    DesktopMediaID::Type type,
    std::unique_ptr<webrtc::DesktopCapturer> capturer)
    : DesktopMediaListBase(base::TimeDelta::FromMilliseconds(
          kDefaultNativeDesktopMediaListUpdatePeriod)),
      thread_("DesktopMediaListCaptureThread"),
      weak_factory_(this) {
  type_ = type;

#if defined(OS_WIN) || defined(OS_MACOSX)
  // On Windows/OSX the thread must be a UI thread.
  base::MessageLoop::Type thread_type = base::MessageLoop::TYPE_UI;
#else
  base::MessageLoop::Type thread_type = base::MessageLoop::TYPE_DEFAULT;
#endif
  thread_.StartWithOptions(base::Thread::Options(thread_type, 0));

  worker_.reset(new Worker(base::ThreadTaskRunnerHandle::Get(),
                           weak_factory_.GetWeakPtr(), type,
                           std::move(capturer)));

  thread_.task_runner()->PostTask(
      FROM_HERE,
      base::BindOnce(&Worker::Start, base::Unretained(worker_.get())));
}

NativeDesktopMediaList::~NativeDesktopMediaList() {
  // This thread should mostly be an idle observer. Stopping it should be fast.
  base::ScopedAllowBaseSyncPrimitivesOutsideBlockingScope allow_thread_join;
  thread_.task_runner()->DeleteSoon(FROM_HERE, worker_.release());
  thread_.Stop();
}

void NativeDesktopMediaList::Refresh() {
  thread_.task_runner()->PostTask(
      FROM_HERE,
      base::BindOnce(&Worker::Refresh, base::Unretained(worker_.get()),
                     view_dialog_id_.id));
}

void NativeDesktopMediaList::RefreshForAuraWindows(
    std::vector<SourceDescription> sources) {
  UpdateSourcesList(sources);

  static bool enable_thumbnail = false;

  if (!enable_thumbnail) {
    base::ThreadTaskRunnerHandle::Get()->PostDelayedTask(
        FROM_HERE,
        base::BindOnce(&NativeDesktopMediaList::UpdateNativeThumbnailsFinished,
                       weak_factory_.GetWeakPtr()),
        base::TimeDelta());
    return;
  }

  // OnAuraThumbnailCaptured() and UpdateNativeThumbnailsFinished() are
  // guaranteed to be excuted after RefreshForAuraWindows() and
  // CaptureAuraWindowThumbnail() in the browser UI thread.
  // Therefore pending_aura_capture_requests_ will be set the number of aura
  // windows to be captured and pending_native_thumbnail_capture_ will be set
  // true if native thumbnail capture is needed before OnAuraThumbnailCaptured()
  // or UpdateNativeThumbnailsFinished() are called.
  std::vector<DesktopMediaID> native_ids;
  for (const auto& source : sources) {
    native_ids.push_back(source.id);
  }

  if (!native_ids.empty()) {
    thread_.task_runner()->PostTask(
        FROM_HERE, base::BindOnce(&Worker::RefreshThumbnails,
                                  base::Unretained(worker_.get()), native_ids,
                                  thumbnail_size_));
  }
}

void NativeDesktopMediaList::UpdateNativeThumbnailsFinished() {
  ScheduleNextRefresh();
}

}  // namespace rtvc
