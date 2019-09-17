#ifndef _RECORD_STORAGE_H
#define _RECORD_STORAGE_H

#include "record_define.h"

namespace yealink
{
class RECORD_API RecordStorage
{
public:
    virtual ~RecordStorage()
    {
    }

    virtual bool Connect(const char* dbPath) = 0;

    /**
         * @brief Insert Call Record
         * 
         * @param param : call record information    
         * @return true - success
		 *         false - failed
         */
    virtual int64_t InsertRecord(CallInfo param) = 0;

    /**
         * @brief Delete All Call Record 
         *   
         * @return true - success
		 *         false - failed
         */
    virtual bool ClearRecord() = 0;

    /**
         * @brief Delete Call Record by id
         * 
         * @param id : Record info id
         * @return true - success
		 *         false - failed
         */
    virtual bool DeleteRecord(int64_t id) = 0;

    /**
         * @brief Delete Call Records by id
         * 
         * @param ids : Record info id array
         * @param count : Array size
         * @return true - success
		 *         false - failed
         */
    virtual bool DeleteRecords(const int64_t* ids, int count) = 0;

    /**
         * @brief Query Call Record
         * 
         * @param keyword : search from  displayName or number, if match
		 * @param count : if count = 0, it will returns the results of all matches
		 *				  if count > 0, it will returns a specified number of results
         * @return Array<CallRecordInfos> if success array size > 0
         */
    virtual Array<CallRecordInfos> QueryRecord(const char* keyword, int count) = 0;

    /**
         * @brief Update Call Record by index
         * 
         * @param param : callInfo
         * @return true - success
		 *         false - failed
         */
    virtual bool UpdateRecord(CallInfo param) = 0;

    /**
         * @brief Update the display name for the same number
         * 
         * @param number : call number
		 * @param name : call display name
         * @return true - success
		 *         false - failed
         */
    virtual bool UpdateDisplayName(const char* number, const char* name) = 0;

    /**
         * @brief Get the record row count
         * 
         * @return int - row count
         */
    virtual int GetRecordCount() = 0;
};
} // namespace yealink
#endif
