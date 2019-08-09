#ifndef YEALINK_RTVC_GLUE_STRUCT_TRAITS_H_
#define YEALINK_RTVC_GLUE_STRUCT_TRAITS_H_

#include <string>

#include "yealink/rtvc/api/account_info.h"

#include "yealink/libvc/include/access/access_define.h"

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

template <>
struct StructTraits<AccountInfo> {
  static bool From(AccountInfo& out, const yealink::LoginUserInfo& val);
};

template <>
struct StructTraits<AccountInfoList> {
  static bool From(AccountInfoList& out,
                   const yealink::Array<LoginUserInfo>& val);
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_GLUE_STRUCT_TRAITS_H_
