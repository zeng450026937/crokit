#ifndef YEALINK_RTVC_BINDING_VIDEO_SINK_V8_H_
#define YEALINK_RTVC_BINDING_VIDEO_SINK_V8_H_

#include "yealink/native_mate/dictionary.h"
#include "yealink/rtvc/api/video/video_sink.h"

namespace yealink {

namespace rtvc {

class VideoSinkV8 : public VideoSink {
 public:
  VideoSinkV8(mate::Dictionary sink);
  ~VideoSinkV8();

 private:
  void OnFrame(const VideoFrame& frame);

  mate::Dictionary sink_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_VIDEO_SINK_V8_H_
