#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

namespace rtvc {

// static
bool StructTraits<AccountInfo>::From(AccountInfo& out,
                                     const yealink::LoginUserInfo& val) {
  ConvertFrom(out.uid, val.account.uid);
  ConvertFrom(out.number, val.account.extension);
  ConvertFrom(out.full_number, val.account.principle);
  ConvertFrom(out.name, val.subject.name);
  ConvertFrom(out.name_pinyin, val.subject.namePinyinForSearch);
  ConvertFrom(out.group_info, val.subject.groupInfos);
  ConvertFrom(out.type, val.subject.type);
  ConvertFrom(out.enterprise.area, val.party.area);
  ConvertFrom(out.enterprise.country, val.party.country);
  ConvertFrom(out.enterprise.domain, val.party.domain);
  ConvertFrom(out.enterprise.frozen, val.party.frozen);
  ConvertFrom(out.enterprise.name, val.party.name);
  ConvertFrom(out.enterprise.number, val.party.number);
  ConvertFrom(out.enterprise.realm, val.party.realm);
  ConvertFrom(out.enterprise.slot, val.party.slot);
  ConvertFrom(out.enterprise.status, val.party.status);
  ConvertFrom(out.enterprise.subtype, val.party.subType);
  ConvertFrom(out.enterprise.uid, val.party.uid);
  ConvertFrom(out.enterprise.zone, val.party.zoneId);
  ConvertFrom(out.token, val.token);
  ConvertFrom(out.meetnow, val.permission.enableMeetingNow);
  return true;
}

// static
bool StructTraits<AccountInfoList>::From(
    AccountInfoList& out,
    const yealink::Array<LoginUserInfo>& val) {
  for (size_t i = 0; i < val.Size(); i++) {
    AccountInfo info;
    ConvertFrom(info, val[i]);
    out.emplace_back(info);
  }
  return true;
}

}  // namespace rtvc

}  // namespace yealink
