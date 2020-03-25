#ifndef YEALINK_RTVC_BINDING_VIDEO_SOURCE_BINDING_H_
#define YEALINK_RTVC_BINDING_VIDEO_SOURCE_BINDING_H_

#include "base/threading/thread_checker.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/video/video_sink.h"

namespace rtvc {

class VideoSourceBinding : public mate::Wrappable<VideoSourceBinding>,
                           public VideoSink {
 public:
  static mate::Handle<VideoSourceBinding> Create(v8::Isolate* isolate) {
    return mate::CreateHandle(isolate, new VideoSourceBinding(isolate));
  }
  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  VideoSourceBinding(v8::Isolate* isolate);
  ~VideoSourceBinding() override;

  // VideoSink impl
  void OnFrame(const VideoFrame& frame) override;

  void AddOrUpdateSink(mate::PersistentDictionary sink);
  void RemoveSink(mate::PersistentDictionary sink);

  std::map<int, VideoSink*> sinks_;

  THREAD_CHECKER(thread_checker_);
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_VIDEO_SOURCE_BINDING_H_
