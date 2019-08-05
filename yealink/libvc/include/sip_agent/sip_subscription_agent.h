#ifndef __SIP_SUBSCRIPTION_AGENT_H__
#define __SIP_SUBSCRIPTION_AGENT_H__

#include "sip_agent/sip_agent_define.h"
#include "sip_agent/sip_agent.h"
#include "sip_agent/sip_observer.h"

namespace yealink
{
class SIPSubscriptionObserver : public SIPObserver
{
public:
    /**
        * @brief
        *
        * @param code only SIP_RINGING
        */
    virtual void OnNOTIFY(const SIPMessageReadonly& message) = 0;
    virtual void OnActived() = 0;
    virtual void OnTerminated() = 0;
};

class SIPSubscribeAgent : public SIPAgent
{
public:
    /**
         * @brief 
         * 
         * @param content 
         * @param contenType 
         * @return true 
         * @return false 
         */
    virtual bool Active() = 0;
    /**
         * @brief 
         * 
         */
    virtual void Termination() = 0;
    /**
         * @brief Set the Observer object
         * 
         * @param pObserver 
         */
    virtual void SetObserver(SIPSubscriptionObserver* pObserver) = 0;
    /**
         * @brief Get the Observer object
         * 
         * @return SIPSubscriptionObserver* 
         */
    virtual SIPSubscriptionObserver* GetObserver() = 0;
};
} // namespace yealink
#endif
