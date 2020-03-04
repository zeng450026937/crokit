#ifndef YTMS_AGENT_H
#define YTMS_AGENT_H

#include "ytms_define.h"

namespace yealink
{
class YTMSProcess
{
public:
    virtual ~YTMSProcess()
    {
    }
    /**
     * @brief stop api func's http request
     * @param  
     */
    virtual bool IsStop()
    {
        return false;
    };

    /**
     * @brief
     * @param  
     */
    virtual void SetErrorInfo(int code, const char* msg){};

    /**
     * @brief
     * @param
     */
    virtual void SetBizCode(int code){};

    /**
     * @brief
     * @param  
     */
    virtual void SetHttpCode(int code){};

    /**
     * @brief
     * @param  
     */
    virtual void SetTransferStatus(int up, int uptotal, int dn, int dntotal){};
};

class YTMSObserver
{
public:
    virtual ~YTMSObserver()
    {
    }

    /**
     * @brief new packet
     */
    virtual void OnPushInstallPacket(){};

    /**
     * @brief 
     */
    virtual void OnPushConfigFile(const char* configFileId)
    {
        (void)configFileId;
    };

    /**
     * @brief 
     */
    virtual void OnPushMessage(const char* message)
    {
        (void)message;
    };

    /**
     * @brief 
     */
    virtual void OnPushUploadLog(const char* sessionId)
    {
        (void)sessionId;
    };

    /**
     * @brief 
     */
    virtual void OnPushUploadConfig(const char* sessionId)
    {
        (void)sessionId;
    };

    /**
     * @brief 
     */
    virtual void OnPushStartCapture(const char* sessionId)
    {
        (void)sessionId;
    };

    /**
     * @brief 
     */
    virtual void OnPushStopCapture(const char* sessionId)
    {
        (void)sessionId;
    };

    /**
     * @brief 
     */
    virtual void OnPushReregiste(const char* sessionId)
    {
        (void)sessionId;
    };

    /**
     * @brief 
     */
    virtual void OnPushReboot(const char* sessionId)
    {
        (void)sessionId;
    };
};

class YTMS_AGENT_API YTMSAgent
{
public:
    virtual ~YTMSAgent()
    {
    }
    /**
         * @brief Add the Observer Handler object
         * 
         * @param handler 
         * @return true/false
         */
    virtual bool AddObserverHandler(YTMSObserver* handler) = 0;

    /**
         * @brief Del the Observer Handler object
         * 
         * @param handler 
         * @return true/false
         */
    virtual bool RemoveObserverHandler(YTMSObserver* handler) = 0;

    /**
         * @brief Set YTMS device info, if not set, it could not registe to YTMS service
         * 
         * @param YtmsConfigInfo 
         * @return true/false
         */
    virtual bool SetYtmsInfo(const YtmsConfigInfo& config, YTMSProcess* process) = 0;

    /**
         * @brief Connect server after setInfo()
         * 
         * @param serverUrl 
         * @return true/false
         */
    virtual bool StartYtmsService(const char* serverUrl, YTMSProcess* process) = 0;

    /**
         * @brief Update client register status
         * 
         * @param status 
         * @return true/false
         */
    virtual bool UpdateRegister(const RegisterStatus& status, YTMSProcess* process) = 0;

    /**
     * @brief re-registration
     * 
     * @param status 
     * @return true/false
     */
    virtual bool UpdateRegister(YTMSProcess* process) = 0;

    /**
         * @brief Get New Package Info, if receive push message for package
         * 
         * @return PackageInfo
         */
    virtual PackageInfo GetPackagesInfo(YTMSProcess* process) = 0;

    /**
         * @brief config info
         * 
         * @return ConfigFileInfo
         */
    virtual ConfigFileInfo GetConfigFileInfo(YTMSProcess* process) = 0;

    /**
         * @brief get version update info, for ios
         * 
         * @param log 
         * @return true/false
         */
    virtual YtmsVersionUpdateInfo GetVersionUpdateInfo(YTMSProcess* process) = 0;

    /**
         * @brief Download file by http
         * 
		 * @param DownloadInfo 
         * @return bool
         */
    virtual bool DownloadFile(const DownloadInfo& params, YTMSProcess* process) = 0;
    /**
         * @brief Upload Event
         * 
         * @param event 
         * @return true/false 
         */
    virtual bool UploadEvent(const YtmsEvent& event, YTMSProcess* process) = 0;

    /**
     * @brief Upload alarm
     * 
     * @param alarm 
     * @return true/false
     */
    virtual bool UploadAlarm(const YtmsAlarm& alarm, YTMSProcess* process) = 0;

    /**
         * @brief Upload feedback
         * 
         * @param feedback 
         * @return true/false 
         */
    virtual bool UploadFeedback(const YtmsFeedback& feedback, YTMSProcess* process) = 0;

    /**
         * @brief Upload config string 
         * 
         * @param config 
         * @return true/false
         */
    virtual bool UploadConfig(const char* config, YTMSProcess* process) = 0;

    /**
         * @brief Upload log file
         * 
         * @param ) 
         * @return true/false
         */
    virtual bool UploadLog(const YtmsLog& log, YTMSProcess* process) = 0;

    /**
        * @brief Upload packet file;
        *
        * @param id
        * @param file
        * @return true/false
        */
    virtual bool UploadPacket(const char* id, const char* file, YTMSProcess* process) = 0;

    /**
         * @brief Report async work session state; 
         *
         * @param id
         * @param state
         * @return true/false
         */
    virtual bool ReportSessionState(const char* id, const char* state, YTMSProcess* process) = 0;

    /**
         * @brief start to capture net log job
         * 
         * @param ) 
         * @return true/false
         */
    virtual bool StartCaptureNetLog(const YtmsNetLog& log, YTMSProcess* process) = 0;
    /**
         * @brief stop to capture net log job and upload packets
         * 
         * @param )
         * @return true/false
         */
    virtual bool StopCaptureNetLog(const char* sessionId, YTMSProcess* process) = 0;

    /**
         * @brief get net devices id infos for capture
         * 
         * @param 
         * @
		 */
    virtual Array<SStringA> GetCaptureDevices() = 0;
};
} // namespace yealink

#endif // YTMS_SERVICE_H
