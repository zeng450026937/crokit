#include "yealink/rtvc/binding/schedule_binding.h"

#include "base/logging.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/converter.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/connector_binding.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/binding/schedule_item_binding.h"

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
      .SetMethod("fetch", &ScheduleBinding::Fetch);
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
}
ScheduleBinding::~ScheduleBinding() {
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

void ScheduleBinding::OnScheduleUpdate(
    const yealink::Array<yealink::ScheduleItem>& newScheduleList,
    const yealink::Array<yealink::ScheduleItem>& modifyScheduleList,
    const yealink::Array<yealink::ScheduleItem>& deleteScheduleList) {
  Emit("updated");
}

}  // namespace rtvc
