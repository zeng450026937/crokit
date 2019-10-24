#include "yealink/rtvc/binding/video_frame_binding.h"

#include "base/logging.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/binding/i420_buffer_binding.h"

namespace rtvc {

// static
mate::Handle<VideoFrameBinding> VideoFrameBinding::Create(v8::Isolate* isolate,
                                                          VideoFrame impl) {
  return mate::CreateHandle(isolate,
                            new VideoFrameBinding(isolate, std::move(impl)));
}
// static
void VideoFrameBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "VideoFrame"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("width", &VideoFrameBinding::width)
      .SetProperty("height", &VideoFrameBinding::height)
      .SetProperty("size", &VideoFrameBinding::size)
      .SetProperty("buffer", &VideoFrameBinding::buffer);
}

VideoFrameBinding::VideoFrameBinding(v8::Isolate* isolate, VideoFrame impl)
    : impl_(std::move(impl)) {
  Init(isolate);
}
VideoFrameBinding::~VideoFrameBinding() {}

int VideoFrameBinding::width() {
  return impl_.width();
}
int VideoFrameBinding::height() {
  return impl_.height();
}

int VideoFrameBinding::size() {
  return impl_.size();
}

v8::Local<v8::Value> VideoFrameBinding::buffer() {
  if (buffer_.IsEmpty()) {
    auto type = impl_.video_frame_buffer()->type();
    auto frame_buffer = impl_.video_frame_buffer();

    switch (type) {
      case VideoFrameBuffer::Type::kI420: {
        auto handle =
            I420BufferBinding::Create(isolate(), frame_buffer->GetI420());
        buffer_.Reset(isolate(), handle.ToV8());
      } break;
      default:
        return v8::Null(isolate());
    }
  }
  return v8::Local<v8::Value>::New(isolate(), buffer_);
}

}  // namespace rtvc
