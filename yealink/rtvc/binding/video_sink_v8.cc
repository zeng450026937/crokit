#include "yealink/rtvc/binding/video_sink_v8.h"

#include "base/logging.h"
#include "yealink/rtvc/binding/invoke_method.h"
#include "yealink/rtvc/binding/video_frame_binding.h"

namespace yealink {

namespace rtvc {

VideoSinkV8::VideoSinkV8(mate::PersistentDictionary sink) : sink_(sink) {}
VideoSinkV8::~VideoSinkV8() {}

void VideoSinkV8::OnFrame(const VideoFrame& frame) {
  v8::Isolate* isolate = sink_.isolate();
  v8::HandleScope handle_scope(isolate);

  std::vector<v8::Local<v8::Value>> converted_args = {
      VideoFrameBinding::Create(isolate, frame).ToV8()};

  CallMethodWithArgs(isolate, sink_.GetHandle(), "onFrame", &converted_args);
}
}  // namespace rtvc

}  // namespace yealink
