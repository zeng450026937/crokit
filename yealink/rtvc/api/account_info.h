#ifndef YEALINK_RTVC_API_ACCOUNT_INFO_H_
#define YEALINK_RTVC_API_ACCOUNT_INFO_H_

#include <string>
#include <vector>

namespace rtvc {

struct EnterpriseInfo {
  std::string uid;
  std::string name;
  std::string number;
  std::string domain;
  std::string realm;
  std::string area;
  std::string country;
  std::string zone;
  bool frozen;
  int slot;
  int status;
  int subtype;
};

struct TurnServerInfo {
  std::string username;
  std::string password;
};

struct AccountInfo {
  std::string id;
  std::string uid;
  std::string number;
  std::string full_number;
  std::string name;
  std::string name_pinyin;
  std::string group_info;
  std::string token;
  int type;
  bool meetnow;

  std::string ha1;

  EnterpriseInfo enterprise;
  TurnServerInfo turn_server;
};

struct PrimaryAccountInfo {
  bool upgraded;
  std::string principle;
  std::string realm;
  std::string type;
  std::string algorithm;
  std::string ha1;
};

struct AccessInfo {
  PrimaryAccountInfo primary_account;
  std::vector<AccountInfo> account_list;
};

struct ErrorInfo {
  int biz_code;
};

struct SchedulerMetaInfo {
  std::string phonebook_version;
  std::vector<std::string> phonebook_support;
  std::string schedule_version;
  std::vector<std::string> schedule_support;
  std::string build;
  std::string version;
  std::string web_host;
  std::string service_account;
  std::string experience_account;
};

using AccountInfoList = std::vector<AccountInfo>;

struct PartyInviteInfos {
  std::string url;
  int applicants;
  PartyInviteInfos() : url(""), applicants(0) {}
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_API_ACCOUNT_INFO_H_
