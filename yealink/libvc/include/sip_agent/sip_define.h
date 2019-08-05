#ifndef __SIP_DEFINE_H__
#define __SIP_DEFINE_H__

namespace yealink
{
/**
     * @brief 
     * 
     */
enum SIPCode
{
    SIP_CODE_UNKNOWN,

    // 1xx-Provisional Responses
    SIP_TRYING = 100, ///Trying
    SIP_RINGING = 180, ///Ringing
    SIP_BEING_FORWARDED = 181, ///Call is Being Forwarded
    SIP_QUEUED = 182, ///Queued
    SIP_PROGRESS = 183, ///Session Progress
    SIP_TERMINATED = 199, ///Early Dialog Terminated

    // 2xx—Successful Responses
    SIP_OK = 200, ///OK
    SIP_ACCEPTED = 202, ///Accepted
    SIP_NO_NOTIFICATION = 204, ///No Notification

    // 3xx
    SIP_MOVE_PERMANENTLY = 301, //moved permanently
    SIP_MOVE_TEMPORAILY = 302, //moved temporaily
    SIP_USER_PROXY = 305, //use proxy
    SIP_ALTERNATIVE_SERVICE = 380, //alternative service

    // 4xx
    SIP_BAD_REQUEST = 400, // bad request
    SIP_UNAUTHORIZED = 401,
    SIP_FORBIDDEN = 403, // forbidden
    SIP_NOT_FOUND = 404, // not found
    SIP_METHOD_NOT_ALLOWED = 405, // method no allowed
    SIP_NOT_ACCEPTABLE = 406, ///
    SIP_PROXY_AUTHENTICATION_REQUIRED = 407, ///
    SIP_REQUEST_TIMEOUT = 408,
    SIP_UNSUPPORTED_MEDIA_TYPE = 415,
    sIP_BAD_EXTENSION = 420,
    SIP_TEMPORARILY_UNAVAILABLE = 480,
    SIP_BUSY_HERE = 486, ///Callee is busy.
    SIP_REQUEST_TERMINATED = 487,
    SIP_NOT_ACCEPTABLE_HERE = 488, ///Some aspect of the session description or the Request-URI is not acceptable, or Codec issue.

    // 5xx
    SIP_SERVER_INTERNAL_ERROR = 500,
    SIP_NOT_IMPLEMENTED = 501,
    SIP_BAD_GATEWAY = 502,
    SIP_SERVICE_UNAVAILABLE = 503,
    SIP_GATEWAY_TIMEOUT = 504,

    // 6xx
    SIP_BUSY_EVERYWHERE = 600,
    SIP_DECLINE = 603,
    SIP_DOES_NOT_EXIST_ANYWHERE = 604,
    SIP_NOT_ACCEPTABLE_MEDIA = 606,
    SIP_UNWANTED = 607
};

enum SIPMethod
{
    SIP_UNKNOWN, /// "UNKNOWN", "NA"
    SIP_ACK, /// "ACK", " RFC 3261"
    SIP_BYE, /// "BYE", "RFC 3261"
    SIP_CANCEL, /// "CANCEL", "RFC 3261"
    SIP_INVITE, /// "INVITE", "RFC 3261"
    SIP_NOTIFY, /// "NOTIFY", "RFC 3265"
    SIP_OPTIONS, /// "OPTIONS", "RFC 3261"
    SIP_REFER, /// "REFER", "RFC 3515"
    SIP_REGISTER, /// "REGISTER", "RFC 3261"
    SIP_SUBSCRIBE, /// "SUBSCRIBE", "RFC 3265"
    SIP_RESPONSE, /// "RESPONSE", "RFC ????"),
    SIP_MESSAGE, /// "MESSAGE", "RFC ????"),
    ///_MESSAGE
    SIP_INFO, /// "INFO", "RFC 2976"
    SIP_PRACK, /// "PRACK", "RFC 3262"
    SIP_PUBLISH, /// "PUBLISH", "RFC draft"
    SIP_SERVICE, /// "SERVICE", "!RFC"
    SIP_UPDATE, /// "UPDATE", "RFC 3311"
    SIP_MAX_METHODS
};

enum SIPInviteTerminatedReason
{
    TERMINATED_BY_ERROR,
    TERMINATED_BY_TIMEOUT,
    TERMINATED_BY_REPLACED,
    TERMINATED_BY_REMOTE_CANCEL,
    TERMINATED_BY_LOCAL_CANCEL,
    TERMINATED_BY_REMOTE_REFUSE,
    TERMINATED_BY_LOCAL_REFUSE,
    TERMINATED_BY_REFERRED,
    TERMINATED_BY_REMOTE_HANGUP,
    TERMINATED_BY_LOCAL_HANGUP,
};

enum SIPReferSubscribeState
{
    REFER_STATE_ACCEPTED,
    REFER_STATE_TRYING,
    REFER_STATE_PROGRESS,
    REFER_STATE_DONE,
    REFER_STATE_FAILED
};
} // namespace yealink

#endif