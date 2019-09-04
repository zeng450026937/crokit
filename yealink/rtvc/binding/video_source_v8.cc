#include "yealink/rtvc/binding/video_source_v8.h"

#include "base/logging.h"
#include "yealink/rtvc/binding/event_emitter_caller.h"

namespace yealink {

namespace rtvc {

VideoSourceV8::VideoSourceV8(mate::PersistentDictionary source)
    : source_(source) {
  v8::Isolate* isolate = source_.isolate();

  source_adapter_ =
      mate::PersistentDictionary(isolate, v8::Object::New(isolate));
  source_adapter_.SetMethod(
      "onFrame",
      base::BindRepeating(&VideoSourceV8::OnFrame, base::Unretained(this)));

  mate::internal::ValueVector converted_args = {source_adapter_.GetHandle()};
  mate::internal::CallMethodWithArgs(isolate, source_.GetHandle(), "addSink",
                                     &converted_args);
}
VideoSourceV8::~VideoSourceV8() {
  mate::internal::ValueVector converted_args = {source_adapter_.GetHandle()};
  mate::internal::CallMethodWithArgs(source_.isolate(), source_.GetHandle(),
                                     "removeSink", &converted_args);
}

void VideoSourceV8::OnFrame(mate::Dictionary frame) {
  LOG(INFO) << __FUNCTIONW__;
  // TBD

  // VideoFrame frame = VideoFrame::Builder().build();
  // for (VideoSink* sink : sinks_) {
  //   sink->OnFrame(frame);
  // }
}

void VideoSourceV8::AddOrUpdateSink(VideoSink* sink) {
  DCHECK(sink);
  sinks_.emplace(sink);
}

void VideoSourceV8::RemoveSink(VideoSink* sink) {
  DCHECK(sink);
  sinks_.erase(sink);
}

}  // namespace rtvc

}  // namespace yealink
