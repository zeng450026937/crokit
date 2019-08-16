#ifndef YEALINK_RTVC_BINDING_VIDEO_SOURCE_ADAPTER_H_
#define YEALINK_RTVC_BINDING_VIDEO_SOURCE_ADAPTER_H_

#include <set>

#include "base/threading/thread_checker.h"
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

 protected:
  void OnVideoFrame(const yealink::VideoFrame& frame) override;

  std::set<VideoSink*> sinks_;
  
  THREAD_CHECKER(thread_checker_);
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_VIDEO_SOURCE_ADAPTER_H_