/*
 * @file schedule_item.h
 * @date 2019-04-11
 *
 * @brief 
 */
#ifndef __SCHEDULE_OBJECT_H__
#define __SCHEDULE_OBJECT_H__
#include "schedule_define.h"
#include "schedule_data.h"
#include "components/base/simplelib/common_marco_define.h"

namespace yealink
{
class SCHEDULE_API ScheduleItem
{
    SIMPLE_OBJECT_DECLARE(ScheduleItem)
public:
    /**
     * @brief 
     * @param data 
     * @return 
     */
    static ScheduleItem CreateSchedule(void* data);
    /**
     * @brief 
     * @return 
     */
    SStringA GetPlanId() const;
    /**
     * @brief 
     * @return 
     */
    int64_t GetSequence() const;
    /**
     * @brief 
     * @return 
     */
    int64_t GetStartDate() const;
    /**
     * @brief 
     * @return 
     */
    int64_t GetEndDate() const;
    /**
     * @brief 
     * @return 
     */
    ScheduleSimpleInfo GetSimpleInfo() const;
    /**
     * @brief 
     * @return 
     */
    ScheduleDetailInfo GetDetailInfo() const;
};
} // namespace yealink

#endif // __SCHEDULE_OBJECT_H__
