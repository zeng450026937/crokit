#ifndef YEALINK_RTVC_BINDING_VIDEO_SINK_ADAPTER_H_
#define YEALINK_RTVC_BINDING_VIDEO_SINK_ADAPTER_H_

#include <set>

#include "yealink/libvc/include/media/media_capture.h"
#include "yealink/rtvc/api/video/video_sink.h"

namespace rtvc {

class VideoSinkAdapter : public yealink::MediaCapture, public VideoSink {
 public:
  VideoSinkAdapter();
  ~VideoSinkAdapter();

  // yealink::MediaCapture impl
  bool ConnectSink(yealink::FrameDeliverySink* sink);
  void DisconnectSink(yealink::FrameDeliverySink* sink);
  bool SetBestResolution(int nWidth, int nHeight);

  // VideoSink impl
  void OnFrame(const VideoFrame& frame);

 protected:
  std::set<yealink::FrameDeliverySink*> sinks_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_VIDEO_SINK_ADAPTER_H_
