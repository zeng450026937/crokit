#ifndef __AUTH_H__
#define __AUTH_H__

#include "sip_agent/sip_agent_define.h"
#include "sip_agent/sip_message_readonly.h"

namespace yealink
{
enum AuthState
{
    AS_NONE,
    AS_LOGGING,
    AS_LOGED,
};

enum AuthEventId
{
    AEID_SUCCESS,
    AEID_FAILED,
    AEID_UPDATED,
};

enum AuthParamType
{
    AUTH_PARAM_USERNAME,
    AUTH_PARAM_PASSWORD,
    AUTH_PARAM_PASSWORD_IS_A1HASH,
    AUTH_PARAM_DISPLAY_NAME,
    AUTH_PARAM_CLIENT_ID,
    AUTH_PARAM_SUBJECT_ID,
    AUTH_PARAM_GRUU,
};

typedef struct _AuthEvent
{
    AuthEventId id;
    Array<SIPReasonInfo> reasons;
} AuthEvent;

typedef struct _AuthICEProfile
{
    const char* strServer;
    int nUDPPort;
    int nTCPPort;
    const char* strUserName;
    const char* strPassword;
} AuthICEProfile;

class AuthHandler
{
public:
    virtual ~AuthHandler(){};
    /**
         * @brief Get the auth param as string.
         * The return value is UNICODE(UTF-8) string, typ == AUTH_PARAM_USERNAME.
         * The return value is UNICODE(UTF-8) string, typ == AUTH_PARAM_PASSWORD.
         * The first byte of the return value is not 0,
         * indicating that the password is an a1hash string, typ == AUTH_PARAM_PASSWORD_IS_A1HASH.
         * The return value is UNICODE(UTF-8) string, typ == AUTH_PARAM_DISPLAY_NAME.
         *
         * @param typ 
         * @return SStringA 
         */
    virtual SByteData GetAuthParam(AuthParamType typ) = 0;

    /**
         * @brief 
         * 
         * @param event 
         */
    virtual void OnAuthEvent(const AuthEvent& event) = 0;

    /**
         * @brief
         *
         * @param event
         */
    virtual void OnICEProfile(const AuthICEProfile& profileTURN, const AuthICEProfile& profileSTUN) = 0;
};
} // namespace yealink
#endif
