#include "yealink/rtvc/binding/schedule_item_binding.h"

#include "base/logging.h"
#include "base/strings/string_number_conversions.h"
#include "base/task/post_task.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace std {

template <>
struct hash<yealink::ScheduleItem> {
  size_t operator()(const yealink::ScheduleItem& item) const {
    std::string hash;
    yealink::rtvc::ConvertFrom(hash, item.GetPlanId());
    hash = hash + base::IntToString(item.GetSequence());
    return std::hash<std::string>()(hash);
  }
};

}  // namespace std

namespace yealink {

namespace rtvc {

namespace {
static std::unordered_map<size_t, int32_t> g_uid_map_;
}  // namespace

mate::WrappableBase* ScheduleItemBinding::New(mate::Arguments* args) {
  return new ScheduleItemBinding(args->isolate(), args->GetThis());
}

// static
mate::Handle<ScheduleItemBinding> ScheduleItemBinding::Create(
    v8::Isolate* isolate,
    yealink::ScheduleItem schedule_item) {
  auto iter =
      g_uid_map_.find(std::hash<yealink::ScheduleItem>()(schedule_item));

  if (iter == g_uid_map_.end()) {
    return mate::CreateHandle(isolate,
                              new ScheduleItemBinding(isolate, schedule_item));
  }

  int32_t weak_map_id = iter->second;

  auto binding = mate::TrackableObject<ScheduleItemBinding>::FromWeakMapID(
      isolate, weak_map_id);

  if (binding) {
    binding->UpdateWith(schedule_item);
    return mate::CreateHandle(isolate, binding);
  }

  return mate::CreateHandle(isolate,
                            new ScheduleItemBinding(isolate, schedule_item));
}

// static
void ScheduleItemBinding::BuildPrototype(
    v8::Isolate* isolate,
    v8::Local<v8::FunctionTemplate> prototype) {
  // prototype->SetClassName(mate::StringToV8(isolate, "ScheduleItem"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("planId", &ScheduleItemBinding::planId)
      .SetProperty("sequence", &ScheduleItemBinding::sequence)
      .SetProperty("profile", &ScheduleItemBinding::profile)
      .SetProperty("subject", &ScheduleItemBinding::subject)
      .SetProperty("organizer", &ScheduleItemBinding::organizer)
      .SetProperty("timezoneId", &ScheduleItemBinding::timezoneId)
      .SetProperty("timezone", &ScheduleItemBinding::timezone)
      .SetProperty("aheadTime", &ScheduleItemBinding::aheadTime)
      .SetProperty("startTime", &ScheduleItemBinding::startTime)
      .SetProperty("endTime", &ScheduleItemBinding::endTime)
      .SetProperty("confNum", &ScheduleItemBinding::confNum)
      .SetProperty("confPwd", &ScheduleItemBinding::confPwd)
      .SetProperty("isRTMP", &ScheduleItemBinding::isRTMP)
      .SetProperty("roomNames", &ScheduleItemBinding::roomNames)
      .SetProperty("recurrence", &ScheduleItemBinding::recurrence)
      .SetProperty("dayOfWeek", &ScheduleItemBinding::dayOfWeek)
      .SetProperty("dayOfWeekIndex", &ScheduleItemBinding::dayOfWeekIndex)
      .SetProperty("dayOfMonth", &ScheduleItemBinding::dayOfMonth)
      .SetProperty("monthOfYear", &ScheduleItemBinding::monthOfYear)
      .SetMethod("getDetail", &ScheduleItemBinding::GetDetail)
      .SetMethod("getMailTemplate", &ScheduleItemBinding::GetMailTemplate);
}

ScheduleItemBinding::ScheduleItemBinding(v8::Isolate* isolate,
                                         yealink::ScheduleItem schedule_item)
    : schedule_item_(std::move(schedule_item)), weak_factory_(this) {
  Init(isolate);
  g_uid_map_.emplace(std::hash<yealink::ScheduleItem>()(schedule_item_),
                     weak_map_id_);
  ConvertFrom(properties_, schedule_item_.GetSimpleInfo());
}

ScheduleItemBinding::ScheduleItemBinding(v8::Isolate* isolate,
                                         v8::Local<v8::Object> wrapper)
    : weak_factory_(this) {
  InitWith(isolate, wrapper);
  g_uid_map_.emplace(std::hash<yealink::ScheduleItem>()(schedule_item_),
                     weak_map_id_);
}
ScheduleItemBinding::~ScheduleItemBinding() {}

void ScheduleItemBinding::UpdateWith(yealink::ScheduleItem schedule_item) {
  schedule_item_ = schedule_item;
  ConvertFrom(properties_, schedule_item_.GetSimpleInfo());
}

std::string ScheduleItemBinding::planId() {
  return properties_.planId;
}
int64_t ScheduleItemBinding::sequence() {
  return properties_.sequence;
}

ScheduleItemProfile ScheduleItemBinding::profile() {
  return properties_.profile;
}
std::string ScheduleItemBinding::subject() {
  return properties_.subject;
}
std::string ScheduleItemBinding::organizer() {
  return properties_.organizer;
}

std::string ScheduleItemBinding::timezoneId() {
  return properties_.timezoneId;
}
ScheduleTimeZone ScheduleItemBinding::timezone() {
  return properties_.timezone;
}

int64_t ScheduleItemBinding::aheadTime() {
  return properties_.aheadTime;
}
int64_t ScheduleItemBinding::startTime() {
  return properties_.startTime;
}
int64_t ScheduleItemBinding::endTime() {
  return properties_.endTime;
}

std::string ScheduleItemBinding::confNum() {
  return properties_.confNum;
}
std::string ScheduleItemBinding::confPwd() {
  return properties_.confPwd;
}
bool ScheduleItemBinding::isRTMP() {
  return properties_.isRTMP;
}

std::vector<std::string> ScheduleItemBinding::roomNames() {
  return properties_.roomNames;
}

ScheduleRecurrence ScheduleItemBinding::recurrence() {
  return properties_.recurrence;
}

std::vector<int> ScheduleItemBinding::dayOfWeek() {
  return properties_.dayOfWeek;
}
int64_t ScheduleItemBinding::dayOfWeekIndex() {
  return properties_.dayOfWeekIndex;
}
int64_t ScheduleItemBinding::dayOfMonth() {
  return properties_.dayOfMonth;
}
int64_t ScheduleItemBinding::monthOfYear() {
  return properties_.monthOfYear;
}

v8::Local<v8::Promise> ScheduleItemBinding::GetDetail() {
  if (details_) {
    return Promise::ResolvedPromise(isolate(), *details_);
  }

  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  details_.reset(new ScheduleItemDetail);

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ScheduleItemBinding::DoGetDetail,
                     weak_factory_.GetWeakPtr()),
      base::BindOnce(
          [](Promise promise,
             base::WeakPtr<ScheduleItemBinding> schedule_item) {
            if (schedule_item) {
              std::move(promise).Resolve(*(schedule_item->details_));
            } else {
              std::move(promise).RejectWithErrorMessage("Maybe destroyed.");
            }
          },
          std::move(promise), weak_factory_.GetWeakPtr()));

  return handle;
}

v8::Local<v8::Promise> ScheduleItemBinding::GetMailTemplate() {
  if (mail_template_) {
    return Promise::ResolvedPromise(isolate(), mail_template_.value_or(""));
  }

  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&ScheduleItemBinding::DoGetMailTemplate,
                     weak_factory_.GetWeakPtr()),
      base::BindOnce(
          [](Promise promise,
             base::WeakPtr<ScheduleItemBinding> schedule_item) {
            if (schedule_item) {
              std::move(promise).Resolve(schedule_item->mail_template_.value());
            } else {
              std::move(promise).RejectWithErrorMessage("Maybe destroyed.");
            }
          },
          std::move(promise), weak_factory_.GetWeakPtr()));

  return handle;
}

void ScheduleItemBinding::DoGetDetail() {
  ConvertFrom(*details_, schedule_item_.GetDetailInfo());
  ConvertFrom(details_->share_link, schedule_item_.GetShareLink());
}
void ScheduleItemBinding::DoGetMailTemplate() {
  std::string mail_template;
  ConvertFrom(mail_template, schedule_item_.GetMailTemplate());
  mail_template_ = mail_template;
}

}  // namespace rtvc

}  // namespace yealink
