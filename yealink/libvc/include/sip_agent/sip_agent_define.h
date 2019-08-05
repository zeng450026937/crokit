/**
 * @file sip_agent_define.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2019-01-29
 * 
 * @copyright Copyright yealink(c) 2019
 * 
 */
#ifndef __SIP_AGENT_DEFINE_H__
#define __SIP_AGENT_DEFINE_H__

#ifdef _WIN32
#    ifdef EXPORT_SYMPOLS
#        define SIP_AGENT_API __declspec(dllexport)
#    else
#        define SIP_AGENT_API __declspec(dllimport)
#    endif
#else
#    define SIP_AGENT_API
#endif

#include "sip_agent/sip_define.h"
#include "components/base/simplelib/simple_lib.h"

namespace yealink
{
enum AddressFamily
{
    AF_IP_UNSPEC = 0,
    AF_IPV4 = 2,
    AF_IPV6 = 23,
};

enum TransportType
{
    TCP,
    TLS,
    UDP,
    DTLS,
};

typedef struct _Address
{
    unsigned char byte[16];
    AddressFamily family;
    unsigned short port = 0;
    bool operator==(const _Address& right) const
    {
        if (family == right.family && port == right.port)
        {
            if (family == AddressFamily::AF_IPV4)
            {
                return memcmp(byte, right.byte, 4) == 0;
            }
            else
            {
                return memcmp(byte, right.byte, 16) == 0;
            }
        }
        return false;
    }
} Address;

typedef struct _Address2
{
    const char* strIp;
    AddressFamily family;
    unsigned short port = 0;
} Address2;

} // namespace yealink

#endif
