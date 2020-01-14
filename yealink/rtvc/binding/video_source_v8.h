#ifndef YEALINK_RTVC_BINDING_VIDEO_SOURCE_V8_H_
#define YEALINK_RTVC_BINDING_VIDEO_SOURCE_V8_H_

#include <set>

#include "yealink/native_mate/persistent_dictionary.h"
#include "yealink/rtvc/api/video/video_source.h"
#include "yealink/rtvc/binding/video_frame_binding.h"

namespace rtvc {

class VideoSourceV8 : public VideoSource {
 public:
  VideoSourceV8(mate::PersistentDictionary source);
  ~VideoSourceV8();

  void AddOrUpdateSink(VideoSink* sink) override;
  void RemoveSink(VideoSink* sink) override;

  mate::PersistentDictionary GetHandle() { return source_; }

 private:
  void OnFrame(mate::Dictionary frame, unsigned int id);

  mate::PersistentDictionary source_;
  mate::PersistentDictionary source_adapter_;
  std::set<VideoSink*> sinks_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_VIDEO_SOURCE_V8_H_
