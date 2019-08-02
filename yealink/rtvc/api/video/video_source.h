#ifndef YEALINK_RTVC_API_VIDEO_VIDEO_SOURCE_H_
#define YEALINK_RTVC_API_VIDEO_VIDEO_SOURCE_H_

#include <limits>

#include "yealink/rtvc/api/video/video_sink.h"
#include "yealink/rtvc/api/video/video_frame.h"

namespace yealink {

namespace rtvc {

template <typename VideoFrameT>
class VideoSourceInterface {
 public:
  virtual ~VideoSourceInterface() = default;

  virtual void AddOrUpdateSink(VideoSinkInterface<VideoFrameT>* sink) = 0;
  // RemoveSink must guarantee that at the time the method returns,
  // there is no current and no future calls to VideoSinkInterface::OnFrame.
  virtual void RemoveSink(VideoSinkInterface<VideoFrameT>* sink) = 0;
};

using VideoSource = VideoSourceInterface<VideoFrame>;

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_API_VIDEO_VIDEO_SOURCE_H_
