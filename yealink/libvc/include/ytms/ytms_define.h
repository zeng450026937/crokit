#ifndef YTMS_DEFINE_H
#define YTMS_DEFINE_H

#include "components/base/simplelib/simple_lib.h"

#ifdef _WIN32
#    ifndef ENABLE_UNIT_TEST
#        ifdef EXPORT_SYMPOLS
#            define YTMS_AGENT_API __declspec(dllexport)
#        else
#            define YTMS_AGENT_API __declspec(dllimport)
#        endif
#    else
#        define YTMS_AGENT_API
#    endif
#else
#    define YTMS_AGENT_API
#endif

namespace yealink
{
enum PushMessageType
{
    PUSH_INSTALL_PACKET = 0,
    PUSH_UPDATE_CONFIG,
    PUSH_MESSAGE,
    PUSH_UPLOAD_LOG,
    PUSH_CONFIG,
    PUSH_START_CAPTURE,
    PUSH_STOP_CAPTURE,
    PUSH_REGISTE_AGAIN,
    PUSH_DEVICE_REBOOT
};

enum RegisterStatus
{
    USER_CONNECTING,
    USER_REGISTERING,
    USER_REGISTERED,
    USER_UNREGISTERED
};

struct YtmsFeedback
{
    const char* title;
    const char* content;
    const char* category;
    const char* contactInfo;
    const char* logPath;
    const char* imagePath;
    const char* videoPath;
    YtmsFeedback()
        : title("")
        , content("")
        , category("")
        , contactInfo("")
        , logPath("")
        , imagePath("")
        , videoPath("")
    {
    }
};

struct YtmsLog
{
    const char* sessionId;
    const char* logPath;
    YtmsLog()
        : sessionId("")
        , logPath("")
    {
    }
};

struct YtmsNetLog
{
    const char* sessionId;
    const char* logPath;
    const char* captureDeviceName;
    YtmsNetLog()
        : sessionId("")
        , logPath("")
        , captureDeviceName("")
    {
    }
};

struct YtmsSessionStatus
{
    SStringA sessionId;
    SStringA status;
};

struct YtmsPacket
{
    SStringA sessionId;
    SStringA packetPath;
};

struct YtmsConfigInfo
{
    const char* clientName;
    const char* clientType; // software/hardware
    const char* clientCategory;
    const char* clientModel; // VCD/VCD-H5/VCD-Web/VCM/VCM-H5/VCM-Web/VC800
    const char* clientPlatform; // Windows/MAC/Andorid/IOS/Linux
    const char* clientVersion;
    const char* clientArch; // x64/ia32
    const char* updateChannel; // insiders/faster/stable
    const char* customId;
    const char* configFileId;
    const char* clientRemarks;
    const char* model;
    const char* resolution;
    const char* os; // windows10/android 8/IOS 11
    const char* ip;
    const char* mac;
    const char* hostname;
    const char* cpu;
    const char* memory;
    const char* userAccount;
    const char* userName;
    const char* userDomain;
    const char* userOutbound;
    const char* userServerType; // YMS/CLOUD
    const char* userServerAddress;
    const char* registerStatus; //  connecting/registering/registered/unregistered
    const char* enterpriseDomain;
    const char* enterpriseId;
    const char* enterpriseName;

    YtmsConfigInfo()
        : clientName("")
        , clientType("")
        , clientCategory("")
        , clientModel("")
        , clientPlatform("")
        , clientVersion("")
        , clientArch("")
        , updateChannel("")
        , customId("")
        , configFileId("")
        , clientRemarks(NULL)
        , model("")
        , resolution("")
        , os("")
        , ip("")
        , mac("")
        , hostname("")
        , cpu("")
        , memory("")
        , userAccount("")
        , userName("")
        , userDomain("")
        , userOutbound("")
        , userServerType("")
        , userServerAddress("")
        , registerStatus("")
        , enterpriseDomain("")
        , enterpriseId("")
        , enterpriseName("")
    {
    }
};

struct YtmsEvent
{
    YtmsEvent()
        : eventCode("")
        , eventName("")
        , networkMode("")
        , ispType("")
    {
    }

    const char* eventCode; // E00001
    const char* eventName; // CLIENT_START_UP
    const char* networkMode; // 3G/4G/5G/WIFI
    const char* ispType; // CHINA MOBILE
};

struct YtmsAlarm
{
    const char* log;
    const char* alarmCode;
    const char* alarmName;
    const char* alarmType;
    const char* alarmLevel;
    const char* alarmDesc;
    YtmsAlarm()
        : log("")
        , alarmCode("")
        , alarmName("")
        , alarmType("")
        , alarmLevel("")
        , alarmDesc("")
    {
    }
};

struct PackageInfo
{
    PackageInfo()
        : fileSize(0)
        , forceUpdate(false)
    {
    }

    SStringA clientVersion;
    SStringA releaseDate;
    SStringA releaseNote;
    SStringA fileName;
    SStringA fileUrl;
    SStringA fileMd5;
    int fileSize;
    bool forceUpdate;
};

struct ConfigFileInfo
{
    SStringA configId;
    SStringA configName;
    SStringA downloadUrl;
    SStringA fileMd5;
};

struct DownloadInfo
{
    const char* url;
    const char* storePath;
    const char* storeName;
    DownloadInfo()
        : url("")
        , storePath("")
        , storeName("")
    {
    }
};
} // namespace yealink

#endif
