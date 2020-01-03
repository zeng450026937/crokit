#ifndef _HTTP_FACTORY_H
#define _HTTP_FACTORY_H
#include <memory>
#include "http_connection.h"
#include "http_download.h"

namespace yealink
{
class HttpFactory
{
public:
    HttpFactory();
    ~HttpFactory();

    //创建出来的HttpDownload实例和HttpConnection实例应在同一个线程使用
    //创建httpConnection实例
    std::shared_ptr<HttpConnection> CreateHttpConnection();
    //通过httpConnection实例创建HttpDownload实例
    std::shared_ptr<HttpDownload> CreateHttpDownloadByConnection(const std::shared_ptr<HttpConnection>& pHttpConnection);
};

} // namespace yealink

#endif // _HTTP_FACTORY_H
