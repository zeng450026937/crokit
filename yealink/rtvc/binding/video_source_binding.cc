#include "yealink/rtvc/binding/video_source_binding.h"

#include "base/logging.h"
#include "yealink/rtvc/binding/video_sink_v8.h"

namespace rtvc {

// static
void VideoSourceBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "VideoSource"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetMethod("addSink", &VideoSourceBinding::AddOrUpdateSink)
      .SetMethod("removeSink", &VideoSourceBinding::RemoveSink);
}

VideoSourceBinding::VideoSourceBinding(v8::Isolate* isolate) {}
VideoSourceBinding::~VideoSourceBinding() {}

void VideoSourceBinding::OnFrame(const VideoFrame& frame) {
  DCHECK_CALLED_ON_VALID_THREAD(thread_checker_);
  for (auto it : sinks_) {
    it.second->OnFrame(frame);
  }
}

void VideoSourceBinding::AddOrUpdateSink(mate::PersistentDictionary sink) {
  int hash = sink.GetHandle()->GetIdentityHash();
  sinks_.emplace(hash, new VideoSinkV8(sink));
}
void VideoSourceBinding::RemoveSink(mate::PersistentDictionary sink) {
  int hash = sink.GetHandle()->GetIdentityHash();
  auto it = sinks_.find(hash);
  if (it == sinks_.end())
    return;
  sinks_.erase(it);
}

}  // namespace rtvc
