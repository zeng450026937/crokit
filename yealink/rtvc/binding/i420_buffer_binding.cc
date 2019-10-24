#include "yealink/rtvc/binding/i420_buffer_binding.h"

#include "base/logging.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/converter.h"

namespace rtvc {

// static
mate::Handle<I420BufferBinding> I420BufferBinding::Create(
    v8::Isolate* isolate,
    scoped_refptr<I420Buffer> impl) {
  return mate::CreateHandle(isolate, new I420BufferBinding(isolate, impl));
}

// static
void I420BufferBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "I420Buffer"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("type", &I420BufferBinding::type)
      .SetProperty("width", &I420BufferBinding::width)
      .SetProperty("height", &I420BufferBinding::height)
      .SetProperty("chromaWidth", &I420BufferBinding::ChromaWidth)
      .SetProperty("chromaHeight", &I420BufferBinding::ChromaHeight)
      .SetProperty("strideY", &I420BufferBinding::StrideY)
      .SetProperty("strideU", &I420BufferBinding::StrideU)
      .SetProperty("strideV", &I420BufferBinding::StrideV)
      .SetProperty("dataY", &I420BufferBinding::DataY)
      .SetProperty("dataU", &I420BufferBinding::DataU)
      .SetProperty("dataV", &I420BufferBinding::DataV)
      .SetMethod("toI420", &I420BufferBinding::ToI420)
      .SetMethod("getI420", &I420BufferBinding::GetI420)
      .SetMethod("getI420A", &I420BufferBinding::GetI420A)
      .SetMethod("getI444", &I420BufferBinding::GetI444);
}

I420BufferBinding::I420BufferBinding(v8::Isolate* isolate,
                                     scoped_refptr<I420Buffer> impl)
    : impl_(impl) {
  Init(isolate);
}
I420BufferBinding::~I420BufferBinding() {}

void I420BufferBinding::Reset(scoped_refptr<I420Buffer> impl) {
  impl_ = impl;
}

VideoFrameBuffer::Type I420BufferBinding::type() {
  return impl_->type();
}

int I420BufferBinding::width() {
  return impl_->width();
}
int I420BufferBinding::height() {
  return impl_->height();
}

v8::Local<v8::Value> I420BufferBinding::ToI420() {
  return GetWrapper();
}

v8::Local<v8::Value> I420BufferBinding::I420BufferBinding::GetI420() {
  return GetWrapper();
}
v8::Local<v8::Value> I420BufferBinding::GetI420A() {
  return v8::Null(isolate());
}
v8::Local<v8::Value> I420BufferBinding::GetI444() {
  return v8::Null(isolate());
}
v8::Local<v8::Value> I420BufferBinding::GetI010() {
  return v8::Null(isolate());
}

int I420BufferBinding::ChromaWidth() {
  return impl_->ChromaWidth();
}
int I420BufferBinding::ChromaHeight() {
  return impl_->ChromaHeight();
}

int I420BufferBinding::StrideY() {
  return impl_->StrideY();
}
int I420BufferBinding::StrideU() {
  return impl_->StrideU();
}
int I420BufferBinding::StrideV() {
  return impl_->StrideV();
}

v8::Local<v8::Value> I420BufferBinding::DataY() {
  const auto* data = reinterpret_cast<const void*>(impl_->DataY());
  int length = impl_->StrideY() * impl_->height();
  v8::Local<v8::ArrayBuffer> array_buffer =
      v8::ArrayBuffer::New(isolate(), const_cast<void*>(data), length);
  return v8::Uint8Array::New(array_buffer, 0, length);
}
v8::Local<v8::Value> I420BufferBinding::DataU() {
  const auto* data = reinterpret_cast<const void*>(impl_->DataU());
  int length = impl_->StrideU() * impl_->ChromaHeight();
  v8::Local<v8::ArrayBuffer> array_buffer =
      v8::ArrayBuffer::New(isolate(), const_cast<void*>(data), length);
  return v8::Uint8Array::New(array_buffer, 0, length);
}
v8::Local<v8::Value> I420BufferBinding::DataV() {
  const auto* data = reinterpret_cast<const void*>(impl_->DataV());
  int length = impl_->StrideV() * impl_->ChromaHeight();
  v8::Local<v8::ArrayBuffer> array_buffer =
      v8::ArrayBuffer::New(isolate(), const_cast<void*>(data), length);
  return v8::Uint8Array::New(array_buffer, 0, length);
}

}  // namespace rtvc
