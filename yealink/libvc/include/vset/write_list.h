/*!
* @file write_list.h
* @date 2019/06/21
*
* @brief 
*
*/
#ifndef __WRITE_LIST_H__
#define __WRITE_LIST_H__

#include <string>
#include <vector>

namespace vset
{
class WriteList
{
public:
    static WriteList* Create();
    static void Release(WriteList* pBatch);

public:
    virtual ~WriteList(){};

public:
    virtual void Push(const std::string& strKey, int64_t nVal) = 0;
    virtual void Push(const std::string& strKey, int32_t nVal) = 0;
    virtual void Push(const std::string& strKey, const bool bVal) = 0;
    virtual void Push(const std::string& strKey, const char* pVal, size_t szLen) = 0;
    // If the database contains a mapping for "key", erase it.
    virtual void Delete(const std::string& strKey) = 0;
};

} // namespace vset

#endif //__WRITE_LIST_H__