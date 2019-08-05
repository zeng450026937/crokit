#ifndef YEALINK_RTVC_BINDING_VIDEO_SOURCE_V8_H_
#define YEALINK_RTVC_BINDING_VIDEO_SOURCE_V8_H_

#include <set>
#include "yealink/native_mate/dictionary.h"
#include "yealink/rtvc/api/video/video_source.h"

namespace yealink {

namespace rtvc {

class VideoSourceV8 : public VideoSource {
 public:
  VideoSourceV8(mate::Dictionary source);
  ~VideoSourceV8();

 private:
  void OnFrame();

  void AddOrUpdateSink(VideoSink* sink) override;
  void RemoveSink(VideoSink* sink) override;

  mate::Dictionary source_;
  mate::Dictionary source_adapter_;
  std::set<VideoSink*> sinks_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_VIDEO_SOURCE_V8_H_
