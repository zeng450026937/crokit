#ifndef __SIP_MESSAGE_READONLY_H__
#define __SIP_MESSAGE_READONLY_H__

#include "sip_agent/sip_agent_define.h"
#include "components/base/simplelib/simple_string.hpp"
#include "components/base/simplelib/simple_data.hpp"
#include "components/base/simplelib/simple_array.hpp"

namespace yealink
{
typedef struct _FromToInfo
{
    SStringA strDisplayName;
    SStringA strUserInfo;
    SStringA strDomain;
    unsigned short nPort;
} FromToInfo;

typedef struct _SIPReasonInfo
{
    int nCode;
    SStringA strScheme;
    SStringA strText;
    _SIPReasonInfo();
    explicit _SIPReasonInfo(const char* strReason);
} SIPReasonInfo;

class SIPMessageReadonly
{
public:
    virtual ~SIPMessageReadonly(){};

    enum HeadLine
    {
        HEAD_CONTENT_LENGTH, ///Header() will be return unsigned int
        HEAD_CONTENT_DISPOSITION, ///Header() will be return token string
        HEAD_CONTENT_ENCODING, ///Header() will be return token string
        HEAD_MIME_VERSION, ///Header() will be return token string
        HEAD_PRIORITY, ///Header() will be return token string
        HEAD_EVENT, ///Header() will be return token string
        HEAD_SUBSCRIPTION_STATE, ///Header() will be return token string
        HEAD_SIP_ETAG, ///Header() will be return token string
        HEAD_SIP_IF_MATCH, ///Header() will be return token string
        HEAD_CONTENT_ID, ///Header() will be return token string
        HEAD_ALLOW_EVENTS, ///Header() will be return token string
        HEAD_IDENTITY, ///Header() will be return string
        HEAD_ACCEPT_ENCODING, ///Header() will be return token string
        HEAD_ACCEPT_LANGUAGE, ///Header() will be return token string
        HEAD_PROXY_REQUIRE, ///Header() will be return token string
        HEAD_REQUIRE, ///Header() will be return token string
        HEAD_SUPPORTED, ///Header() will be return token string
        HEAD_UNSUPPORTED, //Header() will be return token sting
        /*defineMultiHeader(SecurityClient, "Security-Client", Token, "RFC 3329");
            defineMultiHeader(SecurityServer, "Security-Server", Token, "RFC 3329");
            defineMultiHeader(SecurityVerify, "Security-Verify", Token, "RFC 3329");
            defineMultiHeader(RequestDisposition, "Request-Disposition", Token, "RFC 3841");*/
        HEAD_REASON, /// "Reason", Token, "RFC 3326");
        /*defineMultiHeader(Privacy, "Privacy", PrivacyCategory, "RFC 3323");
            defineMultiHeader(PMediaAuthorization, "P-Media-Authorization", Token, "RFC 3313");
            defineHeader(ReferSub, "Refer-Sub", Token, "RFC 4488");
            defineHeader(AnswerMode, "Answer-Mode", Token, "draft-ietf-answermode-04");
            defineHeader(PrivAnswerMode, "Priv-Answer-Mode", Token, "draft-ietf-answermode-04");
            defineMultiHeader(Accept, "Accept", Mime, "RFC 3261");*/
        HEAD_CONTENT_TYPE, // Mime, "RFC 3261");
        /*defineMultiHeader(CallInfo, "Call-Info", GenericUri, "RFC 3261");
            defineMultiHeader(AlertInfo, "Alert-Info", GenericUri, "RFC 3261");
            defineMultiHeader(ErrorInfo, "Error-Info", GenericUri, "RFC 3261");
            defineHeader(IdentityInfo, "Identity-Info", GenericUri, "RFC 4474");
            defineMultiHeader(RecordRoute, "Record-Route", NameAddr, "RFC 3261");
            defineMultiHeader(Route, "Route", NameAddr, "RFC 3261");*/
        HEAD_CONTACT, //NameAddr, "RFC 3261");
        /*defineHeader(From, "From", NameAddr, "RFC 3261");
            defineHeader(To, "To", NameAddr, "RFC 3261");
            defineHeader(ReplyTo, "Reply-To", NameAddr, "RFC 3261");
            defineHeader(ReferTo, "Refer-To", NameAddr, "RFC 3515");
            defineHeader(ReferredBy, "Referred-By", NameAddr, "RFC 3892");
            defineMultiHeader(Path, "Path", NameAddr, "RFC 3327");
            defineMultiHeader(AcceptContact, "Accept-Contact", NameAddr, "RFC 3841");
            defineMultiHeader(RejectContact, "Reject-Contact", NameAddr, "RFC 3841");
            defineMultiHeader(PAssertedIdentity, "P-Asserted-Identity", NameAddr, "RFC 3325");
            defineMultiHeader(PPreferredIdentity, "P-Preferred-Identity", NameAddr, "RFC 3325");
            defineHeader(PCalledPartyId, "P-Called-Party-ID", NameAddr, "RFC 3455");
            defineMultiHeader(PAssociatedUri, "P-Associated-URI", NameAddr, "RFC 3455");
            defineMultiHeader(ServiceRoute, "Service-Route", NameAddr, "RFC 3608");
            defineMultiHeader(RemotePartyId, "Remote-Party-ID", NameAddr, "draft-ietf-sip-privacy-04"); // ?bwc? Not in 3323, should we keep?
            defineMultiHeader(HistoryInfo, "History-Info", NameAddr, "RFC 4244");
            defineHeader(ContentTransferEncoding, "Content-Transfer-Encoding", StringCategory, "RFC 1521");
            defineHeader(Organization, "Organization", StringCategory, "RFC 3261");
            defineHeader(SecWebSocketKey, "Sec-WebSocket-Key", StringCategory, "RFC 6455");
            defineHeader(SecWebSocketKey1, "Sec-WebSocket-Key1", StringCategory, "draft-hixie- thewebsocketprotocol-76");
            defineHeader(SecWebSocketKey2, "Sec-WebSocket-Key2", StringCategory, "draft-hixie- thewebsocketprotocol-76");
            defineHeader(Origin, "Origin", StringCategory, "draft-hixie- thewebsocketprotocol-76");
            defineHeader(Host, "Host", StringCategory, "draft-hixie- thewebsocketprotocol-76");
            defineHeader(SecWebSocketAccept, "Sec-WebSocket-Accept", StringCategory, "RFC 6455");
            defineMultiHeader(Cookie, "Cookie", StringCategory, "RFC 6265");
            defineHeader(Server, "Server", StringCategory, "RFC 3261");
            defineHeader(Subject, "Subject", StringCategory, "RFC 3261");*/
        HEAD_USERAGENT, // "User-Agent", StringCategory, "RFC 3261");
        /*defineHeader(Timestamp, "Timestamp", StringCategory, "RFC 3261");
            defineHeader(ContentLength, "Content-Length", UInt32Category, "RFC 3261");
            defineHeader(MaxForwards, "Max-Forwards", UInt32Category, "RFC 3261");
            defineHeader(MinExpires, "Min-Expires", UInt32Category, "RFC 3261");
            defineHeader(RSeq, "RSeq", UInt32Category, "RFC 3261");
            defineHeader(RetryAfter, "Retry-After", UInt32Category, "RFC 3261");
            defineHeader(FlowTimer, "Flow-Timer", UInt32Category, "RFC 5626");*/
        HEAD_EXPIRES, // "Expires", "RFC 3261");
        /*defineHeader(SessionExpires, "Session-Expires", ExpiresCategory, "RFC 4028");
            defineHeader(MinSE, "Min-SE", ExpiresCategory, "RFC 4028");
            defineHeader(CallID, "Call-ID", CallID, "RFC 3261");*/
        HEAD_REPLACES, // "Replaces", CallID, "RFC 3891");
        /*defineHeader(InReplyTo, "In-Reply-To", CallID, "RFC 3261");
            defineHeader(Join, "Join", CallId, "RFC 3911");
            defineHeader(TargetDialog, "Target-Dialog", CallId, "RFC 4538");
            defineHeader(AuthenticationInfo, "Authentication-Info", Auth, "RFC 3261");
            defineMultiHeader(Authorization, "Authorization", Auth, "RFC 3261");
            defineMultiHeader(ProxyAuthenticate, "Proxy-Authenticate", Auth, "RFC 3261");
            defineMultiHeader(ProxyAuthorization, "Proxy-Authorization", Auth, "RFC 3261");
            defineMultiHeader(WWWAuthenticate, "Www-Authenticate", Auth, "RFC 3261");*/
        HEAD_CSEQ, //CSeqCategory, "RFC 3261");
        /*defineHeader(Date, "Date", DateCategory, "RFC 3261");
            defineMultiHeader(Warning, "Warning", WarningCategory, "RFC 3261");
            defineMultiHeader(Via, "Via", Via, "RFC 3261");
            defineHeader(RAck, "RAck", RAckCategory, "RFC 3262");
            defineHeader(PAccessNetworkInfo, "P-Access-Network-Info", Token, "RFC 3455");
            defineHeader(PChargingVector, "P-Charging-Vector", Token, "RFC 3455");
            defineHeader(PChargingFunctionAddresses, "P-Charging-Function-Addresses", Token, "RFC 3455");
            defineMultiHeader(PVisitedNetworkID, "P-Visited-Network-ID", TokenOrQuotedStringCategory, "RFC 3455");
            defineMultiHeader(UserToUser, "User-to-User", TokenOrQuotedStringCategory, "draft-ietf-cuss-sip-uui-17");*/
    };

public:
    virtual SStringA RawHeader(const char* head) const = 0;
    virtual SByteData Header(const HeadLine head) const = 0;
    virtual SStringA Headers() const = 0;
    virtual SStringA Content() const = 0;
    virtual SStringA ContentType() const = 0;
    virtual SStringA RawData() const = 0;
    virtual SIPMethod Method() const = 0;
    virtual SIPCode StatusCode() const = 0;
    virtual SStringA Reason() const = 0;
    virtual Array<SStringA> Reasons() const = 0;
    virtual Array<SIPReasonInfo> ReasonInfos() const = 0;
    virtual bool IsRequest() const = 0;
    virtual bool IsResponse() const = 0;
    virtual int ResponseSeq() const = 0;
    virtual SIPMethod ResponseMethod() const = 0;
    virtual SStringA Contact() const = 0;
    virtual SStringA Supported() const = 0;
    virtual SStringA FindStrHeader(const char* find) const = 0;
    virtual int Expires() const = 0;
    virtual FromToInfo From() const = 0;
    virtual FromToInfo To() const = 0;
    virtual SStringA UserAgent() const = 0;
    virtual SStringA Replaces() const = 0;
};
} // namespace yealink
#endif