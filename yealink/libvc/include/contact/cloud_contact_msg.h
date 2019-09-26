/*
 * @file cloud_contact_msg.h
 * @date 2019-05-31
 *
 * @brief 
 */
#ifndef __CLOUD_CONTACT_MSG_H__
#define __CLOUD_CONTACT_MSG_H__

#include "cloud_contact_type.h"

namespace yealink
{
struct CloudNodeChangeNotifyEntity
{
    CloudNodeChangeNotifyEntity()
        : type(CC_NODE_NONE)
        , index(0)
    {
    }
    SStringA nodeId;
    SStringA operate;
    CloudContactNodeType type;
    SStringA pid;
    SStringA oldPid;
    int64_t index;
};

class CloudContactObserver
{
public:
    virtual ~CloudContactObserver()
    {
    }

    virtual void OnUpdating()
    {
    }
    virtual void OnUpdateFinished()
    {
    }
    virtual void OnEnableStatusChanged(bool available)
    {
        (void)available;
    }
    virtual void OnNodeChange(const Array<CloudNodeChangeNotifyEntity>& changeData)
    {
        (void)changeData;
    }
    virtual void OnLoadFail()
    {
    }
};

typedef bool (*cleanCacheCb)(void*);
} // namespace yealink

#endif // __CLOUD_CONTACT_MSG_H__
