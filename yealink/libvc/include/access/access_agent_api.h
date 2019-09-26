#ifndef _ACCESS_AGENT_API_H
#define _ACCESS_AGENT_API_H

#include "access/access_agent.h"

namespace yealink
{
/**
     * @brief Create YTMSAgent
     * 
	 * @param clientId : if not set, it will create a clientId
     * @return YTMSAgent* 
     */
ACCESS_AGENT_API AccessAgent* CreateAccessAgent(const char* clientId);
/**
     * @brief YTMSAgent object must be released by
     * calling Release YTMSAgent function.
     * 
     * @param pAgent 
     */
ACCESS_AGENT_API void ReleaseAccessAgent(AccessAgent* pAgent);
} // namespace yealink

#endif // !_YTMS_AGENT_API_H
