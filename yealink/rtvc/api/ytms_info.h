#ifndef YEALINK_RTVC_API_YTMS_INFO_H_
#define YEALINK_RTVC_API_YTMS_INFO_H_

#include <string>

namespace rtvc {

struct TerminalInfo {
  std::string name;
  std::string type;
  std::string category;
  std::string model;
  std::string platform;
  std::string version;
  std::string arch;
  std::string update_channel;
  std::string custom_id;
  std::string config_id;
  std::string remarks;

  std::string device_model;
  std::string device_resolution;
  std::string device_os;
  std::string device_ip;
  std::string device_mac;
  std::string device_hostname;
  std::string device_cpu;
  std::string device_memory;

  std::string account;
  std::string display_name;
  std::string server_type;
  std::string server_address;
  std::string server_domain;
  std::string server_outbound;
  std::string register_status;

  std::string enterprise_domain;
  std::string enterprise_id;
  std::string enterprise_name;
};

struct AlarmInfo {
  std::string file_path;
  std::string code;
  std::string name;
  std::string type;
  std::string level;
  std::string desc;
};

struct FeedbackInfo {
  std::string title;
  std::string content;
  std::string category;
  std::string contact;
  std::string file_path;
  std::string image_path;
  std::string video_path;
};

struct PackageInfo {
  std::string version;
  std::string date;
  std::string note;
  std::string name;
  std::string url;
  std::string md5;
  int size;
  bool force_update;
};

struct ConfigurationInfo {
  std::string id;
  std::string name;
  std::string url;
  std::string md5;
};

struct DownloadInfo {
 std::string url;
 std::string path;
 std::string file_name;
};

struct UploadLogInfo {
  std::string session_id;
  std::string file_path;
};

struct NetCaptureInfo {
  std::string path;
  std::string device_id;
  std::string session_id;
};

struct EventInfo {
  std::string code;
  std::string name;
  std::string network;
  std::string isp;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_API_ACCOUNT_INFO_H_
