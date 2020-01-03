#ifndef _HTTP_DOWNLOAD_H
#define _HTTP_DOWNLOAD_H
#include "http_connection.h"

namespace yealink
{
class HttpDownload
{
public:
    virtual ~HttpDownload() = default;

    virtual HttpResponse DownloadFile(const std::string& strUri, const std::string& strFilePath) = 0;
};

} // namespace yealink

#endif // _HTTP_DOWNLOAD_H
