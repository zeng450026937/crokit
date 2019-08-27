#ifndef YEALINK_RTVC_BINDING_YTMS_BINDING_H_
#define YEALINK_RTVC_BINDING_YTMS_BINDING_H_

#include <string>

#include "yealink/libvc/include/ytms/ytms_agent_api.h"
#include "yealink/native_mate/handle.h"
#include "yealink/native_mate/wrappable.h"
#include "yealink/rtvc/api/ytms_info.h"
#include "yealink/rtvc/binding/event_emitter.h"
#include "yealink/rtvc/binding/promise.h"
#include "ytms_process.h"

namespace yealink {

class YTMSAgent;
class ProcessObserver;

namespace rtvc {

class YTMSBinding : public mate::EventEmitter<YTMSBinding>,
                    public yealink::YTMSObserver {
 public:
  static mate::WrappableBase* New(mate::Arguments* args);

  static void BuildPrototype(v8::Isolate* isolate,
                             v8::Local<v8::FunctionTemplate> prototype);

 protected:
  YTMSBinding(v8::Isolate* isolate,
              v8::Local<v8::Object> wrapper,
              std::string client_id);
  ~YTMSBinding() override;

  std::string server();
  void SetServer(std::string server);

  v8::Local<v8::Promise> Start();
  v8::Local<v8::Promise> Update(TerminalInfo params);

  v8::Local<v8::Promise> UploadAlarm(AlarmInfo params);
  v8::Local<v8::Promise> UploadFeedBack(FeedbackInfo params);
  v8::Local<v8::Promise> UploadEvent(EventInfo params);
  v8::Local<v8::Promise> UploadConfig(mate::Arguments* args);
  v8::Local<v8::Promise> UploadLog(UploadLogInfo params);

  v8::Local<v8::Promise> GetPackagesInfo();
  v8::Local<v8::Promise> GetConfigFileInfo();

  v8::Local<v8::Promise> DownloadFile(DownloadInfo params);

  v8::Local<v8::Promise> StartCapture(NetCaptureInfo params);
  v8::Local<v8::Promise> StopCapture(mate::Arguments* args);

  // yealink::YTMSObserver impl
  void OnPushInstallPacket() override;
  void OnPushConfigFile(const char* configFileId) override;
  void OnPushMessage(const char* message) override;
  void OnPushUploadLog(const char* sessionId) override;
  void OnPushUploadConfig(const char* sessionId) override;
  void OnPushStartCapture(const char* sessionId) override;
  void OnPushStopCapture(const char* sessionId) override;
  void OnPushReregiste(const char* sessionId) override;
  void OnPushReboot(const char* sessionId) override;

 private:
  void OnProcessCompeleted(Promise promise, ProcessObserver* observer);

  void DoStart(ProcessObserver* observer);
  void DoUpdate(TerminalInfo params, ProcessObserver* observer);

  void DoUploadAlarm(AlarmInfo params, ProcessObserver* observer);
  void DoUploadFeedBack(FeedbackInfo params, ProcessObserver* observer);
  void DoUploadEvent(EventInfo params, ProcessObserver* observer);
  void DoUploadConfig(std::string params, ProcessObserver* observer);
  void DoUploadLog(UploadLogInfo params, ProcessObserver* observer);

  void DoGetPackagesInfo();
  void OnGetPackagesCompeleted(Promise promise);

  void DoGetConfigFileInfo();
  void OnGetConfigCompeleted(Promise promise);

  void DoDownloadFile(DownloadInfo params, ProcessObserver* observer);

  void DoStartCapture(NetCaptureInfo params, ProcessObserver* observer);
  void DoStopCapture(std::string params, ProcessObserver* observer);

  std::string server_;
  std::string client_id_;

  bool is_running_;

  TerminalInfo client_info_;
  PackageInfo package_info_;
  ConfigurationInfo config_info_;

  YTMSAgent* ytms_agent_;
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_BINDING_YTMS_BINDING_H_
