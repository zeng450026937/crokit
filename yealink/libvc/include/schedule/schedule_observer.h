/*
 * @file schedule_observer.h
 * @date 2019-04-11
 *
 * @brief 
 */
#ifndef __SCHEDULE_OBSERVER_H__
#define __SCHEDULE_OBSERVER_H__
#include "schedule_data.h"
#include "schedule_item.h"

namespace yealink
{
class ScheduleObserver
{
public:
    virtual ~ScheduleObserver()
    {
    }
    /**
     * @brief 
     * @param newScheduleList 
     * @param modifyScheduleList 
     * @param deleteScheduleList 
     */
    virtual void OnScheduleUpdate(const Array<ScheduleItem>& newScheduleList,
                                  const Array<ScheduleItem>& modifyScheduleList,
                                  const Array<ScheduleItem>& deleteScheduleList)
    {
        (void)newScheduleList;
        (void)modifyScheduleList;
        (void)deleteScheduleList;
    }
};

class ScheduleRequestHandler
{
public:
    virtual ~ScheduleRequestHandler()
    {
    }
    /**
     * @brief 
     * @return 
     */
    virtual int64_t GetStartDate() = 0;
    /**
     * @brief 
     * @return 
     */
    virtual int64_t GetEndDate() = 0;
};

} // namespace yealink

#endif // __SCHEDULE_OBSERVER_H__
