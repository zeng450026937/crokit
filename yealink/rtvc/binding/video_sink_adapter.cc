#include "yealink/rtvc/binding/video_sink_adapter.h"

#include "base/bind.h"
#include "base/logging.h"
#include "yealink/rtvc/api/video/i420_buffer.h"
#include "yealink/rtvc/api/video/video_frame.h"
#include "yealink/rtvc/api/video/video_sink.h"
#include "yealink/rtvc/binding/context.h"

namespace yealink {

namespace rtvc {

VideoSinkAdapter::VideoSinkAdapter() {}
VideoSinkAdapter::~VideoSinkAdapter() {}

bool VideoSinkAdapter::ConnectSink(yealink::FrameDeliverySink* sink) {
  DCHECK(sink);
  sinks_.emplace(sink);
  return true;
}
void VideoSinkAdapter::DisconnectSink(yealink::FrameDeliverySink* sink) {
  DCHECK(sink);
  sinks_.erase(sink);
}
bool VideoSinkAdapter::SetBestResolution(int width, int height) {
  DCHECK(width);
  DCHECK(height);
  return false;
}

void VideoSinkAdapter::OnFrame(const VideoFrame& frame) {
  // yealink::CaptureFrame video_frame;
  // yealink::FrameDeliverySink::AllocI420FrameData(video_frame, frame.width(),
  //                                                frame.height());

  // auto buffer = frame.video_frame_buffer()->GetI420();

  // DCHECK_EQ(video_frame.nWidth, buffer->width());
  // DCHECK_EQ(video_frame.nHeight, buffer->height());

  // for (size_t i = 0; i < 3; i++) {
  //   if (i == yealink::VideoFrame::PlaneValueType::kYPlane) {
  //     yealink::VideoFrame::PlaneData plane = video_frame.arrData[i];
  //     std::memcpy(plane.data, buffer->DataY(), plane.len);
  //   }
  //   else if (i == yealink::VideoFrame::PlaneValueType::kUPlane) {
  //     yealink::VideoFrame::PlaneData plane = video_frame.arrData[i];
  //     std::memcpy(plane.data, buffer->DataU(), plane.len);
  //   }
  //   else if (i == yealink::VideoFrame::PlaneValueType::kVPlane) {
  //     yealink::VideoFrame::PlaneData plane = video_frame.arrData[i];
  //     std::memcpy(plane.data, buffer->DataV(), plane.len);
  //   }
  // }

  // for (auto sink : sinks_) {
  //   sink->OnFrame(video_frame);
  // }

  // yealink::FrameDeliverySink::FreeFrameData(video_frame);
}

}  // namespace rtvc

}  // namespace yealink
