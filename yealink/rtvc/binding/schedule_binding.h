#ifndef YEALINK_RTVC_BINDING_SCHEDULE_BINDING_H_
#define YEALINK_RTVC_BINDING_SCHEDULE_BINDING_H_

#include "base/memory/weak_ptr.h"
#include "yealink/libvc/include/schedule/schedule_manager.h"
#include "yealink/native_mate/handle.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"

namespace yealink {

namespace rtvc {

class ScheduleBinding : public mate::EventEmitter<ScheduleBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  ScheduleBinding(v8::Isolate* isolate,
                  v8::Local<v8::Object> wrapper,
                  yealink::AccessAgent* access_agent);
  ~ScheduleBinding() override;

  v8::Local<v8::Promise> Sync(uint64_t start_time, uint64_t end_time, mate::Arguments* args);
  v8::Local<v8::Promise> Fetch(uint64_t start_time, uint64_t end_time);

 private:
  bool IsOutOfRange(uint64_t start_time, uint64_t end_time);
  void DoSync(uint64_t start_time, uint64_t end_time);

  yealink::AccessAgent* access_agent_;
  std::unique_ptr<yealink::ScheduleManager> schedule_manager_;

  bool synced_;
  uint64_t start_time_;
  uint64_t end_time_;

  base::WeakPtrFactory<ScheduleBinding> weak_factory_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_SCHEDULE_BINDING_H_
