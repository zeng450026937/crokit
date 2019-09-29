#include "yealink/rtvc/binding/ytms_binding.h"

#include "base/task/post_task.h"
#include "yealink/libvc/include/ytms/ytms_agent_api.h"
#include "yealink/native_mate/object_template_builder.h"
#include "yealink/rtvc/binding/context.h"
#include "yealink/rtvc/binding/converter.h"
#include "yealink/rtvc/binding/promise.h"
#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

namespace rtvc {

// static
mate::WrappableBase* YTMSBinding::New(mate::Arguments* args) {
  std::string clientId;

  if (!(args->Length() == 1 && args->GetNext(&clientId))) {
    args->ThrowError("An unique client id is required.");
    return nullptr;
  }

  return new YTMSBinding(args->isolate(), args->GetThis(), clientId);
}

// static
void YTMSBinding::BuildPrototype(v8::Isolate* isolate,
                                 v8::Local<v8::FunctionTemplate> prototype) {
  prototype->SetClassName(mate::StringToV8(isolate, "YTMS"));
  mate::ObjectTemplateBuilder(isolate, prototype->PrototypeTemplate())
      .MakeDestroyable()
      .SetProperty("server", &YTMSBinding::server, &YTMSBinding::SetServer)
      .SetMethod("start", &YTMSBinding::Start)
      .SetMethod("update", &YTMSBinding::Update)
      .SetMethod("uploadAlarm", &YTMSBinding::UploadAlarm)
      .SetMethod("uploadFeedBack", &YTMSBinding::UploadFeedBack)
      .SetMethod("uploadEvent", &YTMSBinding::UploadEvent)
      .SetMethod("uploadConfig", &YTMSBinding::UploadConfig)
      .SetMethod("uploadLog", &YTMSBinding::UploadLog)
      .SetMethod("getPackagesInfo", &YTMSBinding::GetPackagesInfo)
      .SetMethod("getConfigFileInfo", &YTMSBinding::GetConfigFileInfo)
      .SetMethod("downloadFile", &YTMSBinding::DownloadFile)
      .SetMethod("getCaptureDevice", &YTMSBinding::GetCaptureDevice)
      .SetMethod("startCapture", &YTMSBinding::StartCapture)
      .SetMethod("stopCapture", &YTMSBinding::StopCapture);
}

YTMSBinding::YTMSBinding(v8::Isolate* isolate,
                         v8::Local<v8::Object> wrapper,
                         std::string client_id)
    : client_id_(client_id),
      ytms_agent_(yealink::CreateYTMSAgent(client_id.c_str())),
      weak_factory_(this) {
  InitWith(isolate, wrapper);

  ytms_agent_->AddObserverHandler(this);
}
YTMSBinding::~YTMSBinding() {
  ytms_agent_->RemoveObserverHandler(this);
}

std::string YTMSBinding::server() {
  return server_;
}
void YTMSBinding::SetServer(std::string server) {
  server_ = server;
}

void YTMSBinding::OnPushInstallPacket() {
  LOG(INFO) << __FUNCTIONW__;

  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    context->PostTask(FROM_HERE,
                      base::BindOnce(&YTMSBinding::OnPushInstallPacket,
                                     weak_factory_.GetWeakPtr()));
    return;
  }

  Emit("pushPacket");
}
void YTMSBinding::OnPushConfigFile(const char* configFileId) {
  LOG(INFO) << __FUNCTIONW__;

  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    std::string id = configFileId;
    char* param = new char[id.size() + 1];
    strcpy(param, configFileId);

    context->PostTask(FROM_HERE,
                      base::BindOnce(&YTMSBinding::OnPushConfigFile,
                                     weak_factory_.GetWeakPtr(), param));
    return;
  }

  if (configFileId) {
    Emit("pushConfig", configFileId);
    delete[] configFileId;
    configFileId = nullptr;
  } else {
    Emit("pushConfig");
  }
}
void YTMSBinding::OnPushMessage(const char* message) {
  LOG(INFO) << __FUNCTIONW__;

  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    std::string id = message;
    char* param = new char[id.size() + 1];
    strcpy(param, message);

    context->PostTask(FROM_HERE,
                      base::BindOnce(&YTMSBinding::OnPushMessage,
                                     weak_factory_.GetWeakPtr(), param));
    return;
  }

  if (message) {
    Emit("message", message);
    delete[] message;
    message = nullptr;
  } else {
    Emit("message");
  }
}
void YTMSBinding::OnPushUploadLog(const char* sessionId) {
  LOG(INFO) << __FUNCTIONW__;

  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    std::string id = sessionId;
    char* param = new char[id.size() + 1];
    strcpy(param, sessionId);

    context->PostTask(FROM_HERE,
                      base::BindOnce(&YTMSBinding::OnPushUploadLog,
                                     weak_factory_.GetWeakPtr(), param));
    return;
  }

  if (sessionId) {
    Emit("uploadLog", sessionId);
    delete[] sessionId;
    sessionId = nullptr;
  } else {
    Emit("uploadLog");
  }
}
void YTMSBinding::OnPushUploadConfig(const char* sessionId) {
  LOG(INFO) << __FUNCTIONW__;

  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    std::string id = sessionId;
    char* param = new char[id.size() + 1];
    strcpy(param, sessionId);

    context->PostTask(FROM_HERE,
                      base::BindOnce(&YTMSBinding::OnPushUploadConfig,
                                     weak_factory_.GetWeakPtr(), param));
    return;
  }

  if (sessionId) {
    Emit("uploadConfig", sessionId);
    delete[] sessionId;
    sessionId = nullptr;
  } else {
    Emit("uploadConfig");
  }
}
void YTMSBinding::OnPushStartCapture(const char* sessionId) {
  LOG(INFO) << __FUNCTIONW__;

  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    std::string id = sessionId;
    char* param = new char[id.size() + 1];
    strcpy(param, sessionId);

    context->PostTask(FROM_HERE,
                      base::BindOnce(&YTMSBinding::OnPushStartCapture,
                                     weak_factory_.GetWeakPtr(), param));
    return;
  }

  if (sessionId) {
    Emit("startCapture", sessionId);
    delete[] sessionId;
    sessionId = nullptr;
  } else {
    Emit("startCapture");
  }
}
void YTMSBinding::OnPushStopCapture(const char* sessionId) {
  LOG(INFO) << __FUNCTIONW__;

  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    std::string id = sessionId;
    char* param = new char[id.size() + 1];
    strcpy(param, sessionId);

    context->PostTask(FROM_HERE,
                      base::BindOnce(&YTMSBinding::OnPushStopCapture,
                                     weak_factory_.GetWeakPtr(), param));
    return;
  }

  if (sessionId) {
    Emit("stopCapture", sessionId);
    delete[] sessionId;
    sessionId = nullptr;
  } else {
    Emit("stopCapture");
  }
}
void YTMSBinding::OnPushReregiste(const char* sessionId) {
  LOG(INFO) << __FUNCTIONW__;

  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    std::string id = sessionId;
    char* param = new char[id.size() + 1];
    strcpy(param, sessionId);

    context->PostTask(FROM_HERE,
                      base::BindOnce(&YTMSBinding::OnPushReregiste,
                                     weak_factory_.GetWeakPtr(), param));
    return;
  }

  if (sessionId) {
    Emit("reregiste", sessionId);
    delete[] sessionId;
    sessionId = nullptr;
  } else {
    Emit("reregiste");
  }
}
void YTMSBinding::OnPushReboot(const char* sessionId) {
  LOG(INFO) << __FUNCTIONW__;

  Context* context = Context::Instance();
  if (!context->CalledOnValidThread()) {
    std::string id = sessionId;
    char* param = new char[id.size() + 1];
    strcpy(param, sessionId);

    context->PostTask(FROM_HERE,
                      base::BindOnce(&YTMSBinding::OnPushReboot,
                                     weak_factory_.GetWeakPtr(), param));
    return;
  }

  if (sessionId) {
    Emit("reboot", sessionId);
    delete[] sessionId;
    sessionId = nullptr;
  } else {
    Emit("reboot");
  }
}

void YTMSBinding::OnProcessCompeleted(Promise promise,
                                      ProcessObserver* observer) {
  if (observer) {
    int code =
        observer->bizCode() ? observer->bizCode() : observer->errorCode();
    std::move(promise).Resolve(code);
    delete observer;
    observer = nullptr;
  } else {
    std::move(promise).Resolve(0);
  }
}

v8::Local<v8::Promise> YTMSBinding::Start() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  ProcessObserver* observer = new ProcessObserver();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&YTMSBinding::DoStart, base::Unretained(this), observer),
      base::BindOnce(&YTMSBinding::OnProcessCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise), observer));

  return handle;
}
void YTMSBinding::DoStart(ProcessObserver* observer) {
  is_running_ = ytms_agent_->StartYtmsService(server_.c_str(), nullptr);
}

v8::Local<v8::Promise> YTMSBinding::Update(TerminalInfo params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  ProcessObserver* observer = new ProcessObserver();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&YTMSBinding::DoUpdate, base::Unretained(this), params,
                     observer),
      base::BindOnce(&YTMSBinding::OnProcessCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise), observer));

  return handle;
}
void YTMSBinding::DoUpdate(TerminalInfo params, ProcessObserver* observer) {
  YtmsConfigInfo config;

  config.clientName = params.name.c_str();
  config.clientType = params.type.c_str();
  config.clientCategory = params.category.c_str();
  config.clientModel = params.model.c_str();
  config.clientPlatform = params.platform.c_str();
  config.clientVersion = params.version.c_str();
  config.clientArch = params.arch.c_str();
  config.updateChannel = params.update_channel.c_str();
  config.customId = params.custom_id.c_str();
  config.configFileId = params.config_id.c_str();
  config.clientRemarks = params.remarks.c_str();

  config.model = params.device_model.c_str();
  config.resolution = params.device_resolution.c_str();
  config.os = params.device_os.c_str();
  config.ip = params.device_ip.c_str();
  config.mac = params.device_mac.c_str();
  config.hostname = params.device_hostname.c_str();
  config.cpu = params.device_cpu.c_str();
  config.memory = params.device_memory.c_str();

  config.userAccount = params.account.c_str();
  config.userName = params.display_name.c_str();
  config.userServerType = params.server_type.c_str();
  config.userServerAddress = params.server_address.c_str();
  config.userDomain = params.server_domain.c_str();
  config.userOutbound = params.server_outbound.c_str();
  config.registerStatus = params.register_status.c_str();

  config.enterpriseDomain = params.enterprise_domain.c_str();
  config.enterpriseId = params.enterprise_id.c_str();
  config.enterpriseName = params.enterprise_name.c_str();

  ytms_agent_->SetYtmsInfo(config, observer);
}

v8::Local<v8::Promise> YTMSBinding::UploadAlarm(AlarmInfo params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  ProcessObserver* observer = new ProcessObserver();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&YTMSBinding::DoUploadAlarm, base::Unretained(this),
                     params, observer),
      base::BindOnce(&YTMSBinding::OnProcessCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise), observer));

  return handle;
}
void YTMSBinding::DoUploadAlarm(AlarmInfo params, ProcessObserver* observer) {
  YtmsAlarm config;

  config.log = params.file_path.c_str();
  config.alarmCode = params.code.c_str();
  config.alarmName = params.name.c_str();
  config.alarmType = params.type.c_str();
  config.alarmLevel = params.level.c_str();
  config.alarmDesc = params.desc.c_str();

  ytms_agent_->UploadAlarm(config, observer);
}

v8::Local<v8::Promise> YTMSBinding::UploadFeedBack(FeedbackInfo params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  ProcessObserver* observer = new ProcessObserver();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&YTMSBinding::DoUploadFeedBack, base::Unretained(this),
                     params, observer),
      base::BindOnce(&YTMSBinding::OnProcessCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise), observer));

  return handle;
}
void YTMSBinding::DoUploadFeedBack(FeedbackInfo params,
                                   ProcessObserver* observer) {
  YtmsFeedback config;

  config.title = params.title.c_str();
  config.content = params.content.c_str();
  config.category = params.category.c_str();
  config.contactInfo = params.contact.c_str();
  config.logPath = params.file_path.c_str();
  config.imagePath = params.image_path.c_str();
  config.videoPath = params.video_path.c_str();

  ytms_agent_->UploadFeedback(config, observer);
}

v8::Local<v8::Promise> YTMSBinding::UploadEvent(EventInfo params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  ProcessObserver* observer = new ProcessObserver();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&YTMSBinding::DoUploadEvent, base::Unretained(this),
                     params, observer),
      base::BindOnce(&YTMSBinding::OnProcessCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise), observer));

  return handle;
}
void YTMSBinding::DoUploadEvent(EventInfo params, ProcessObserver* observer) {
  YtmsEvent config;

  config.eventCode = params.code.c_str();
  config.eventName = params.name.c_str();
  config.ispType = params.isp.c_str();
  config.networkMode = params.network.c_str();

  ytms_agent_->UploadEvent(config, observer);
}

v8::Local<v8::Promise> YTMSBinding::UploadConfig(mate::Arguments* args) {
  std::string body;

  if (!args->GetNext(&body)) {
    args->ThrowError("body is required to upload config info");
  }

  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  ProcessObserver* observer = new ProcessObserver();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&YTMSBinding::DoUploadConfig, base::Unretained(this), body,
                     observer),
      base::BindOnce(&YTMSBinding::OnProcessCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise), observer));

  return handle;
}
void YTMSBinding::DoUploadConfig(std::string params,
                                 ProcessObserver* observer) {
  ytms_agent_->UploadConfig(params.c_str(), observer);
}

v8::Local<v8::Promise> YTMSBinding::UploadLog(UploadLogInfo params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  ProcessObserver* observer = new ProcessObserver();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&YTMSBinding::DoUploadLog, base::Unretained(this), params,
                     observer),
      base::BindOnce(&YTMSBinding::OnProcessCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise), observer));

  return handle;
}
void YTMSBinding::DoUploadLog(UploadLogInfo params, ProcessObserver* observer) {
  YtmsLog config;

  config.sessionId = params.session_id.c_str();
  config.logPath = params.file_path.c_str();

  ytms_agent_->UploadLog(config, observer);
}

// get package info
v8::Local<v8::Promise> YTMSBinding::GetPackagesInfo() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&YTMSBinding::DoGetPackagesInfo, base::Unretained(this)),
      base::BindOnce(&YTMSBinding::OnGetPackagesCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}
void YTMSBinding::DoGetPackagesInfo() {
  ConvertFrom(package_info_, ytms_agent_->GetPackagesInfo(nullptr));
}
void YTMSBinding::OnGetPackagesCompeleted(Promise promise) {
  std::move(promise).Resolve(package_info_);
}

// get config info
v8::Local<v8::Promise> YTMSBinding::GetConfigFileInfo() {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&YTMSBinding::DoGetConfigFileInfo, base::Unretained(this)),
      base::BindOnce(&YTMSBinding::OnGetConfigCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise)));

  return handle;
}
void YTMSBinding::DoGetConfigFileInfo() {
  ConvertFrom(config_info_, ytms_agent_->GetConfigFileInfo(nullptr));
}
void YTMSBinding::OnGetConfigCompeleted(Promise promise) {
  std::move(promise).Resolve(config_info_);
}

// download
v8::Local<v8::Promise> YTMSBinding::DownloadFile(DownloadInfo params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  ProcessObserver* observer = new ProcessObserver();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&YTMSBinding::DoDownloadFile, base::Unretained(this),
                     params, observer),
      base::BindOnce(&YTMSBinding::OnProcessCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise), observer));

  return handle;
}
void YTMSBinding::DoDownloadFile(DownloadInfo params,
                                 ProcessObserver* observer) {
  yealink::DownloadInfo config;

  config.url = params.url.c_str();
  config.storePath = params.path.c_str();
  config.storeName = params.file_name.c_str();

  ytms_agent_->DownloadFile(config, observer);
}

std::vector<std::string> YTMSBinding::GetCaptureDevice() {
  std::vector<std::string> deviceInfo;

  ConvertFrom(deviceInfo, ytms_agent_->GetCaptureDevices());

  return deviceInfo;
}

// start capture
v8::Local<v8::Promise> YTMSBinding::StartCapture(NetCaptureInfo params) {
  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  ProcessObserver* observer = new ProcessObserver();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&YTMSBinding::DoStartCapture, base::Unretained(this),
                     params, observer),
      base::BindOnce(&YTMSBinding::OnProcessCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise), observer));

  return handle;
}
void YTMSBinding::DoStartCapture(NetCaptureInfo params,
                                 ProcessObserver* observer) {
  YtmsNetLog config;

  config.captureDeviceName = params.device_id.c_str();
  config.logPath = params.path.c_str();
  config.sessionId = params.session_id.c_str();

  ytms_agent_->StartCaptureNetLog(config, observer);
}

// stop capture
v8::Local<v8::Promise> YTMSBinding::StopCapture(mate::Arguments* args) {
  std::string sessionId;

  if (!args->GetNext(&sessionId)) {
    args->ThrowError("sessionId is required to stop capture");
  }

  Promise promise(isolate());
  v8::Local<v8::Promise> handle = promise.GetHandle();
  ProcessObserver* observer = new ProcessObserver();

  base::PostTaskAndReply(
      FROM_HERE,
      base::BindOnce(&YTMSBinding::DoStopCapture, base::Unretained(this),
                     sessionId, observer),
      base::BindOnce(&YTMSBinding::OnProcessCompeleted,
                     weak_factory_.GetWeakPtr(), std::move(promise), observer));

  return handle;
}
void YTMSBinding::DoStopCapture(std::string params, ProcessObserver* observer) {
  ytms_agent_->StopCaptureNetLog(params.c_str(), observer);
}

}  // namespace rtvc

}  // namespace yealink
