/*
 * @file schedule_data.h
 * @date 2019-04-10
 *
 * @brief 
 */
#ifndef __SCHEDULE_DATA_H__
#define __SCHEDULE_DATA_H__
#include <cstdint>
#include "components/base/simplelib/simple_lib.h"

namespace yealink
{
enum ScheduleResult
{
    SCHEDULE_SUCCESS,
    SCHEDULE_INVALID_PARAMS,
    SCHEDULE_HTTP_FAILURE,
    SCHEDULE_INVALID,
};

enum ScheduleItemProfile
{
    SCHEDULE_ITEM_PROFILE_INVALID,
    SCHEDULE_ITEM_PROFILE_DEFAULT,
    SCHEDULE_ITEM_PROFILE_EDUCATION,
    SCHEDULE_ITEM_PROFILE_SEMINAR
};

enum ScheduleRecurrenceType
{
    SCHEDULE_RECURRENCE_TYPE_INVALID,
    SCHEDULE_RECURRENCE_TYPE_NORMAL,
    SCHEDULE_RECURRENCE_TYPE_DAILY,
    SCHEDULE_RECURRENCE_TYPE_WEEKLY,
    SCHEDULE_RECURRENCE_TYPE_MONTHLY,
    SCHEDULE_RECURRENCE_TYPE_MONTH_NTH,
    SCHEDULE_RECURRENCE_TYPE_YEARLY,
    SCHEDULE_RECURRENCE_TYPE_YEAR_NTH
};

enum ScheduleDailyType
{
    SCHEDULE_DAILY_TYPE_INVALID,
    SCHEDULE_DAILY_TYPE_EACH,
    SCHEDULE_DAILY_TYPE_WEEKDAY
};

enum ScheduleRangeType
{
    SCHEDULE_RANGE_TYPE_INVALID,
    SCHEDULE_RANGE_TYPE_FOREVER,
    SCHEDULE_RANGE_TYPE_TIMES,
    SCHEDULE_RANGE_TYPE_UNTIL
};

enum ScheduleMemberRole
{
    SCHEDULE_MEMBER_ROLE_INVALID,
    SCHEDULE_MEMBER_ROLE_ORGANIZER,
    SCHEDULE_MEMBER_ROLE_PRESENTER,
    SCHEDULE_MEMBER_ROLE_PARTICIPANT,
    SCHEDULE_MEMBER_ROLE_CAST_VIEWER
};

enum ScheduleMemberType
{
    SCHEDULE_MEMBER_TYPE_INVALID,
    SCHEDULE_MEMBER_TYPE_INSIDER,
    SCHEDULE_MEMBER_TYPE_OUTSIDER
};

struct ScheduleDaylightStrategyInfo
{
    ScheduleDaylightStrategyInfo()
        : isFixedDateRule(false)
    {
    }

    bool isFixedDateRule;
    SStringA day;
    SStringA month;
    SStringA week;
    SStringA dayOfWeek;
    SStringA timeOfDay;
};

struct ScheduleTimeZoneRule
{
    SStringA dateStart;
    SStringA dateEnd;
    SStringA daylightDelta;
    ScheduleDaylightStrategyInfo daylightStrategyStart;
    ScheduleDaylightStrategyInfo daylightStrategyEnd;
};

struct ScheduleTimeZoneConfig
{
    ScheduleTimeZoneConfig()
        : utcOffset(-1)
    {
    }

    SStringA zoneId;
    int64_t utcOffset;
    SStringA offsetDisplayName;
    SStringA cnZoneName;
    SStringA usZoneName;
    Array<ScheduleTimeZoneRule> rule;
};
struct ScheduleSimpleInfo
{
    ScheduleSimpleInfo()
        : sequence(-1)
        , profile(SCHEDULE_ITEM_PROFILE_INVALID)
        , aheadTime(-1)
        , startDateTime(-1)
        , endDateTime(-1)
        , recurrenceType(SCHEDULE_RECURRENCE_TYPE_INVALID)
        , dailyType(SCHEDULE_DAILY_TYPE_INVALID)
        , recurrenceInterval(-1)
        , dayOfMonth(-1)
        , monthOfYear(-1)
        , rangeStartDate(-1)
        , rangeEndDate(-1)
        , rangeType(SCHEDULE_RANGE_TYPE_INVALID)
        , rangeOccurrences(-1)
        , isRtmp(false)
    {
    }

    SStringA planId;
    int64_t sequence;
    ScheduleItemProfile profile;
    SStringA subject;
    SStringA organizerName;

    SStringA zoneId;
    ScheduleTimeZoneConfig timeZoneConfig;
    int64_t aheadTime;
    int64_t startDateTime;
    int64_t endDateTime;

    SStringA conferenceNo;
    SStringA conferencePwd;
    Array<SStringA> roomNames;
    ScheduleRecurrenceType recurrenceType;
    ScheduleDailyType dailyType;

    int32_t recurrenceInterval;
    Array<int32_t> dayOfWeek;
    int32_t dayOfMonth;
    int32_t monthOfYear;
    int64_t rangeStartDate;

    int64_t rangeEndDate;
    ScheduleRangeType rangeType;
    int32_t rangeOccurrences;
    bool isRtmp;
};

struct ScheduleMemberInfo
{
    ScheduleMemberInfo()
        : role(SCHEDULE_MEMBER_ROLE_INVALID)
        , type(SCHEDULE_MEMBER_TYPE_INVALID)
    {
    }

    SStringA identifier;
    ScheduleMemberRole role;
    ScheduleMemberType type;
    SStringA showName;
    SStringA extension;
};

struct ScheduleRoomInfo
{
    SStringA roomId;
    SStringA name;
};

struct ScheduleDetailInfo
{
    ScheduleMemberInfo organizer;
    SStringA remark;
    Array<ScheduleMemberInfo> participants;
    Array<ScheduleRoomInfo> rooms;
};

} // namespace yealink

#endif // __SCHEDULE_DATA_H__
