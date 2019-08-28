#include "yealink/rtvc/glue/struct_traits.h"

namespace yealink {

namespace rtvc {

// static
bool StructTraits<AccountInfo>::From(AccountInfo& out,
                                     const yealink::LoginUserInfo& val) {
  ConvertFrom(out.id, val.account.uid);
  ConvertFrom(out.uid, val.subject.uid);
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
bool StructTraits<ScheduleItemProfile>::From(
    ScheduleItemProfile& out,
    const yealink::ScheduleItemProfile& val) {
  switch (val) {
    case yealink::ScheduleItemProfile::SCHEDULE_ITEM_PROFILE_DEFAULT:
      out = ScheduleItemProfile::kDefault;
      break;
    case yealink::ScheduleItemProfile::SCHEDULE_ITEM_PROFILE_EDUCATION:
      out = ScheduleItemProfile::kEducation;
      break;
    case yealink::ScheduleItemProfile::SCHEDULE_ITEM_PROFILE_SEMINAR:
      out = ScheduleItemProfile::kSeminar;
      break;
    default:
      out = ScheduleItemProfile::kDefault;
      break;
  }

  return true;
}

// static
bool StructTraits<ScheduleRecurrenceType>::From(
    ScheduleRecurrenceType& out,
    const yealink::ScheduleRecurrenceType& val) {
  switch (val) {
    case yealink::ScheduleRecurrenceType::SCHEDULE_RECURRENCE_TYPE_INVALID:
      out = ScheduleRecurrenceType::kNone;
      break;
    case yealink::ScheduleRecurrenceType::SCHEDULE_RECURRENCE_TYPE_DAILY:
      out = ScheduleRecurrenceType::kDaily;
      break;
    case yealink::ScheduleRecurrenceType::SCHEDULE_RECURRENCE_TYPE_WEEKLY:
      out = ScheduleRecurrenceType::kWeekly;
      break;
    case yealink::ScheduleRecurrenceType::SCHEDULE_RECURRENCE_TYPE_MONTHLY:
      out = ScheduleRecurrenceType::kMonthly;
      break;
    case yealink::ScheduleRecurrenceType::SCHEDULE_RECURRENCE_TYPE_MONTH_NTH:
      out = ScheduleRecurrenceType::kMonthlyNTH;
      break;
    case yealink::ScheduleRecurrenceType::SCHEDULE_RECURRENCE_TYPE_YEAR_NTH:
      out = ScheduleRecurrenceType::kYearlyNTH;
      break;
    case yealink::ScheduleRecurrenceType::SCHEDULE_RECURRENCE_TYPE_YEARLY:
      out = ScheduleRecurrenceType::kYearly;
      break;
    default:
      out = ScheduleRecurrenceType::kNone;
      break;
  }

  return true;
}

// static
bool StructTraits<ScheduleRecurrenceDailyType>::From(
    ScheduleRecurrenceDailyType& out,
    const yealink::ScheduleDailyType& val) {
  switch (val) {
    case yealink::ScheduleDailyType::SCHEDULE_DAILY_TYPE_INVALID:
      out = ScheduleRecurrenceDailyType::kNone;
      break;
    case yealink::ScheduleDailyType::SCHEDULE_DAILY_TYPE_EACH:
      out = ScheduleRecurrenceDailyType::kEach;
      break;
    case yealink::ScheduleDailyType::SCHEDULE_DAILY_TYPE_WEEKDAY:
      out = ScheduleRecurrenceDailyType::kWeekday;
      break;
    default:
      out = ScheduleRecurrenceDailyType::kNone;
      break;
  }

  return true;
}

// static
bool StructTraits<ScheduleRecurrenceRangeType>::From(
    ScheduleRecurrenceRangeType& out,
    const yealink::ScheduleRangeType& val) {
  switch (val) {
    case yealink::ScheduleRangeType::SCHEDULE_RANGE_TYPE_FOREVER:
      out = ScheduleRecurrenceRangeType::kForever;
      break;
    case yealink::ScheduleRangeType::SCHEDULE_RANGE_TYPE_TIMES:
      out = ScheduleRecurrenceRangeType::kTimes;
      break;
    case yealink::ScheduleRangeType::SCHEDULE_RANGE_TYPE_UNTIL:
      out = ScheduleRecurrenceRangeType::kUntil;
      break;
    default:
      out = ScheduleRecurrenceRangeType::kTimes;
      break;
  }

  return true;
}

// static
bool StructTraits<ScheduleMemberRole>::From(
    ScheduleMemberRole& out,
    const yealink::ScheduleMemberRole& val) {
  switch (val) {
    case yealink::ScheduleMemberRole::SCHEDULE_MEMBER_ROLE_CAST_VIEWER:
      out = ScheduleMemberRole::kCastViewer;
      break;
    case yealink::ScheduleMemberRole::SCHEDULE_MEMBER_ROLE_ORGANIZER:
      out = ScheduleMemberRole::kOrganizer;
      break;
    case yealink::ScheduleMemberRole::SCHEDULE_MEMBER_ROLE_PARTICIPANT:
      out = ScheduleMemberRole::kPaticipant;
      break;
    case yealink::ScheduleMemberRole::SCHEDULE_MEMBER_ROLE_PRESENTER:
      out = ScheduleMemberRole::kPresenter;
      break;
    default:
      out = ScheduleMemberRole::kPaticipant;
      break;
  }

  return true;
}

// static
bool StructTraits<ScheduleMemberType>::From(
    ScheduleMemberType& out,
    const yealink::ScheduleMemberType& val) {
  switch (val) {
    case yealink::ScheduleMemberType::SCHEDULE_MEMBER_TYPE_OUTSIDER:
      out = ScheduleMemberType::kExternal;
      break;
    case yealink::ScheduleMemberType::SCHEDULE_MEMBER_TYPE_INSIDER:
      out = ScheduleMemberType::kInternal;
      break;
    default:
      out = ScheduleMemberType::kInternal;
      break;
  }

  return true;
}

// static
bool StructTraits<ScheduleRTMPLimitType>::From(
    ScheduleRTMPLimitType& out,
    const yealink::ScheduleRtmpWatchLimitType& val) {
  switch (val) {
    case yealink::ScheduleRtmpWatchLimitType::SCHEDULE_WATCH_TYPE_BY_ALL:
      out = ScheduleRTMPLimitType::kAll;
      break;
    case yealink::ScheduleRtmpWatchLimitType::SCHEDULE_WATCH_TYPE_BY_PASSWORD:
      out = ScheduleRTMPLimitType::kPassword;
      break;
    default:
      out = ScheduleRTMPLimitType::kPassword;
      break;
  }

  return true;
}

// static
bool StructTraits<ScheduleDaylightStrategy>::From(
    ScheduleDaylightStrategy& out,
    const yealink::ScheduleDaylightStrategyInfo& val) {
  ConvertFrom(out.day, val.day);
  ConvertFrom(out.dayOfWeek, val.dayOfWeek);
  ConvertFrom(out.isFixedDateRule, val.isFixedDateRule);
  ConvertFrom(out.month, val.month);
  ConvertFrom(out.timeOfDay, val.timeOfDay);
  ConvertFrom(out.week, val.week);
  return true;
}

// static
bool StructTraits<ScheduleTimeZoneRule>::From(
    ScheduleTimeZoneRule& out,
    const yealink::ScheduleTimeZoneRule& val) {
  ConvertFrom(out.daylightDelta, val.daylightDelta);
  ConvertFrom(out.daylightStrategyEnd, val.daylightStrategyEnd);
  ConvertFrom(out.daylightStrategyStart, val.daylightStrategyStart);
  ConvertFrom(out.endDate, val.dateEnd);
  ConvertFrom(out.startDate, val.dateStart);
  return true;
}

// static
bool StructTraits<ScheduleTimeZone>::From(
    ScheduleTimeZone& out,
    const yealink::ScheduleTimeZoneConfig& val) {
  ConvertFrom(out.id, val.zoneId);
  ConvertFrom(out.cnName, val.cnZoneName);
  ConvertFrom(out.usName, val.usZoneName);
  ConvertFrom(out.utcOffset, val.utcOffset);
  ConvertFrom(out.utcOffsetName, val.offsetDisplayName);
  ConvertFrom(out.rule, val.rule);
  return true;
}

// static
bool StructTraits<ScheduleMember>::From(
    ScheduleMember& out,
    const yealink::ScheduleMemberInfo& val) {
  ConvertFrom(out.id, val.identifier);
  ConvertFrom(out.name, val.showName);
  ConvertFrom(out.number, val.extension);
  ConvertFrom(out.role, val.role);
  ConvertFrom(out.type, val.type);
  return true;
}

// static
bool StructTraits<ScheduleRoom>::From(ScheduleRoom& out,
                                      const yealink::ScheduleRoomInfo& val) {
  ConvertFrom(out.id, val.roomId);
  ConvertFrom(out.name, val.name);
  return true;
}

// static
bool StructTraits<ScheduleItem>::From(ScheduleItem& out,
                                      const yealink::ScheduleSimpleInfo& val) {
  ConvertFrom(out.planId, val.planId);
  ConvertFrom(out.sequence, val.sequence);
  ConvertFrom(out.profile, val.profile);
  ConvertFrom(out.subject, val.subject);
  ConvertFrom(out.organizer, val.organizerName);
  ConvertFrom(out.timezoneId, val.zoneId);
  ConvertFrom(out.timezone, val.timeZoneConfig);
  ConvertFrom(out.aheadTime, val.aheadTime);
  ConvertFrom(out.startTime, val.startDateTime);
  ConvertFrom(out.endTime, val.endDateTime);
  ConvertFrom(out.confNum, val.conferenceNo);
  ConvertFrom(out.confPwd, val.conferencePwd);
  ConvertFrom(out.isRTMP, val.isRtmp);
  ConvertFrom(out.roomNames, val.roomNames);
  ConvertFrom(out.recurrence.type, val.recurrenceType);
  ConvertFrom(out.recurrence.dailyType, val.dailyType);
  ConvertFrom(out.recurrence.rangeType, val.rangeType);
  ConvertFrom(out.recurrence.interval,
              static_cast<int64_t>(val.recurrenceInterval));
  ConvertFrom(out.recurrence.count, static_cast<int64_t>(val.rangeOccurrences));
  ConvertFrom(out.recurrence.startDate, val.rangeStartDate);
  ConvertFrom(out.recurrence.endDate, val.rangeEndDate);
  ConvertFrom(out.dayOfWeek, val.dayOfWeek);
  // ConvertFrom(out.dayOfWeekIndex, val.dayOfWeekIndex);
  out.dayOfWeekIndex = 0;
  ConvertFrom(out.dayOfMonth, static_cast<int64_t>(val.dayOfMonth));
  ConvertFrom(out.monthOfYear, static_cast<int64_t>(val.monthOfYear));
  return true;
}

// static
bool StructTraits<ScheduleItemDetail>::From(
    ScheduleItemDetail& out,
    const yealink::ScheduleDetailInfo& val) {
  ConvertFrom(out.remark, val.remark);
  ConvertFrom(out.organizer, val.organizer);
  ConvertFrom(out.participants, val.participants);
  ConvertFrom(out.rooms, val.rooms);
  ConvertFrom(out.rtmp.autoRecord, val.rtmpAutoRecord);
  ConvertFrom(out.rtmp.limitType, val.rtmpWatchLimitType);
  ConvertFrom(out.rtmp.logoUrl, val.rtmpLogoUrl);
  ConvertFrom(out.rtmp.password, val.rtmpWatchPwd);
  ConvertFrom(out.rtmp.url, val.rtmpWatchUrl);
  return true;
}

// static
bool StructTraits<ContactLoadMode>::From(
    ContactLoadMode& out,
    const yealink::CloudContactLoadMode& val) {
  switch (val) {
    case yealink::CloudContactLoadMode::CC_LOAD_AUTO:
      out = ContactLoadMode::kAuto;
      break;
    case yealink::CloudContactLoadMode::CC_LOAD_OVERALL:
      out = ContactLoadMode::kOverall;
      break;
    case yealink::CloudContactLoadMode::CC_LOAD_PARTIAL:
      out = ContactLoadMode::kPartial;
      break;
    default:
      out = ContactLoadMode::kAuto;
      break;
  }

  return true;
}

// static
bool StructTraits<ContactNodeType>::From(
    ContactNodeType& out,
    const yealink::CloudContactNodeType& val) {
  switch (val) {
    case yealink::CloudContactNodeType::CC_NODE_DEPARTMENT:
      out = ContactNodeType::kDepartment;
      break;
    case yealink::CloudContactNodeType::CC_NODE_DEVICE:
      out = ContactNodeType::kDevice;
      break;
    case yealink::CloudContactNodeType::CC_NODE_PARTY_MANAGER:
      out = ContactNodeType::kEnterprise;
      break;
    case yealink::CloudContactNodeType::CC_NODE_MEETING_ROOM:
      out = ContactNodeType::kRoom;
      break;
    case yealink::CloudContactNodeType::CC_NODE_STAFF:
      out = ContactNodeType::kStaff;
      break;
    case yealink::CloudContactNodeType::CC_NODE_THIRD_PARTY:
      out = ContactNodeType::kThirdParty;
      break;
    case yealink::CloudContactNodeType::CC_NODE_VMR:
      out = ContactNodeType::kVMR;
      break;
    default:
      out = ContactNodeType::kDevice;
      break;
  }

  return true;
}

// static
bool StructTraits<ContactNode>::From(ContactNode& out,
                                     const yealink::CloudNodeInfo& val) {
  ConvertFrom(out.uid, val.nodeId);
  ConvertFrom(out.type, val.type);
  ConvertFrom(out.parentId, val.parentID);
  ConvertFrom(out.childCounts,
              static_cast<uint64_t>(val.contactCountRecursive));
  ConvertFrom(out.name, val.name);
  ConvertFrom(out.i18nName, val.i18nName);
  ConvertFrom(out.pinyin, val.pinyin);
  ConvertFrom(out.pinyinAbbr, val.pinyinAbbr);
  ConvertFrom(out.email, val.email);
  ConvertFrom(out.number, val.number);
  ConvertFrom(out.fullNumber, val.extensionNum);
  return true;
}

// static
bool StructTraits<std::vector<ContactNode>>::From(
    std::vector<ContactNode>& out,
    const yealink::CloudSubNodeInfo& val) {
  for (size_t i = 0; i < val.cloudInfoList.Size(); i++) {
    ContactNode node;
    ConvertFrom(node, val.cloudInfoList[i]);
    out.emplace_back(node);
  }
  return true;
}

// static
bool StructTraits<std::vector<ContactNode>>::From(
    std::vector<ContactNode>& out,
    const yealink::Array<yealink::CloudNodeInfo>& val) {
  for (size_t i = 0; i < val.Size(); i++) {
    ContactNode node;
    ConvertFrom(node, val[i]);
    out.emplace_back(node);
  }
  return true;
}

// static
// bool StructTraits<TerminalInfo>::From(TerminalInfo& out,
//                                      const yealink::YtmsConfigInfo& val) {
//   ConvertFrom(out.name, val.clientName);
//   ConvertFrom(out.type, val.clientType);
//   ConvertFrom(out.category, val.clientCategory);
//   ConvertFrom(out.model, val.clientModel);
//   ConvertFrom(out.version, val.clientVersion);
//   ConvertFrom(out.arch, val.clientArch);
//   ConvertFrom(out.update_channel, val.updateChannel);
//   ConvertFrom(out.custom_id, val.customId);
//   ConvertFrom(out.config_id, val.configFileId);
//   ConvertFrom(out.remarks, val.clientRemarks);

//   ConvertFrom(out.device_model, val.model);
//   ConvertFrom(out.device_resolution, val.resolution);
//   ConvertFrom(out.device_os, val.os);
//   ConvertFrom(out.device_ip, val.ip);
//   ConvertFrom(out.device_mac, val.mac);
//   ConvertFrom(out.device_hostname, val.hostname);
//   ConvertFrom(out.device_cpu, val.cpu);
//   ConvertFrom(out.device_memory, val.memory);

//   ConvertFrom(out.account, val.userAccount);
//   ConvertFrom(out.display_name, val.userName);
//   ConvertFrom(out.server_type, val.userServerType);
//   ConvertFrom(out.server_address, val.userServerAddress);
//   ConvertFrom(out.server_domain, val.userDomain);
//   ConvertFrom(out.server_outbound, val.userOutbound);

//   ConvertFrom(out.enterprise_domain, val.enterpriseDomain);
//   ConvertFrom(out.enterprise_id, val.enterpriseId);
//   ConvertFrom(out.enterprise_name, val.enterpriseName);

//   return true;
// }

// static
bool StructTraits<PackageInfo>::From(PackageInfo& out,
                                     const yealink::PackageInfo& val) {
  ConvertFrom(out.version, val.clientVersion);
  ConvertFrom(out.date, val.releaseDate);
  ConvertFrom(out.note, val.releaseNote);
  ConvertFrom(out.name, val.fileName);
  ConvertFrom(out.url, val.fileUrl);
  ConvertFrom(out.md5, val.fileMd5);
  ConvertFrom(out.size, val.fileSize);
  ConvertFrom(out.force_update, val.forceUpdate);

  return true;
}

// static
bool StructTraits<ConfigurationInfo>::From(ConfigurationInfo& out,
                                     const yealink::ConfigFileInfo& val) {
  ConvertFrom(out.id, val.configId);
  ConvertFrom(out.name, val.configName);
  ConvertFrom(out.url, val.downloadUrl);
  ConvertFrom(out.md5, val.fileMd5);

  return true;
}

}  // namespace rtvc

}  // namespace yealink
