#ifndef YEALINK_RTVC_BINDING_VIDEO_FRAME_BINDING_H_
#define YEALINK_RTVC_BINDING_VIDEO_FRAME_BINDING_H_

#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/video/video_frame.h"

namespace rtvc {

class VideoFrameBinding : public mate::Wrappable<VideoFrameBinding> {
 public:
  static mate::Handle<VideoFrameBinding> Create(v8::Isolate* isolate,
                                                VideoFrame impl);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  VideoFrameBinding(v8::Isolate* isolate, VideoFrame impl);
  ~VideoFrameBinding() override;

  int width();
  int height();

  int size();

  v8::Local<v8::Value> buffer();

 private:
  VideoFrame impl_;
  v8::Global<v8::Value> buffer_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_VIDEO_FRAME_BINDING_H_
