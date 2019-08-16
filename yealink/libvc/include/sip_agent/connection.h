#ifndef __CONNECTION_H__
#define __CONNECTION_H__

#include "sip_agent/sip_agent_define.h"
#include "sip_agent/auth.h"
#include <string>

namespace yealink
{
enum ConnectCertificateCode
{
    CCC_CERTIFICATE_EXPIRED = 0,
    CCC_CERTIFICATE_NANE_MISMATCH = 1,
    CCC_CERTIFICATE_UNTRUSTED = 2,
};

typedef struct _ConnectionParam
{
    const char* addrHost; ///like 10.10.1.1 or voip.com
    const char* addrProxy; ///like 10.10.1.1 or voip.com
    unsigned short hostPort;
    unsigned short proxyPort;
} ConnectionParam;

class SIP_AGENT_API ConnectionHandler
{
public:
    virtual ~ConnectionHandler(){};

    /**
         * @brief Handle invalid TLS/HTTP certificate.
         * 
         * @return true will ignore error.
         * @return false to cancel the auth request.
         */
    virtual bool OnCertificateError(ConnectCertificateCode code)
    {
        (void)code;
        return false;
    }
    /**
         * @brief call on Retry-After failure. 
         * 
         * @param message
         */
    virtual void OnConnectFailed(int message)
    {
        (void)message;
    }
    /**
         * @brief 
         * 
         * @param message 
         */
    virtual void OnConnected()
    {
    }
    /**
         * @brief 
         * 
         * @param message 
         */
    virtual void OnConnectInterruption(int message)
    {
        (void)message;
    }
    /**
         * @brief 
         * 
         */
    virtual void OnReceivedData()
    {
    }
};
/**
     * @brief 
     * 
     */
class SIP_AGENT_API Connnection
{
public:
    /**
         * @brief Set the auth handler object.Remove the handler 
         * by setting the parameter NULL.
         * 
         * @param pHandler 
         */
    virtual void SetAuthHandler(AuthHandler* pHandler) = 0;
    /**
         * @brief Get the Auth Handler object
         * 
         * @return AuthHandler* 
         */
    virtual AuthHandler* GetAuthHandler() = 0;
    /**
         * @brief Set the connection handler object.Remove the handler 
         * by setting the parameter NULL.
         * 
         * @param handler 
         */
    virtual void SetConnectionHandler(ConnectionHandler* handler) = 0;
    /**
         * @brief 
         * 
         * @return ConnectionHandler* 
         */
    virtual ConnectionHandler* GetConnectionHandler() = 0;
    /**
         * @brief 
         * 
         */
    virtual bool Connect(const ConnectionParam& param) = 0;
    /**
         * @brief 
         * 
         */
    virtual void Disconnect() = 0;
    /**
         * @brief Set the user agent name
         * 
         * @param userAgent 
         */
    virtual void SetUserAgent(const char* userAgent) = 0;
    /**
         * @brief Set the site name
         *
         * @param name
         */
    virtual void SetSiteName(const char* name) = 0;
    /**
     * @brief Set the user agent name
     *
     * @param userAgent
     */
    virtual SStringA Domain() = 0;
    /**
     * @brief Set DNS servers
     *
     * @param arrServers
     * @param nCount
     */
    virtual bool SetResolver(const char* arrServers[], int nCount) = 0;

    /**
         * @brief set registe region ,it is for debug mdoe
         *
         * @param region example: cn-shanghai cn-shenzhen etc...
		 * @return true/false
         */
    virtual bool SetRegion(const char* region) = 0;
};
} // namespace yealink
#endif
