/**
 * @file ua_api.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-02-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#ifndef __SIP_AGENT_API_H__
#define __SIP_AGENT_API_H__

#include "sip_agent/sip_agent_define.h"
#include "sip_agent/auth.h"
#include "sip_agent/sip_message_readonly.h"
#include "sip_agent/sip_invite_agent.h"
#include "sip_agent/sip_message_agent.h"
#include "sip_agent/sip_subscription_agent.h"
#include "sip_agent/sip_client.h"
#include "sip_agent/sip_service_agent.h"

namespace yealink
{
/**
     * @brief 
     * 
     * @return SIPClient* 
     */
SIP_AGENT_API SIPClient* CreateSIPClient();
/**
     * @brief SIPClient object must be released by
     * calling RealseSIPClient function.
     * 
     * @param pObject 
     */
SIP_AGENT_API void RealseSIPClient(SIPClient* pObject);
} // namespace yealink

#endif
