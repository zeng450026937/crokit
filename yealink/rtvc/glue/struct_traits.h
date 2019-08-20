#ifndef YEALINK_RTVC_GLUE_STRUCT_TRAITS_H_
#define YEALINK_RTVC_GLUE_STRUCT_TRAITS_H_

#include <string>
#include <vector>

#include "yealink/rtvc/api/account_info.h"
#include "yealink/rtvc/api/contact.h"
#include "yealink/rtvc/api/schedule_item.h"

#include "yealink/libvc/include/access/access_define.h"
#include "yealink/libvc/include/contact/cloud_contact_type.h"
#include "yealink/libvc/include/schedule/schedule_item.h"

namespace yealink {

namespace rtvc {

template <typename T1, typename T2 = void>
struct StructTraits {};

template <typename T1, typename T2>
typename std::enable_if<!std::is_same<T1, T2>::value, bool>::type ConvertFrom(
    T1& out,
    const T2& input) {
  return StructTraits<T1>::From(out, input);
}

template <typename T1, typename T2>
typename std::enable_if<std::is_same<T1, T2>::value, bool>::type ConvertFrom(
    T1& out,
    const T2& input) {
  out = input;
  return true;
}

template <typename T1, typename T2>
typename std::enable_if<!std::is_same<T1, T2>::value, bool>::type ConvertTo(
    const T1& input,
    T2& out) {
  return StructTraits<T1>::To(input, out);
}

template <typename T1, typename T2>
typename std::enable_if<std::is_same<T1, T2>::value, bool>::type ConvertTo(
    const T1& input,
    T2& out) {
  out = input;
  return true;
}

template <>
struct StructTraits<std::string> {
  static bool To(const std::string& val, yealink::SStringA& out) {
    out = yealink::SStringA(val.c_str());
    return true;
  }
  static bool From(std::string& out, const yealink::SStringA& val) {
    out = std::string(val.ConstData());
    return true;
  }
};

template <typename T>
struct StructTraits<std::vector<T>> {
  template <typename U>
  static bool To(const std::vector<T>& val, yealink::Array<U>& out) {
    for (auto& t : val) {
      U u;
      ConvertTo(t, u);
      out.Append(u);
    }
    return true;
  }
  template <typename U>
  static bool From(std::vector<T>& out, const yealink::Array<U>& val) {
    for (size_t i = 0; i < val.Size(); i++) {
      T t;
      ConvertFrom(t, val[i]);
      out.emplace_back(t);
    }
    return true;
  }
};

template <>
struct StructTraits<AccountInfo> {
  static bool From(AccountInfo& out, const yealink::LoginUserInfo& val);
};

template <>
struct StructTraits<ScheduleItemProfile> {
  static bool From(ScheduleItemProfile& out,
                   const yealink::ScheduleItemProfile& val);
};

template <>
struct StructTraits<ScheduleRecurrenceType> {
  static bool From(ScheduleRecurrenceType& out,
                   const yealink::ScheduleRecurrenceType& val);
};

template <>
struct StructTraits<ScheduleRecurrenceDailyType> {
  static bool From(ScheduleRecurrenceDailyType& out,
                   const yealink::ScheduleDailyType& val);
};

template <>
struct StructTraits<ScheduleRecurrenceRangeType> {
  static bool From(ScheduleRecurrenceRangeType& out,
                   const yealink::ScheduleRangeType& val);
};

template <>
struct StructTraits<ScheduleMemberRole> {
  static bool From(ScheduleMemberRole& out,
                   const yealink::ScheduleMemberRole& val);
};

template <>
struct StructTraits<ScheduleMemberType> {
  static bool From(ScheduleMemberType& out,
                   const yealink::ScheduleMemberType& val);
};

template <>
struct StructTraits<ScheduleRTMPLimitType> {
  static bool From(ScheduleRTMPLimitType& out,
                   const yealink::ScheduleRtmpWatchLimitType& val);
};

template <>
struct StructTraits<ScheduleDaylightStrategy> {
  static bool From(ScheduleDaylightStrategy& out,
                   const yealink::ScheduleDaylightStrategyInfo& val);
};

template <>
struct StructTraits<ScheduleTimeZoneRule> {
  static bool From(ScheduleTimeZoneRule& out,
                   const yealink::ScheduleTimeZoneRule& val);
};

template <>
struct StructTraits<ScheduleTimeZone> {
  static bool From(ScheduleTimeZone& out,
                   const yealink::ScheduleTimeZoneConfig& val);
};

template <>
struct StructTraits<ScheduleMember> {
  static bool From(ScheduleMember& out, const yealink::ScheduleMemberInfo& val);
};

template <>
struct StructTraits<ScheduleRoom> {
  static bool From(ScheduleRoom& out, const yealink::ScheduleRoomInfo& val);
};

template <>
struct StructTraits<ScheduleItem> {
  static bool From(ScheduleItem& out, const yealink::ScheduleSimpleInfo& val);
};

template <>
struct StructTraits<ScheduleItemDetail> {
  static bool From(ScheduleItemDetail& out,
                   const yealink::ScheduleDetailInfo& val);
};

template <>
struct StructTraits<ContactLoadMode> {
  static bool From(ContactLoadMode& out,
                   const yealink::CloudContactLoadMode& val);
};

template <>
struct StructTraits<ContactNodeType> {
  static bool From(ContactNodeType& out,
                   const yealink::CloudContactNodeType& val);
};

template <>
struct StructTraits<ContactNode> {
  static bool From(ContactNode& out, const yealink::CloudNodeInfo& val);
};

template <>
struct StructTraits<std::vector<ContactNode>> {
  static bool From(std::vector<ContactNode>& out,
                   const yealink::CloudSubNodeInfo& val);
  static bool From(std::vector<ContactNode>& out,
                   const yealink::Array<yealink::CloudNodeInfo>& val);
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_GLUE_STRUCT_TRAITS_H_
