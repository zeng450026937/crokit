#ifndef YEALINK_RTVC_BINDING_VIDEO_SOURCE_ADAPTER_H_
#define YEALINK_RTVC_BINDING_VIDEO_SOURCE_ADAPTER_H_

#include <set>

#include "base/memory/weak_ptr.h"
#include "yealink/libvc/include/media/media_video_frame.h"
#include "yealink/rtvc/api/video/video_source.h"

namespace yealink {

namespace rtvc {

class VideoSourceAdapter : public yealink::VideoRender, public VideoSource {
 public:
  VideoSourceAdapter();
  ~VideoSourceAdapter();

  void AddOrUpdateSink(VideoSink* sink) override;
  void RemoveSink(VideoSink* sink) override;

  void OnVideoFrame(const yealink::VideoFrame& frame) override;

 protected:
  std::set<VideoSink*> sinks_;
  base::WeakPtrFactory<VideoSourceAdapter> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_VIDEO_SOURCE_ADAPTER_H_
