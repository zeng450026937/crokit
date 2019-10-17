#ifndef YEALINK_RTVC_BINDING_VIDEO_SINK_V8_H_
#define YEALINK_RTVC_BINDING_VIDEO_SINK_V8_H_

#include "base/memory/weak_ptr.h"
#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/rtvc/api/video/video_sink.h"

namespace yealink {

namespace rtvc {

class VideoSinkV8 : public VideoSink {
 public:
  VideoSinkV8(mate::PersistentDictionary sink);
  ~VideoSinkV8();

  void OnFrame(const VideoFrame& frame) override;

  mate::PersistentDictionary GetHandle() { return sink_; }

 private:
  mate::PersistentDictionary sink_;
  base::WeakPtrFactory<VideoSinkV8> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_VIDEO_SINK_V8_H_
