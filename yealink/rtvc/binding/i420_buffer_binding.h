#ifndef YEALINK_RTVC_BINDING_I420_BUFFER_BINDING_H_
#define YEALINK_RTVC_BINDING_I420_BUFFER_BINDING_H_

#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/video/i420_buffer.h"

namespace rtvc {

class I420BufferBinding : public mate::Wrappable<I420BufferBinding> {
 public:
  static mate::Handle<I420BufferBinding> Create(
      v8::Isolate* isolate,
      scoped_refptr<I420Buffer> impl);
  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void Reset(scoped_refptr<I420Buffer> impl);

 protected:
  I420BufferBinding(v8::Isolate* isolate, scoped_refptr<I420Buffer> impl);
  ~I420BufferBinding() override;

  VideoFrameBuffer::Type type();

  int width();
  int height();

  v8::Local<v8::Value> ToI420();

  v8::Local<v8::Value> GetI420();
  v8::Local<v8::Value> GetI420A();
  v8::Local<v8::Value> GetI444();
  v8::Local<v8::Value> GetI010();

  int ChromaWidth();
  int ChromaHeight();

  int StrideY();
  int StrideU();
  int StrideV();

  v8::Local<v8::Value> DataY();
  v8::Local<v8::Value> DataU();
  v8::Local<v8::Value> DataV();

 private:
  scoped_refptr<I420Buffer> impl_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_I420_BUFFER_BINDING_H_
