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

  std::string algorithm;
  std::string credential;

  EnterpriseInfo enterprise;
  TurnServerInfo turn_server;
};

using AccountInfoList = std::vector<AccountInfo>;

struct PartyInviteInfos {
  std::string url;
  int applicants;
  PartyInviteInfos() : url(""), applicants(0) {}
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_API_ACCOUNT_INFO_H_
