#include "yealink/rtvc/binding/video_sink_v8.h"

#include "base/logging.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/invoke_method.h"
#include "yealink/rtvc/binding/video_frame_binding.h"

namespace yealink {

namespace rtvc {

VideoSinkV8::VideoSinkV8(mate::PersistentDictionary sink)
    : sink_(sink), weak_factory_(this) {}
VideoSinkV8::~VideoSinkV8() {}

void VideoSinkV8::OnFrame(const VideoFrame& frame) {
  if (!Context::Instance()->CalledOnValidThread()) {
    Context::Instance()->PostTask(
        FROM_HERE, base::BindOnce(&VideoSinkV8::OnFrame,
                                  weak_factory_.GetWeakPtr(), frame));

    return;
  }

  v8::Isolate* isolate = sink_.isolate();
  v8::HandleScope handle_scope(isolate);

  std::vector<v8::Local<v8::Value>> converted_args = {
      VideoFrameBinding::Create(isolate, frame).ToV8()};

  CallMethodWithArgs(isolate, sink_.GetHandle(), "onFrame", &converted_args);
}
}  // namespace rtvc

}  // namespace yealink
