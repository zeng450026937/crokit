/*
 * @file cloud_contact_api.h
 * @date 2019-05-31
 *
 * @brief 
 */
#ifndef __CLOUD_CONTACT_API_H__
#define __CLOUD_CONTACT_API_H__

#include "cloud_contact_type.h"
#include "cloud_contact_msg.h"
#include "components/base/simplelib/simple_string.hpp"
#include "components/base/simplelib/simple_array.hpp"
#include "access/access_agent.h"

#ifdef _WIN32
#    ifndef ENABLE_UNIT_TEST
#        ifdef EXPORT_SYMPOLS
#            define CLOUD_CONTACT_API __declspec(dllexport)
#        else
#            define CLOUD_CONTACT_API __declspec(dllimport)
#        endif
#    else
#        define CLOUD_CONTACT_API
#    endif
#else
#    define CLOUD_CONTACT_API
#endif
namespace yealink
{
namespace cloud_contact
{
class CloudContactMgr;
}

class CLOUD_CONTACT_API CloudContactManager
{
public:
    /**
     * @brief create and init cloud contact module
     */
    CloudContactManager();
    /**
     * @brief release object
     */
    virtual ~CloudContactManager();
    /**
     * @brief 
     * @param other 
     */
    CloudContactManager(const CloudContactManager& other);
    /**
     * @brief 
     * @param other 
     * @return 
     */
    CloudContactManager& operator=(const CloudContactManager& other);
    /**
     * @brief release cloud contact module
     */
    void ReleaseManager();
    /**
     * @brief 关闭云联系人模块
     */
    void Shutdown();
    /**
     * @brief add cloud contact observer to listen notice
     * @param observer 
     */
    void AddObserver(CloudContactObserver* observer);
    /**
     * @brief remove cloud contact observer
     * @param observer
     */
    void RemoveObserver(CloudContactObserver* observer);
    /**
     * @brief 判断云联系人是否可用
     * @return 云联系人状态
     */
    bool IsAvailable();
    /**
     * @brief 判断云联系人功能是否打开
     * @return 云联系人功能状态
     */
    bool IsEnable();
    /**
     * @brief 获取服务器推送的加载模式
     * @return 加载模式
     */
    CloudContactLoadMode GetLoadMode();
    /**
     * @brief 获取公司根节点ID
     * @return 公司根节点ID
     */
    SStringA GetCompanyId();
    /**
     * @brief 根据号码获取云联系人信息
     * @param strNumber 联系人号码
     * @return 联系人信息
     */
    CloudNodeInfo GetCloudNodeInfoByNumber(const char* strNumber);
    /**
     * @brief 根据号码列表获取云联系人信息
     * @param listNumber 联系人号码列表
     * @return 联系人信息列表
     */
    Array<CloudNodeInfo> GetCloudNodeInfoByNumbers(const Array<SStringA>& listNumber);
    /**
     * @brief 设置URL、账号、密码参数
     * @param agent
     * @param strNegotiateUrl
     * @param strWorkDir 
     * @param strDbName 
     * @return 
     */
    bool SetCloudPhoneBookConf(
        AccessAgent* agent,
        const char* strNegotiateUrl,
        const char* strWorkDir,
        const char* strDbName);
    /**
     * @brief 
     * @return 
     */
    bool Update();
    /**
     * @brief 根据ID获取节点信息
     * @param strNodeId 节点ID
     * @return 节点信息
     */
    CloudNodeInfo GetNodeInfoById(const char* strNodeId);
    /**
     * @brief 分页获取子节点信息列表
     * @param id 父节点ID
     * @param recursive 是否递归获取
     * @param offset 分页起始位置
     * @param limit 分页大小
     * @param type 查询类型，支持与操作
     * @return 子节点信息，包括总数和列表
     */
    CloudSubNodeInfo GetSubNodeInfo(const char* id, bool recursive, int32_t offset, int32_t limit,
                                    CloudContactNodeType type);
    /**
     * @brief 分页获取子节点ID和type
     * @param id 父节点ID
     * @param recursive 是否递归获取
     * @param offset 分页起始位置
     * @param limit 分页大小
     * @param type 查询类型，支持与操作
     * @return 子节点type，包括总数和列表
     */
    CloudSubNodeIdInfo GetSubNodeIDVectorWithType(
        const char* id, bool recursive, int32_t offset, int32_t limit, CloudContactNodeType type);
    /**
     * @brief 分页搜索云联系人
     * @param key 搜索关键字
     * @param offset 分页起始位置
     * @param limit 分页大小
     * @return 搜索结果
     */
    CloudSubNodeInfo SearchContactInfo(const char* key, int32_t offset, int32_t limit);
    /**
     * @brief 获取个人节点id
     * @return 个人结点id
     */
    SStringA GetMyId();
    /**
     * @brief 删除云联系人缓存
     * @return 删除的文件大小，单位KB
     */
    // static float CleanCache();
private:
    cloud_contact::CloudContactMgr& m_mgr;
};

} // namespace yealink

#endif // __CLOUD_CONTACT_API_H__
