#ifndef YEALINK_RTVC_API_VIDEO_VIDEO_SINK_H_
#define YEALINK_RTVC_API_VIDEO_VIDEO_SINK_H_

#include "yealink/rtvc/api/video/video_frame.h"

namespace rtvc {

template <typename VideoFrameT>
class VideoSinkInterface {
 public:
  virtual ~VideoSinkInterface() = default;

  virtual void OnFrame(const VideoFrameT& frame, unsigned int id) = 0;

  // Should be called by the source when it discards the frame due to rate
  // limiting.
  virtual void OnDiscardedFrame() {}
};

using VideoSink = VideoSinkInterface<VideoFrame>;

}  // namespace rtvc

#endif  // YEALINK_RTVC_API_VIDEO_VIDEO_SINK_H_
