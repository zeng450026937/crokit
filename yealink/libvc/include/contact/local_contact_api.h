/*
 * @file local_contact_api.h
 * @date 2019-07-13
 *
 * @brief 
 */
#ifndef __LOCAL_CONTACT_API_H__
#define __LOCAL_CONTACT_API_H__

#include "components/base/simplelib/common_marco_define.h"
#include <cstdint>
#include "components/base/simplelib/simple_string.hpp"
#include "components/base/simplelib/simple_array.hpp"

namespace yealink
{
struct LocalContactExternInfo
{
    LocalContactExternInfo()
    {
    }

    LocalContactExternInfo(const char* typeParam, const char* infoParam)
        : type(typeParam)
        , info(infoParam)
    {
    }

    SStringA type;
    SStringA info;
};

struct LocalContactInfo
{
    LocalContactInfo()
        : uid(0)
    {
    }

    int64_t uid;
    SStringA name;
    SStringA searchKey;
    Array<LocalContactExternInfo> externInfoList;
};

class VC_EXPORT_API LocalContactManager
{
    SIMPLE_OBJECT_DECLARE(LocalContactManager)
public:
    /**
     * @brief init object before use
     * @param workPath path where database place in
     * @param dbName name of database, default is "", equal to "local_contact.db"
     * @return true for success and false for fail
     * @note if return false, should init again
     */
    bool Init(const char* workPath, const char* dbName);
    /**
     * @brief add contact to database
     * @param name name of contact which is used to search
     * @param searchKey search key of contact(maybe pinyin or other) which is used to search
     * @param externInfoList extern info list of contact
     * @return uid for this contact, and return 0 when add contact fail
     */
    int64_t AddContact(const char* name,
                       const char* searchKey,
                       const Array<LocalContactExternInfo>& externInfoList);
    /**
     * @brief get contact list which support paging acquisition.
     * @param limit limit of each page (0 to acquire all)
     * @param offset acquire offset (available when limit isn't 0)
     * @return list of contact
     */
    Array<LocalContactInfo> GetContactList(int32_t limit, int32_t offset);
    /**
     * @brief get contact count number
     * @return result
     */
    int64_t GetContactCount();
    /**
     * @brief search contact by uid
     * @param uid contact uid
     * @return contact info (invalid when info.uid == 0)
     */
    LocalContactInfo SearchContact(int64_t uid);
    /**
     * @brief search contact info list by key, support paging acquisition.
     * @param key search key
     * @param limit limit of each page (0 to acquire all)
     * @param offset acquire offset (available when limit isn't 0)
     * @return list of contact info
     */
    Array<LocalContactInfo> SearchContact(const char* key, int32_t limit, int32_t offset);
    /**
     * @brief search contact info list by key and type, support paging acquisition.
     * @param type extern info type
     * @param key search key
     * @param limit limit of each page (0 to acquire all)
     * @param offset acquire offset (available when limit isn't 0)
     * @return list of contact info
     * @note full match
     */
    Array<LocalContactInfo> FindContact(const char* type, const char* key, int32_t limit, int32_t offset);
    /**
     * @brief search contact info list by name, support paging acquisition.
     * @param name contact name
     * @param limit limit of each page (0 to acquire all)
     * @param offset acquire offset (available when limit isn't 0)
     * @return list of contact info
     * @note full match
     */
    Array<LocalContactInfo> FindContact(const char* name, int32_t limit, int32_t offset);
    /**
     * @brief fuzzy search contact info list by key and type, support paging acquisition.
     * @param type extern info type
     * @param key search key
     * @param limit limit of each page (0 to acquire all)
     * @param offset acquire offset (available when limit isn't 0)
     * @return list of contact info
     * @note fuzzy match
     */
    Array<LocalContactInfo> SearchContactFuzzy(const char* type, const char* key, int32_t limit, int32_t offset);
    /**
     * @brief delete contact by uid
     * @param uid contact uid
     * @return true for success, and false for fail
     */
    bool DeleteContact(int64_t uid);
    /**
     * @brief modify contact info by uid
     * @param uid contact uid
     * @param name modified name
     * @param searchKey modified search key
     * @param externInfoList modifyed extern info list
     * @return true for success, and false for fail
     */
    bool ModifyContact(int64_t uid,
                       const char* name,
                       const char* searchKey,
                       const Array<LocalContactExternInfo>& externInfoList);
};

} // namespace yealink

#endif // __LOCAL_CONTACT_API_H__
