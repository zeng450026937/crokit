#include "yealink/rtvc/binding/video_sink_v8.h"

#include "base/logging.h"
#include "yealink/rtvc/binding/event_emitter_caller.h"

namespace yealink {

namespace rtvc {

VideoSinkV8::VideoSinkV8(mate::Dictionary sink) : sink_(sink) {}
VideoSinkV8::~VideoSinkV8() {}

void VideoSinkV8::OnFrame(const VideoFrame& frame) {
  LOG(INFO) << __FUNCTIONW__;
  v8::Isolate* isolate = sink_.isolate();

  mate::internal::ValueVector converted_args = {};

  mate::internal::CallMethodWithArgs(isolate, sink_.GetHandle(), "onFrame",
                                     &converted_args);
}
}  // namespace rtvc

}  // namespace yealink
