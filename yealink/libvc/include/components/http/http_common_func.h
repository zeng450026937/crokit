#ifndef _HTTP_COMMON_FUNC_H
#define _HTTP_COMMON_FUNC_H
#include <string>
#include <list>
#include "http_connection.h"

namespace yealink
{
namespace http_common
{
//拼接带有参数的URI
std::string GenURIByParams(const std::string& strUri, const std::list<std::pair<std::string, std::string>>& params);

//通过压缩类型枚举，拼接对应字符串
std::string GetStringByHttpCompressTypes(const std::list<HttpCompressType>& types);

size_t ReadHttpRequestData(std::string* pStr, void* data, int size);

} // namespace http_common

} // namespace yealink

#endif // _HTTP_COMMON_FUNC_H
