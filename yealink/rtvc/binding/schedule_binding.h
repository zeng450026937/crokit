#ifndef YEALINK_RTVC_BINDING_SCHEDULE_BINDING_H_
#define YEALINK_RTVC_BINDING_SCHEDULE_BINDING_H_

#include "base/memory/weak_ptr.h"
#include "yealink/libvc/include/schedule/schedule_manager.h"
#include "yealink/native_mate/handle.h"
#include "yealink/rtvc/api/schedule_item.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"

namespace rtvc {

class ScheduleBinding : public mate::EventEmitter<ScheduleBinding>,
                        public yealink::ScheduleObserver {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  ScheduleBinding(v8::Isolate* isolate,
                  v8::Local<v8::Object> wrapper,
                  yealink::AccessAgent* access_agent);
  ~ScheduleBinding() override;

  v8::Local<v8::Promise> Sync(uint64_t start_time,
                              uint64_t end_time,
                              mate::Arguments* args);
  v8::Local<v8::Promise> Fetch(uint64_t start_time, uint64_t end_time);

  v8::Local<v8::Promise> AddSchedulePlan(SchedulePlanInfo infos);
  v8::Local<v8::Promise> EditSerialSchedulePlan(std::string id,
                                                SchedulePlanInfo infos);
  v8::Local<v8::Promise> EditSingleSchedulePlan(std::string id,
                                                int64_t sequence,
                                                SchedulePlanInfo infos);
  v8::Local<v8::Promise> DeleteSerialSchedulePlan(std::string id);
  v8::Local<v8::Promise> DeleteSingleSchedulePlan(std::string id,
                                                  int64_t sequence);
  v8::Local<v8::Promise> GetScheduleConfig();
  v8::Local<v8::Promise> GetServiceAbility(
      std::vector<ScheduleServiceAbility> info);
  v8::Local<v8::Promise> GetScheduleByPlanId(std::string id);

  // yealink::ScheduleObserver impl
  void OnScheduleUpdate(
      const yealink::Array<yealink::ScheduleItem>& newScheduleList,
      const yealink::Array<yealink::ScheduleItem>& modifyScheduleList,
      const yealink::Array<yealink::ScheduleItem>& deleteScheduleList) override;

 private:
  bool IsOutOfRange(uint64_t start_time, uint64_t end_time);
  void DoSync(uint64_t start_time, uint64_t end_time);

  void DoAddSchedulePlan(SchedulePlanInfo infos, int32_t* res);
  void DoEditSerialSchedulePlan(std::string id,
                                SchedulePlanInfo infos,
                                int32_t* res);
  void DoEditSingleSchedulePlan(std::string id,
                                int64_t sequence,
                                SchedulePlanInfo infos,
                                int32_t* res);
  void DoDeleteSerialSchedulePlan(std::string id, int32_t* res);
  void DoDeleteSingleSchedulePlan(std::string id,
                                  int64_t sequence,
                                  int32_t* res);
  void DoGetScheduleConfig(SchedulePlanConfig* res);
  void DoGetServiceAbility(ScheduleServiceResponse* res,
                           std::vector<ScheduleServiceAbility> info);
  void DoGetScheduleByPlanId(std::string id);

  void DoHttpRequest(Promise promise, int32_t* res);

  yealink::AccessAgent* access_agent_;
  std::unique_ptr<yealink::ScheduleManager> schedule_manager_;

  bool synced_;
  uint64_t start_time_;
  uint64_t end_time_;

  base::WeakPtrFactory<ScheduleBinding> weak_factory_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_SCHEDULE_BINDING_H_
