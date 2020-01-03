#include "yealink/rtvc/binding/schedule_binding.h"

#include "base/logging.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/converter.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/connector_binding.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/binding/schedule_item_binding.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace mate {
template <>
struct Converter<yealink::ScheduleItem> {
  static v8::Local<v8::Value> ToV8(v8::Isolate* isolate,
                                   const yealink::ScheduleItem& val) {
    return rtvc::ScheduleItemBinding::Create(isolate, val).ToV8();
  }
};
}  // namespace mate

namespace rtvc {

mate::WrappableBase* ScheduleBinding::New(mate::Arguments* args) {
  mate::Handle<ConnectorBinding> connector;
  if (args->Length() != 1 || !args->GetNext(&connector)) {
    args->ThrowError("Connector is required.");
    return nullptr;
  }
  return new ScheduleBinding(args->isolate(), args->GetThis(),
                             connector->GetAccessAgent());
}

// static
void ScheduleBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "Schedule"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetMethod("sync", &ScheduleBinding::Sync)
      .SetMethod("fetch", &ScheduleBinding::Fetch)
      .SetMethod("addSchedulePlan", &ScheduleBinding::AddSchedulePlan)
      .SetMethod("editSerialSchedulePlan",
                 &ScheduleBinding::EditSerialSchedulePlan)
      .SetMethod("editSingleSchedulePlan",
                 &ScheduleBinding::EditSingleSchedulePlan)
      .SetMethod("deleteSerialSchedulePlan",
                 &ScheduleBinding::DeleteSerialSchedulePlan)
      .SetMethod("deleteSingleSchedulePlan",
                 &ScheduleBinding::DeleteSingleSchedulePlan)
      .SetMethod("getScheduleConfig", &ScheduleBinding::GetScheduleConfig)
      .SetMethod("getServiceAbility", &ScheduleBinding::GetServiceAbility)
      .SetMethod("getScheduleByPlanId", &ScheduleBinding::GetScheduleByPlanId);
}

ScheduleBinding::ScheduleBinding(v8::Isolate* isolate,
                                 v8::Local<v8::Object> wrapper,
                                 yealink::AccessAgent* access_agent)
    : access_agent_(access_agent),
      schedule_manager_(new yealink::ScheduleManager()),
      synced_(false),
      start_time_(0),
      end_time_(0),
      weak_factory_(this) {
  DCHECK(access_agent_);
  DCHECK(schedule_manager_);
  InitWith(isolate, wrapper);
  schedule_manager_->Init();
  schedule_manager_->AddObserver(this);
}
ScheduleBinding::~ScheduleBinding() {
  schedule_manager_->RemoveObserver(this);
  schedule_manager_->Clear();
}

v8::Local<v8::Promise> ScheduleBinding::Sync(uint64_t start_time,
                                             uint64_t end_time,
                                             mate::Arguments* args) {
  DCHECK_GT(end_time, start_time);

  bool force = false;

  if (args->GetNext(&force) && force) {
    synced_ = false;
  }

  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ScheduleBinding::DoSync, weak_factory_.GetWeakPtr(),
                     start_time, end_time),
      base::BindOnce(&Promise::ResolveEmptyPromise, std::move(promise)));

  return handle;
}
v8::Local<v8::Promise> ScheduleBinding::Fetch(uint64_t start_time,
                                              uint64_t end_time) {
  DCHECK_GT(end_time, start_time);

  if (IsOutOfRange(start_time, end_time)) {
    Promise promise(isolate());
    v8::Local<v8::Promise> handle = promise.GetHandle();

    base::PostTaskAndReply(
        FROM_HERE,
        base::BindOnce(&ScheduleBinding::DoSync, weak_factory_.GetWeakPtr(),
                       start_time, end_time),
        base::BindOnce(
            [](Promise promise, yealink::ScheduleManager* manager,
               uint64_t start_time, uint64_t end_time) {
              std::move(promise).Resolve(
                  manager->GetScheduleList(start_time, end_time));
            },
            std::move(promise), schedule_manager_.get(), start_time, end_time));

    return handle;
  }

  return Promise::ResolvedPromise(
      isolate(), schedule_manager_->GetScheduleList(start_time, end_time));
}

bool ScheduleBinding::IsOutOfRange(uint64_t start_time, uint64_t end_time) {
  DCHECK_GT(end_time, start_time);
  bool out_of_start = start_time < start_time_;
  bool out_of_end = end_time > end_time_;
  return out_of_start || out_of_end;
}

void ScheduleBinding::DoSync(uint64_t start_time, uint64_t end_time) {
  DCHECK_GT(end_time, start_time);

  bool out_of_start = start_time < start_time_;
  bool out_of_end = end_time > end_time_;
  // bool out_of_range = out_of_start || out_of_end;
  bool need_sync = synced_ && out_of_end;
  bool need_resync = synced_ && out_of_start;

  if (!synced_ || need_resync) {
    schedule_manager_->Disconnect();
    schedule_manager_->Connect(access_agent_, start_time, end_time, "");
    start_time_ = start_time;
    end_time_ = end_time;
  }

  if (need_sync) {
    schedule_manager_->Sync(end_time);
    end_time_ = end_time;
  }

  synced_ = true;
}

v8::Local<v8::Promise> ScheduleBinding::AddSchedulePlan(
    SchedulePlanInfo infos) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  int32_t* res = new int32_t();
  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ScheduleBinding::DoAddSchedulePlan,
                     base::Unretained(this), infos, res),
      base::BindOnce(&ScheduleBinding::DoHttpRequest,
                     weak_factory_.GetWeakPtr(), std::move(promise), res));

  return handle;
}

void ScheduleBinding::DoAddSchedulePlan(SchedulePlanInfo infos, int32_t* res) {
  yealink::SchedulePlanInfo schedule = yealink::SchedulePlanInfo::Create();

  schedule.SetDurationHour(infos.durationHour);
  schedule.SetDurationMinute(infos.durationMinute);
  schedule.SetEnableAutoRecord(infos.enableAutoRecord);
  schedule.SetExtensionType(
      (yealink::ScheduleExtensionType)infos.extensionType);
  schedule.SetInterval(infos.interval);
  schedule.SetProfile((yealink::ScheduleItemProfile)infos.profile);
  schedule.SetRangeEndDate(infos.rangeEndDate.c_str());
  schedule.SetRecurrenceType(
      (yealink::ScheduleRecurrenceType)infos.recurrenceType);
  schedule.SetRemark(infos.remark.c_str());
  schedule.SetRtmpLogoFileName(infos.rtmpLogoFileName.c_str());
  schedule.SetRtmpWatchLimitType(
      (yealink::ScheduleRtmpWatchLimitType)infos.rtmpWatchLimitType);
  schedule.SetRtmpWatchPwd(infos.rtmpWatchPwd.c_str());
  schedule.SetStartDate(infos.startDate.c_str());
  schedule.SetStartTime(infos.startTime.c_str());
  schedule.SetSubject(infos.subject.c_str());
  schedule.SetZoneId(infos.zoneId.c_str());
  schedule.AddDayOfWeek(infos.dayOfWeek);
  schedule.AddParticipants(infos.identifier.c_str(),
                           (yealink::ScheduleMemberType)infos.memberType,
                           (yealink::ScheduleMemberRole)infos.roleType);

  if (res)
    *res = schedule_manager_->AddSchedulePlan(schedule);
}

v8::Local<v8::Promise> ScheduleBinding::EditSerialSchedulePlan(
    std::string id,
    SchedulePlanInfo infos) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  int32_t* res = new int32_t();
  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ScheduleBinding::DoEditSerialSchedulePlan,
                     base::Unretained(this), id, infos, res),
      base::BindOnce(&ScheduleBinding::DoHttpRequest,
                     weak_factory_.GetWeakPtr(), std::move(promise), res));

  return handle;
}

void ScheduleBinding::DoEditSerialSchedulePlan(std::string id,
                                               SchedulePlanInfo infos,
                                               int32_t* res) {
  yealink::SchedulePlanInfo schedule = yealink::SchedulePlanInfo::Create();

  schedule.SetDurationHour(infos.durationHour);
  schedule.SetDurationMinute(infos.durationMinute);
  schedule.SetEnableAutoRecord(infos.enableAutoRecord);
  schedule.SetExtensionType(
      (yealink::ScheduleExtensionType)infos.extensionType);
  schedule.SetInterval(infos.interval);
  schedule.SetProfile((yealink::ScheduleItemProfile)infos.profile);
  schedule.SetRangeEndDate(infos.rangeEndDate.c_str());
  schedule.SetRecurrenceType(
      (yealink::ScheduleRecurrenceType)infos.recurrenceType);
  schedule.SetRemark(infos.remark.c_str());
  schedule.SetRtmpLogoFileName(infos.rtmpLogoFileName.c_str());
  schedule.SetRtmpWatchLimitType(
      (yealink::ScheduleRtmpWatchLimitType)infos.rtmpWatchLimitType);
  schedule.SetRtmpWatchPwd(infos.rtmpWatchPwd.c_str());
  schedule.SetStartDate(infos.startDate.c_str());
  schedule.SetStartTime(infos.startTime.c_str());
  schedule.SetSubject(infos.subject.c_str());
  schedule.SetZoneId(infos.zoneId.c_str());

  if (res)
    *res = schedule_manager_->EditSerialSchedulePlan(id.c_str(), schedule);
}

v8::Local<v8::Promise> ScheduleBinding::EditSingleSchedulePlan(
    std::string id,
    int64_t sequence,
    SchedulePlanInfo infos) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  int32_t* res = new int32_t();
  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ScheduleBinding::DoEditSingleSchedulePlan,
                     base::Unretained(this), id, sequence, infos, res),
      base::BindOnce(&ScheduleBinding::DoHttpRequest,
                     weak_factory_.GetWeakPtr(), std::move(promise), res));

  return handle;
}

void ScheduleBinding::DoEditSingleSchedulePlan(std::string id,
                                               int64_t sequence,
                                               SchedulePlanInfo infos,
                                               int32_t* res) {
  yealink::SchedulePlanInfo schedule = yealink::SchedulePlanInfo::Create();

  schedule.SetDurationHour(infos.durationHour);
  schedule.SetDurationMinute(infos.durationMinute);
  schedule.SetEnableAutoRecord(infos.enableAutoRecord);
  schedule.SetExtensionType(
      (yealink::ScheduleExtensionType)infos.extensionType);
  schedule.SetInterval(infos.interval);
  schedule.SetProfile((yealink::ScheduleItemProfile)infos.profile);
  schedule.SetRangeEndDate(infos.rangeEndDate.c_str());
  schedule.SetRecurrenceType(
      (yealink::ScheduleRecurrenceType)infos.recurrenceType);
  schedule.SetRemark(infos.remark.c_str());
  schedule.SetRtmpLogoFileName(infos.rtmpLogoFileName.c_str());
  schedule.SetRtmpWatchLimitType(
      (yealink::ScheduleRtmpWatchLimitType)infos.rtmpWatchLimitType);
  schedule.SetRtmpWatchPwd(infos.rtmpWatchPwd.c_str());
  schedule.SetStartDate(infos.startDate.c_str());
  schedule.SetStartTime(infos.startTime.c_str());
  schedule.SetSubject(infos.subject.c_str());
  schedule.SetZoneId(infos.zoneId.c_str());

  if (res)
    *res = schedule_manager_->EditSingleSchedulePlan(id.c_str(), sequence,
                                                     schedule);
}

v8::Local<v8::Promise> ScheduleBinding::DeleteSerialSchedulePlan(
    std::string id) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  int32_t* res = new int32_t();
  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ScheduleBinding::DoDeleteSerialSchedulePlan,
                     base::Unretained(this), id, res),
      base::BindOnce(&ScheduleBinding::DoHttpRequest,
                     weak_factory_.GetWeakPtr(), std::move(promise), res));

  return handle;
}

void ScheduleBinding::DoDeleteSerialSchedulePlan(std::string id, int32_t* res) {
  if (res)
    *res = schedule_manager_->DeleteSerialSchedulePlan(id.c_str());
}

v8::Local<v8::Promise> ScheduleBinding::DeleteSingleSchedulePlan(
    std::string id,
    int64_t sequence) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  int32_t* res = new int32_t();
  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ScheduleBinding::DoDeleteSingleSchedulePlan,
                     base::Unretained(this), id, sequence, res),
      base::BindOnce(&ScheduleBinding::DoHttpRequest,
                     weak_factory_.GetWeakPtr(), std::move(promise), res));

  return handle;
}

void ScheduleBinding::DoDeleteSingleSchedulePlan(std::string id,
                                                 int64_t sequence,
                                                 int32_t* res) {
  if (res)
    *res = schedule_manager_->DeleteSingleSchedulePlan(id.c_str(), sequence);
}

v8::Local<v8::Promise> ScheduleBinding::GetScheduleConfig() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  SchedulePlanConfig* res = new SchedulePlanConfig();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ScheduleBinding::DoGetScheduleConfig,
                     weak_factory_.GetWeakPtr(), base::Unretained(res)),
      base::BindOnce(
          [](Promise promise, SchedulePlanConfig* result) {
            std::move(promise).Resolve(*result);
          },
          std::move(promise), base::Owned(res)));

  return handle;
}

void ScheduleBinding::DoGetScheduleConfig(SchedulePlanConfig* res) {
  yealink::SchedulePlanConfig ret;

  ret = schedule_manager_->GetScheduleConfig();

  if (res)
    ConvertFrom(*res, ret);
}

v8::Local<v8::Promise> ScheduleBinding::GetServiceAbility(
    std::vector<ScheduleServiceAbility> info) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  ScheduleServiceResponse* res = new ScheduleServiceResponse();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ScheduleBinding::DoGetServiceAbility,
                     weak_factory_.GetWeakPtr(), base::Unretained(res), info),
      base::BindOnce(
          [](Promise promise, ScheduleServiceResponse* result) {
            std::move(promise).Resolve(*result);
          },
          std::move(promise), base::Owned(res)));

  return handle;
}

void ScheduleBinding::DoGetServiceAbility(
    ScheduleServiceResponse* res,
    std::vector<ScheduleServiceAbility> info) {
  yealink::ScheduleServiceResponse ret;
  yealink::Array<yealink::ScheduleServiceAbility> req;

  ConvertTo(info, req);

  ret = schedule_manager_->GetServiceAbility(req);

  if (res)
    ConvertFrom(*res, ret);
}

v8::Local<v8::Promise> ScheduleBinding::GetScheduleByPlanId(std::string id) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ScheduleBinding::DoGetScheduleByPlanId,
                     weak_factory_.GetWeakPtr(), id),
      base::BindOnce(
          [](Promise promise, yealink::ScheduleManager* manager,
             std::string id) {
            std::move(promise).Resolve(
                manager->GetScheduleByPlanId(id.c_str()));
          },
          std::move(promise), schedule_manager_.get(), id));

  return handle;
}

void ScheduleBinding::DoGetScheduleByPlanId(std::string id) {}

void ScheduleBinding::DoHttpRequest(Promise promise, int32_t* res) {
  if (res != nullptr) {
    if (*res == 900200)
      std::move(promise).Resolve(*res);
    else
      std::move(promise).Reject(*res);
  } else {
    std::move(promise).Reject();
  }
}

void ScheduleBinding::OnScheduleUpdate(
    const yealink::Array<yealink::ScheduleItem>& newScheduleList,
    const yealink::Array<yealink::ScheduleItem>& modifyScheduleList,
    const yealink::Array<yealink::ScheduleItem>& deleteScheduleList) {
  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    context->PostTask(
        FROM_HERE, base::BindOnce(&ScheduleBinding::OnScheduleUpdate,
                                  weak_factory_.GetWeakPtr(), newScheduleList,
                                  modifyScheduleList, deleteScheduleList));
    return;
  }

  Emit("updated");
}

}  // namespace rtvc
