/*
 * @file cloud_contact_type.h
 * @date 2019-05-31
 *
 * @brief 
 */
#ifndef __CLOUD_CONTACT_TYPE_H__
#define __CLOUD_CONTACT_TYPE_H__

#include "components/base/simplelib/simple_lib.h"

namespace yealink
{
enum CloudContactLoadMode
{
    CC_LOAD_NONE, // 未加载
    CC_LOAD_AUTO, // 自动选择
    CC_LOAD_OVERALL, // 全量加载
    CC_LOAD_PARTIAL // 部分加载
};

enum CloudContactNodeType
{
    CC_NODE_NONE = 0x0000,
    CC_NODE_DEPARTMENT = 0x0001,
    CC_NODE_STAFF = 0x0002,
    CC_NODE_DEVICE = 0x0004,
    CC_NODE_VMR = 0x0008,
    CC_NODE_THIRD_PARTY = 0x0010,
    CC_NODE_MEETING_ROOM = 0x0020,
    CC_NODE_PARTY_MANAGER = 0x0040,
    CC_NODE_TERMINAL = CC_NODE_STAFF | CC_NODE_DEVICE | CC_NODE_VMR | CC_NODE_THIRD_PARTY | CC_NODE_MEETING_ROOM | CC_NODE_PARTY_MANAGER,
    CC_NODE_ALL = CC_NODE_DEPARTMENT | CC_NODE_TERMINAL,
};

struct CloudNodeIdAndType
{
    CloudNodeIdAndType()
        : type()
    {
    }
    SStringA nodeId;
    CloudContactNodeType type;
};

struct CloudNodeInfo
{
    CloudNodeInfo()
        : type()
        , contactCountRecursive(0)
    {
    }
    SStringA nodeId;
    CloudContactNodeType type;
    Array<SStringA> parentID;
    int32_t contactCountRecursive;
    SStringA name;
    SStringA pinyin;
    SStringA pinyinAbbr;
    SStringA i18nName;
    SStringA email;
    SStringA number;
    SStringA extensionNum;
};

struct CloudSubNodeInfo
{
    CloudSubNodeInfo()
        : total(0)
        , cloudInfoList(0)
    {
    }

    int32_t total;
    Array<CloudNodeInfo> cloudInfoList;
};

struct CloudSubNodeIdInfo
{
    CloudSubNodeIdInfo()
        : total(0)
        , cloudInfoList(0)
    {
    }

    int32_t total;
    Array<CloudNodeIdAndType> cloudInfoList;
};

} // namespace yealink

#endif // __CLOUD_CONTACT_TYPE_H__
