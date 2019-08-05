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

namespace yealink
{
class SCHEDULE_API ScheduleManager
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
};

} // namespace yealink

#endif // __SCHEDULE_CONTROLLER_H__
