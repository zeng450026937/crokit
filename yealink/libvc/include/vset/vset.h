/*!
* @file vset.h
* @date 2019/06/20
*
* @brief 
*
*/
#ifndef __VSET_H__
#define __VSET_H__
#include "vset/vset_define.h"
#include "vset/write_list.h"
#include <string>
#include <vector>

namespace vset
{
class KVHandler
{
public:
    virtual ~KVHandler()
    {
    }

public:
    virtual void OnValueChanged(const void* data, size_t len) = 0;
};

class VSET_EXPORT KVSets
{
public:
    static KVSets* Create();
    static void Release(KVSets* sets);
    static bool DeleteSets(const std::string& strPath);

public:
    virtual ~KVSets(){};

public:
    virtual bool Open(const std::string& strPath) = 0;
    virtual void Close() = 0;
    virtual bool OpenFactory(const std::string& strPath) = 0;
    virtual void CloseFactory() = 0;
    virtual bool Write(const std::string& strKey, int64_t nVal) = 0;
    virtual bool Write(const std::string& strKey, int32_t nVal) = 0;
    virtual bool Write(const std::string& strKey, const bool bVal) = 0;
    virtual bool Write(const std::string& strKey, const char* pVal, size_t szLen) = 0;
    virtual bool Read(const std::string& strKey, int64_t& nVal) = 0;
    virtual bool Read(const std::string& strKey, int32_t& nVal) = 0;
    virtual bool Read(const std::string& strKey, bool& bVal) = 0;
    virtual bool Read(const std::string& strKey, std::string& strVal) = 0;
    virtual bool Read(const std::string& strKey, std::vector<int8_t>& vecBuf) = 0;
    virtual bool Delete(const std::string& strKey) = 0;
    virtual bool FlushBatch(WriteList* pBatch) = 0;
    virtual bool RegisterHandler(const std::string& strKey, KVHandler* pHandler) = 0;
    virtual void RemoveHandler(const std::string& strKey, KVHandler* pHandler) = 0;
};

} // namespace vset

#endif //__VSET_H__