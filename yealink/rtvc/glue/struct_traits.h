#ifndef YEALINK_RTVC_GLUE_STRUCT_TRAITS_H_
#define YEALINK_RTVC_GLUE_STRUCT_TRAITS_H_

#include <string>
#include <vector>

#include "yealink/rtvc/api/account_info.h"
#include "yealink/rtvc/api/channel.h"
#include "yealink/rtvc/api/conference_desc.h"
#include "yealink/rtvc/api/conference_state.h"
#include "yealink/rtvc/api/conference_user.h"
#include "yealink/rtvc/api/conference_view.h"
#include "yealink/rtvc/api/contact.h"
#include "yealink/rtvc/api/schedule_item.h"
#include "yealink/rtvc/api/ytms_info.h"

#include "yealink/libvc/include/access/access_define.h"
#include "yealink/libvc/include/contact/cloud_contact_type.h"
#include "yealink/libvc/include/media/media_api.h"
#include "yealink/libvc/include/room/room_data.h"
#include "yealink/libvc/include/schedule/schedule_item.h"
#include "yealink/libvc/include/ytms/ytms_define.h"

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

template <>
struct StructTraits<TerminalInfo> {
  static bool From(TerminalInfo& out, const yealink::YtmsConfigInfo& val);
};

template <>
struct StructTraits<PackageInfo> {
  static bool From(PackageInfo& out, const yealink::PackageInfo& val);
};

template <>
struct StructTraits<ConfigurationInfo> {
  static bool From(ConfigurationInfo& out, const yealink::ConfigFileInfo& val);
};

// description
template <>
struct StructTraits<DescProfile> {
  static bool From(DescProfile& out,
                   const yealink::ConferenceDescription::Profile& val);
};

template <>
struct StructTraits<DescPosition> {
  static bool From(DescPosition& out,
                   const yealink::ConferenceDescription::Banner::Position& val);
};

template <>
struct StructTraits<DescBanner> {
  static bool From(DescBanner& out,
                   const yealink::ConferenceDescription::Banner& val);
};

template <>
struct StructTraits<DescRtmpSessionType> {
  static bool From(
      DescRtmpSessionType& out,
      const yealink::ConferenceDescription::DefaultRtmp::McuSessionType& val);
};

template <>
struct StructTraits<DescRtmpFsType> {
  static bool From(
      DescRtmpFsType& out,
      const yealink::ConferenceDescription::DefaultRtmp::MaxVideoFs& val);
};

template <>
struct StructTraits<DescDefaultRtmp> {
  static bool From(DescDefaultRtmp& out,
                   const yealink::ConferenceDescription::DefaultRtmp& val);
};

template <>
struct StructTraits<DescUriPurpose> {
  static bool From(DescUriPurpose& out,
                   const yealink::ConferenceDescription::Entry::Purpose& val);
};

template <>
struct StructTraits<DescConfUriInfo> {
  static bool From(DescConfUriInfo& out,
                   const yealink::ConferenceDescription::Entry& val);
};

template <>
struct StructTraits<DescOrganizerInfo> {
  static bool From(DescOrganizerInfo& out,
                   const yealink::ConferenceDescription::OrganizerInfo& val);
};

template <>
struct StructTraits<DescConferenceType> {
  static bool From(DescConferenceType& out,
                   const yealink::ConferenceDescription::ConferenceType& val);
};

template <>
struct StructTraits<DescNumberType> {
  static bool From(
      DescNumberType& out,
      const yealink::ConferenceDescription::ConferenceNumberType& val);
};

template <>
struct StructTraits<DescAdmissionPolicy> {
  static bool From(DescAdmissionPolicy& out,
                   const yealink::ConferenceDescription::AdmissionPolicy& val);
};
template <>
struct StructTraits<DescAttendeeByPass> {
  static bool From(DescAttendeeByPass& out,
                   const yealink::ConferenceDescription::AttendeeByPass& val);
};
template <>
struct StructTraits<DescAutoPromote> {
  static bool From(DescAutoPromote& out,
                   const yealink::ConferenceDescription::AutoPromote& val);
};

template <>
struct StructTraits<DescRecordType> {
  static bool From(DescRecordType& out,
                   const yealink::ConferenceDescription::RecordServerType& val);
};
template <>
struct StructTraits<DescRecordPrivilege> {
  static bool From(DescRecordPrivilege& out,
                   const yealink::ConferenceDescription::RecordPrivilege& val);
};

template <>
struct StructTraits<DescInfo> {
  static bool From(DescInfo& out, const yealink::ConferenceDescription& val);
};
// state

// users
template <>
struct StructTraits<RequesrResult> {
  static bool From(RequesrResult& out, const yealink::ConferenceResult& val);
};

template <>
struct StructTraits<ResponseInfo> {
  static bool From(ResponseInfo& out, const yealink::RequestResult& val);
};

template <>
struct StructTraits<UserProtocolType> {
  static bool From(UserProtocolType& out,
                   const yealink::MemberInfo::Protocol& val);
};

template <>
struct StructTraits<UserPermissionType> {
  static bool From(UserPermissionType& out,
                   const yealink::MemberInfo::Roles::PermissionRole& val);
};

template <>
struct StructTraits<UserDemoStateType> {
  static bool From(UserDemoStateType& out,
                   const yealink::MemberInfo::Roles::DemoStateRole& val);
};

template <>
struct StructTraits<PresenterDemoStateType> {
  static bool From(
      PresenterDemoStateType& out,
      const yealink::MemberInfo::Roles::PresenterDemoStateRole& val);
};

template <>
struct StructTraits<UserRolesInfo> {
  static bool From(UserRolesInfo& out, const yealink::MemberInfo::Roles& val);
};

template <>
struct StructTraits<UserEndpointSeesionType> {
  static bool From(UserEndpointSeesionType& out,
                   const yealink::MemberInfo::Endpoint::SessionType& val);
};

template <>
struct StructTraits<UserEndpointStatusType> {
  static bool From(UserEndpointStatusType& out,
                   const yealink::MemberInfo::Endpoint::Status& val);
};

template <>
struct StructTraits<UserJoinMethod> {
  static bool From(UserJoinMethod& out,
                   const yealink::MemberInfo::Endpoint::JoiningMethod& val);
};

template <>
struct StructTraits<UserMediaType> {
  static bool From(UserMediaType& out,
                   const yealink::MemberInfo::Endpoint::Media::Type& val);
};

template <>
struct StructTraits<UserMediaLabelType> {
  static bool From(UserMediaLabelType& out,
                   const yealink::MemberInfo::Endpoint::Media::Label& val);
};

template <>
struct StructTraits<UserMediaDirectionType> {
  static bool From(UserMediaDirectionType& out,
                   const yealink::MemberInfo::Endpoint::Media::Status& val);
};

template <>
struct StructTraits<UserMediafilterType> {
  static bool From(
      UserMediafilterType& out,
      const yealink::MemberInfo::Endpoint::Media::MediaFilter& val);
};

template <>
struct StructTraits<UserMediaBlockByType> {
  static bool From(UserMediaBlockByType& out,
                   const yealink::MemberInfo::Endpoint::Media::BlockBy& val);
};

template <>
struct StructTraits<UserMediaInfo> {
  static bool From(UserMediaInfo& out,
                   const yealink::MemberInfo::Endpoint::Media& val);
};

template <>
struct StructTraits<UserMediaFilterInfo> {
  static bool From(UserMediaFilterInfo& out,
                   const yealink::MemberInfo::Endpoint::Media& val);
};

template <>
struct StructTraits<UserEndpointInfo> {
  static bool From(UserEndpointInfo& out,
                   const yealink::MemberInfo::Endpoint& val);
};

template <>
struct StructTraits<UserInfo> {
  static bool From(UserInfo& out, const yealink::MemberInfo& val);
};

template <>
struct StructTraits<UserMediaDataInfo> {
  static bool From(UserMediaDataInfo& out, const yealink::UserMediaDetail& val);
};

template <>
struct StructTraits<UserStatisticsInfo> {
  static bool From(UserStatisticsInfo& out, const yealink::UserMediaInfo& val);
};

// view
template <>
struct StructTraits<ViewSpeakMode> {
  static bool From(ViewSpeakMode& out,
                   const yealink::ConferenceViewSpeakMode& val);
};

template <>
struct StructTraits<ViewLayoutType> {
  static bool From(
      ViewLayoutType& out,
      const yealink::ConferenceView::EntityState::VideoLayout& val);
};

template <>
struct StructTraits<ViewPresenterLayoutType> {
  static bool From(
      ViewPresenterLayoutType& out,
      const yealink::ConferenceView::EntityState::VideoPresenterLayout& val);
};

template <>
struct StructTraits<GetLayoutInfo> {
  static bool From(GetLayoutInfo& out,
                   const yealink::ConferenceView::EntityState& val);
};

template <>
struct StructTraits<ViewFilterRoleType> {
  static bool From(ViewFilterRoleType& out,
                   const yealink::ConferenceView::EntityState::
                       MediaFiltersRules::InitialFilter::Role& val);
};

template <>
struct StructTraits<ViewFilterType> {
  static bool From(ViewFilterType& out,
                   const yealink::ConferenceView::EntityState::
                       MediaFiltersRules::InitialFilter::Filter& val);
};

template <>
struct StructTraits<ViewFilterRuleInfo> {
  static bool From(ViewFilterRuleInfo& out,
                   const yealink::ConferenceView::EntityState::
                       MediaFiltersRules::InitialFilter& val);
};

template <>
struct StructTraits<StatsAudioCodecType> {
  static bool From(StatsAudioCodecType& out, const yealink::AudioCodecs& val);
};

template <>
struct StructTraits<StatsVideoCodecType> {
  static bool From(StatsVideoCodecType& out, const yealink::VideoCodecs& val);
};

template <>
struct StructTraits<StatsVideoProfileType> {
  static bool From(StatsVideoProfileType& out,
                   const yealink::VideoCodecProfile& val);
};

template <>
struct StructTraits<VideoStatsInfo> {
  static bool From(VideoStatsInfo& out, const yealink::VideoChannelStats& val);
};

template <>
struct StructTraits<RTCVideoStats> {
  static bool From(RTCVideoStats& out, const yealink::VideoStreamStats& val);
};

template <>
struct StructTraits<RTCAudioStats> {
  static bool From(RTCAudioStats& out, const yealink::AudioStreamStats& val);
};

template <>
struct StructTraits<RTCStats> {
  static bool From(RTCStats& out, const yealink::MediaStreamStats& val);
};

}  // namespace rtvc

}  // namespace yealink

#endif  // YEALINK_RTVC_GLUE_STRUCT_TRAITS_H_
