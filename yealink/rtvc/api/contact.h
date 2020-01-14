#ifndef YEALINK_RTVC_API_CONTACT_H_
#define YEALINK_RTVC_API_CONTACT_H_

#include <string>
#include <vector>

namespace rtvc {

enum class ContactLoadMode {
  kAuto,
  kOverall,
  kPartial,
};

enum class ContactNodeType {
  kDepartment,
  kStaff,
  kDevice,
  kVMR,
  kThirdParty,
  kRoom,
  kEnterprise,
};

struct ContactNode {
  std::string uid;
  ContactNodeType type;
  std::vector<std::string> parentId;
  uint64_t childCounts;

  std::string name;
  std::string i18nName;
  std::string pinyin;
  std::string pinyinAbbr;
  std::string email;
  std::string phone;
  std::string mobile;
  std::string number;
  std::string fullNumber;
};

struct ContactNodeUpdated {
  std::string uid;
  std::string operate;
  ContactNodeType type;
  std::string pid;
  std::string oldPid;
};

struct ContactConfig {
  std::string workspace_folder;
  std::string database_name;
};

class Contact {
 public:
  void Create();
  void Remove();
  void Update();
  void Search();
  // alias for create
  void Add();
  // alias for update
  void Modify();
  // alias for search
  void Find();

 protected:
  virtual ~Contact() = default;
};

struct LocalContactConfig : public ContactConfig {};

class LocalContact : public Contact {
 public:
  // support paging acquisition
  // limit 0 to acquire all
  // acquire all by default
  std::vector<ContactNode> GetList(uint64_t limit, uint64_t offset);

 protected:
  virtual ~LocalContact() override = default;
};

class ConnectorBinding;

struct CloudContactConfig : public ContactConfig {
  ConnectorBinding* connector;
  std::string server;
};

class CloudContact {
 public:
  bool synced();
  void load_mode();

  std::string root_id();
  std::string self_id();

  void Sync();
  void Search();

  ContactNode GetNode(std::string nodeId);
  std::vector<ContactNode> GetNodeChild(std::string nodeId, bool recursive);

 protected:
  virtual ~CloudContact() = default;
};

}  // namespace rtvc

#endif  // YEALINK_RTVC_API_CONTACT_H_
