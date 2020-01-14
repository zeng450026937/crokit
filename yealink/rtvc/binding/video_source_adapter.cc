#include "yealink/rtvc/binding/video_source_adapter.h"

#include "base/bind.h"
#include "base/logging.h"
#include "yealink/rtvc/api/video/i420_buffer.h"
#include "yealink/rtvc/api/video/video_frame.h"
#include "yealink/rtvc/api/video/video_sink.h"
#include "yealink/rtvc/binding/context.h"

namespace rtvc {

VideoSourceAdapter::VideoSourceAdapter() : weak_factory_(this) {}
VideoSourceAdapter::~VideoSourceAdapter() {}

void VideoSourceAdapter::AddOrUpdateSink(VideoSink* sink) {
  DCHECK(sink);
  sinks_.emplace(sink);
}
void VideoSourceAdapter::RemoveSink(VideoSink* sink) {
  DCHECK(sink);
  sinks_.erase(sink);
}

void VideoSourceAdapter::OnVideoFrame(const yealink::VideoFrame& frame,
                                      unsigned int id) {
  if (sinks_.empty())
    return;

  auto type = frame.RawDataType();
  scoped_refptr<VideoFrameBuffer> buffer;

  if (type == yealink::VideoRawDataType::VIDEO_RAW_DATA_I420) {
    auto y_plane = frame.GetData(yealink::VideoFrame::PlaneValueType::kYPlane);
    auto u_plane = frame.GetData(yealink::VideoFrame::PlaneValueType::kUPlane);
    auto v_plane = frame.GetData(yealink::VideoFrame::PlaneValueType::kVPlane);
    // auto i420_buffer = I420BufferImpl::Create(frame.Width(),
    // frame.Height());;
    auto i420_buffer = I420BufferImpl::Copy(
        frame.Width(), frame.Height(), (uint8_t*)y_plane.data, y_plane.stride,
        (uint8_t*)u_plane.data, u_plane.stride, (uint8_t*)v_plane.data,
        v_plane.stride);
    buffer = i420_buffer;
  }

  DCHECK(buffer) << "Invalid frame buffer type:" << type;

  VideoFrame video_frame =
      VideoFrame::Builder().set_video_frame_buffer(buffer).build();

  OnFrame(video_frame, id);
}

void VideoSourceAdapter::OnFrame(const VideoFrame& frame, unsigned int id) {
  if (!Context::Instance()->CalledOnValidThread()) {
    Context::Instance()->PostTask(
        FROM_HERE, base::BindOnce(&VideoSourceAdapter::OnFrame,
                                  weak_factory_.GetWeakPtr(), frame, id));

    return;
  }

  for (auto sink : sinks_) {
    sink->OnFrame(frame, id);
  }
}

}  // namespace rtvc
