#ifndef __SIP_OBSERVER_H__
#define __SIP_OBSERVER_H__

#include "sip_agent/sip_agent_define.h"
#include "sip_agent/sip_message_readonly.h"

namespace yealink
{
class SIPObserver
{
public:
    virtual ~SIPObserver()
    {
    }
    /**
         * @brief 
         * 
         * @param code 
         */
    virtual bool OnResponse(const SIPMessageReadonly& message) = 0;
    /**
         * @brief 
         * 
         * @param code 
         */
    virtual bool OnRequest(const SIPMessageReadonly& message) = 0;
    /**
         * @brief 
         * 
         * @param pAgent 
         */
    virtual void AfterAgentRelase(void* pAgent) = 0;
};
} // namespace yealink
#endif
