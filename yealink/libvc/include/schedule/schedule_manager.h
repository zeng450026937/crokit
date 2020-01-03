/*
 * @file schedule_manager.h
 * @date 2019-04-10
 *
 * @brief 
 */
#ifndef __SCHEDULE_CONTROLLER_H__
#define __SCHEDULE_CONTROLLER_H__
#include "schedule_define.h"
#include "schedule_observer.h"
#include "access/access_agent.h"
#include "components/base/simplelib/common_marco_define.h"
#include "schedule_plan_info.h"

namespace yealink
{
class VC_EXPORT_API ScheduleManager
{
    SIMPLE_OBJECT_DECLARE(ScheduleManager)
public:
    /**
     * @brief init schedule manager
     * @return true for success, and false for failure
     */
    bool Init();
    /**
     * @brief 
     * @param client sip client
     * @param startDate
     * @param endDate
     * @param serverAddr server ip to get schedule
     * @return 
     */
    ScheduleResult Connect(AccessAgent* client, int64_t startDate, int64_t endDate, const char* serverAddr);
    /**
     * @brief disconnect schedule
     * @return 
     * @note this interface will clear all cache data
     */
    ScheduleResult Disconnect();
    /**
     * @brief 
     * @return 
     */
    ScheduleResult Sync(int64_t endDate);
    /**
     * @brief 
     * @param observer 
     */
    void AddObserver(ScheduleObserver* observer);
    /**
     * @brief 
     * @param observer 
     */
    void RemoveObserver(ScheduleObserver* observer);
    /**
     * @brief 
     * @return 
     */
    Array<ScheduleItem> GetScheduleList() const;
    /**
     * @brief 
     * @return 
     */
    Array<ScheduleItem> GetScheduleList(int64_t startTime, int64_t endTime) const;
    /**
     * @brief release internal object recourse
     */
    void Clear();
    int32_t AddSchedulePlan(const SchedulePlanInfo& info);
    int32_t EditSerialSchedulePlan(const char* planId, const SchedulePlanInfo& info);
    int32_t EditSingleSchedulePlan(const char* planId, int64_t sequence, const SchedulePlanInfo& info);
    int32_t DeleteSerialSchedulePlan(const char* planId);
    int32_t DeleteSingleSchedulePlan(const char* planId, int64_t sequence);
    SchedulePlanConfig GetScheduleConfig();
    ScheduleServiceResponse GetServiceAbility(const Array<ScheduleServiceAbility>& abilityList);

    Array<ScheduleItem> GetScheduleByPlanId(const char* planId);
};

} // namespace yealink

#endif // __SCHEDULE_CONTROLLER_H__
