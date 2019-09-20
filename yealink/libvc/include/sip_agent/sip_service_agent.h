#ifndef __SIP_SERVICE_AGENT_H__
#define __SIP_SERVICE_AGENT_H__

#include "sip_agent/sip_agent_define.h"
#include "sip_agent/sip_message_readonly.h"
#include "sip_agent/sip_observer.h"
#include "sip_agent/sip_agent.h"

namespace yealink
{
class SIPServiceObserver : public SIPObserver
{
public:
    virtual void OnServiceReponse(const SIPMessageReadonly& message) = 0;
};

class SIPServiceAgent
{
public:
    virtual ~SIPServiceAgent(){};
    virtual bool SendService(const char* strContent, const char* strContentType) = 0;

public:
    virtual void SetObserver(SIPServiceObserver* pObserver) = 0;

    virtual SIPServiceObserver* GetObserver() = 0;
};
} // namespace yealink
#endif