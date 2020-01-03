#ifndef _HTTP_CONNECTION_H
#define _HTTP_CONNECTION_H
#include <string>
#include <map>
#include <list>
#include <functional>
#include "components/base/simplelib/src/util_string.h"

namespace yealink
{
typedef std::function<bool()> FuncIsStop;
typedef std::function<void(int, int, int, int)> FuncSetTransferStatus;
typedef std::function<size_t(void*, int)> FuncReadData;

constexpr const char* APP_JSON_U8 = "application/json;charset=UTF-8";
constexpr const char* APP_XML_U8 = "application/xml;charset=UTF-8";

enum class HttpCompressType
{
    HCT_BR = 0, //brotli
    HCT_GZIP, //gzip
    HCT_DEFLATE //zlib
};

//表单数据
struct HttpFormatData
{
    std::map<std::string, std::pair<std::string, std::string>> mapFiles; //key:name;value:localFilePath&remoteFile
    std::map<std::string, std::string> mapContent; //key:name;value
};

struct HttpResponse
{
    int32_t nCurlCode = 0; //libcurl接口状态码，0表示成功
    int32_t nHttpCode = 0; //http请求响应码 200 OK
    std::string strErrDesc; //请求失败的错误说明
    std::map<std::string, std::string, string_cmp_less> mapResHeaders; //请求响应的头部信息
};

class HttpConnection
{
public:
    virtual ~HttpConnection() = default;

    //设置主机地址
    virtual void SetHost(const std::string& strBaseUrl) = 0;
    //设置鉴权的用户名密码
    virtual void SetUserPwd(const std::string& strUserName, const std::string& strPassword) = 0;
    //设置请求的超时时间
    virtual void SetRequestTimeout(int64_t nSeconds) = 0;
    //设置数据收发响应超时时间
    virtual void SetDataTimeout(int64_t nSeconds) = 0;
    //设置回调函数：控制请求停止
    virtual void SetCallbackFuncStop(const FuncIsStop& func) = 0;
    //设置回调函数：获取当前请求进度
    virtual void SetCallbackFuncTransferStatus(const FuncSetTransferStatus& func) = 0;
    //设置回调函数：返回从服务端读取的数据
    virtual void SetCallbackFuncReadData(const FuncReadData& func) = 0;
    //设置一些特殊头域
    virtual void AddHeaderFields(const std::string& strKey, const std::string& strValue) = 0;
    //设置使用的压缩方式,gzip
    virtual void SetCompressType(const std::string& strType) = 0;
    //设置最大下载速率,bytes/s
    virtual void SetMaxRecvSpeed(int64_t nSpeed) = 0;
    //设置上传或者下载的起始点，默认为0
    virtual void SetResumeIndex(int64_t nIndex) = 0;
    //取消一些日志打印，下载时打开这个选项
    virtual void DisableDebugLog() = 0;
    //设置明文数据（json、xml等）
    virtual void SetTextData(const std::string& strData, const std::string& strType) = 0;
    //设置表单数据
    virtual void SetFormData(const HttpFormatData& data) = 0;

    //get
    virtual HttpResponse Get(const std::string& strPathAndParam) = 0;
    //post
    virtual HttpResponse Post(const std::string& strPath) = 0;
    //put
    virtual HttpResponse Put(const std::string& strPath) = 0;
};

} // namespace yealink

#endif // _HTTP_CONNECTION_H
