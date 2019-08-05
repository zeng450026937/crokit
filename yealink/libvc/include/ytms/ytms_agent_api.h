#ifndef _YTMS_AGENT_API_H
#define _YTMS_AGENT_API_H

#include "ytms_agent.h"

namespace yealink
{
/**
     * @brief Create YTMSAgent
     * 
	 * @param clientId : if not set, it will create a clientId
     * @return YTMSAgent* 
     */
YTMS_AGENT_API YTMSAgent* CreateYTMSAgent(const char* clientId);
/**
     * @brief YTMSAgent object must be released by
     * calling Release YTMSAgent function.
     * 
     * @param pAgent 
     */
YTMS_AGENT_API void ReleaseYTMSAgent(YTMSAgent* pAgent);
} // namespace yealink

#endif // !_YTMS_AGENT_API_H
