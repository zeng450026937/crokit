#ifndef _RECORD_API_H
#define _RECORD_API_H

#include "record_storage.h"

namespace yealink
{
/**
     * @brief Create RecordStorage
     * 
	 * @param clientId : if not set, it will create a clientId
     * @return RecordStorage* 
     */
RECORD_API RecordStorage* CreateRecordStorage();

/**
     * @brief RecordStorage object must be released by
     * calling Release RecordStorage function.
     * 
     * @param pAgent 
     */
RECORD_API void ReleaseRecordStorage(RecordStorage* pAgent);
} // namespace yealink

#endif
