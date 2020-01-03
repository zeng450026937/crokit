/*
 * @file schedule_plan_info.h
 * @date 2019-11-09
 *
 * @brief 
 */

#ifndef __SCHEDULE_PLAN_INFO_H__
#define __SCHEDULE_PLAN_INFO_H__
#include "components/base/simplelib/common_marco_define.h"
#include "schedule_data.h"

namespace yealink
{
class VC_EXPORT_API SchedulePlanInfo
{
    SIMPLE_OBJECT_DECLARE(SchedulePlanInfo)
public:
    friend class ScheduleManager;
    friend class ScheduleItem;

public:
    static SchedulePlanInfo Create();

public:
    SchedulePlanInfo& SetProfile(ScheduleItemProfile profile);
    SchedulePlanInfo& SetSubject(const char* subject);
    SchedulePlanInfo& SetZoneId(const char* zoneId);
    SchedulePlanInfo& SetStartDate(const char* startDate);
    SchedulePlanInfo& SetStartTime(const char* startTime);

    SchedulePlanInfo& SetDurationHour(int32_t durationHour);
    SchedulePlanInfo& SetDurationMinute(int32_t durationMinute);
    SchedulePlanInfo& SetRecurrenceType(ScheduleRecurrenceType recurrenceType);
    SchedulePlanInfo& SetInterval(int32_t interval);
    SchedulePlanInfo& AddDayOfWeek(int32_t dayOfWeek);

    SchedulePlanInfo& SetRangeEndDate(const char* rangeEndDate);
    SchedulePlanInfo& SetRemark(const char* remark);
    SchedulePlanInfo& AddParticipants(const char* identifier, ScheduleMemberType type, ScheduleMemberRole role);
    SchedulePlanInfo& SetExtensionType(ScheduleExtensionType extensionType);
    SchedulePlanInfo& SetRtmpLogoFileName(const char* rtmpLogoFileName);

    SchedulePlanInfo& SetRtmpWatchLimitType(ScheduleRtmpWatchLimitType rtmpWatchLimitType);
    SchedulePlanInfo& SetRtmpWatchPwd(const char* rtmpWatchPwd);
    SchedulePlanInfo& SetEnableAutoRecord(bool enableAutoRecord);
};

} // namespace yealink

#endif // __SCHEDULE_PLAN_INFO_H__
