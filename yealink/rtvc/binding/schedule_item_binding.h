#ifndef YEALINK_RTVC_BINDING_SCHEDULE_ITEM_BINDING_H_
#define YEALINK_RTVC_BINDING_SCHEDULE_ITEM_BINDING_H_

#include "base/memory/weak_ptr.h"
#include "base/optional.h"
#include "yealink/libvc/include/schedule/schedule_item.h"
#include "yealink/native_mate/handle.h"
#include "yealink/rtvc/api/schedule_item.h"
#include "yealink/rtvc/binding/trackable_object.h"
#include "yealink/rtvc/binding/promise.h"

namespace rtvc {

class ScheduleItemBinding : public mate::TrackableObject<ScheduleItemBinding> {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static mate::Handle<ScheduleItemBinding> Create(
      v8::Isolate* isolate,
      yealink::ScheduleItem schedule_item);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

  void UpdateWith(yealink::ScheduleItem schedule_item);

 protected:
  ScheduleItemBinding(v8::Isolate* isolate,
                      yealink::ScheduleItem schedule_item);
  ScheduleItemBinding(v8::Isolate* isolate, v8::Local<v8::Object> wrapper);
  ~ScheduleItemBinding() override;

  std::string planId();
  int64_t sequence();

  ScheduleItemProfile profile();
  std::string subject();
  std::string organizer();

  std::string timezoneId();
  ScheduleTimeZone timezone();

  int64_t aheadTime();
  int64_t startTime();
  int64_t endTime();

  std::string confNum();
  std::string confPwd();
  bool isRTMP();

  std::vector<std::string> roomNames();

  ScheduleRecurrence recurrence();

  std::vector<int> dayOfWeek();
  int64_t dayOfWeekIndex();
  int64_t dayOfMonth();
  int64_t monthOfYear();

  v8::Local<v8::Promise> GetDetail();
  v8::Local<v8::Promise> GetMailTemplate();

  v8::Local<v8::Promise> EditSerial(SchedulePlanInfo infos);
  v8::Local<v8::Promise> EditSingle(SchedulePlanInfo infos);

  v8::Local<v8::Promise> DeleteSingle();
  v8::Local<v8::Promise> DeleteSerial();

 private:
  void DoGetDetail();
  void DoGetMailTemplate();

  void DoEditSerial(SchedulePlanInfo infos, int32_t* res);
  void DoEditSingle(SchedulePlanInfo infos, int32_t* res);
  void DoDeleteSingle(int32_t* res);
  void DoDeleteSerial(int32_t* res);

  void DoHttpRequest(Promise promise, int32_t* res);

  yealink::ScheduleItem schedule_item_;
  ScheduleItem properties_;
  std::unique_ptr<ScheduleItemDetail> details_;
  base::Optional<std::string> mail_template_;

  base::WeakPtrFactory<ScheduleItemBinding> weak_factory_;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_BINDING_SCHEDULE_ITEM_BINDING_H_
