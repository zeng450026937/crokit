#include "yealink/rtvc/glue/struct_traits.h"

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
  ConvertFrom(out.turn_server.username, val.turnServer.username);
  ConvertFrom(out.turn_server.password, val.turnServer.password);
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

// description
bool StructTraits<DescProfile>::From(
    DescProfile& out,
    const yealink::ConferenceDescription::Profile& val) {
  switch (val) {
    case yealink::ConferenceDescription::Profile::CONFERENCE:
      out = DescProfile::kConference;
      break;
    case yealink::ConferenceDescription::Profile::TEACHING:
      out = DescProfile::kTeaching;
      break;
    case yealink::ConferenceDescription::Profile::SEMINAR:
      out = DescProfile::kSeminar;
      break;
    default:
      out = DescProfile::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<DescPosition>::From(
    DescPosition& out,
    const yealink::ConferenceDescription::Banner::Position& val) {
  switch (val) {
    case yealink::ConferenceDescription::Banner::Position::TOP:
      out = DescPosition::kTop;
      break;
    case yealink::ConferenceDescription::Banner::Position::MEDIUM:
      out = DescPosition::kMedium;
      break;
    case yealink::ConferenceDescription::Banner::Position::BOTTOM:
      out = DescPosition::kBottom;
      break;
    default:
      out = DescPosition::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<DescBanner>::From(
    DescBanner& out,
    const yealink::ConferenceDescription::Banner& val) {
  ConvertFrom(out.enabled, val.enabled);
  ConvertFrom(out.display_text, val.displayText);
  ConvertFrom(out.position, val.position);

  return true;
}

bool StructTraits<DescRtmpSessionType>::From(
    DescRtmpSessionType& out,
    const yealink::ConferenceDescription::DefaultRtmp::McuSessionType& val) {
  switch (val) {
    case yealink::ConferenceDescription::DefaultRtmp::McuSessionType::MCU_AV:
      out = DescRtmpSessionType::kAV;
      break;
    case yealink::ConferenceDescription::DefaultRtmp::McuSessionType::MCU_AD:
      out = DescRtmpSessionType::kAD;
      break;
    case yealink::ConferenceDescription::DefaultRtmp::McuSessionType::MCU_AVD:
      out = DescRtmpSessionType::kAVD;
      break;
    default:
      out = DescRtmpSessionType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<DescRtmpFsType>::From(
    DescRtmpFsType& out,
    const yealink::ConferenceDescription::DefaultRtmp::MaxVideoFs& val) {
  switch (val) {
    case yealink::ConferenceDescription::DefaultRtmp::MaxVideoFs::FS_360P:
      out = DescRtmpFsType::k360P;
      break;
    case yealink::ConferenceDescription::DefaultRtmp::MaxVideoFs::FS_720P:
      out = DescRtmpFsType::k720P;
      break;
    case yealink::ConferenceDescription::DefaultRtmp::MaxVideoFs::FS_1080P:
      out = DescRtmpFsType::k1080P;
      break;
    default:
      out = DescRtmpFsType::kInvalid;
      break;
  }

  return true;
}
bool StructTraits<DescDefaultRtmp>::From(
    DescDefaultRtmp& out,
    const yealink::ConferenceDescription::DefaultRtmp& val) {
  ConvertFrom(out.enabled, val.enabled);
  ConvertFrom(out.display_text, val.displayText);
  ConvertFrom(out.mcu_session_type, val.mcuSessionType);
  ConvertFrom(out.max_video_fs, val.maxVideoFs);
  ConvertFrom(out.web_share_url, val.webShareUrl);

  return true;
}

bool StructTraits<DescUriPurpose>::From(
    DescUriPurpose& out,
    const yealink::ConferenceDescription::Entry::Purpose& val) {
  switch (val) {
    case yealink::ConferenceDescription::Entry::Purpose::FOCUS:
      out = DescUriPurpose::kFocus;
      break;
    case yealink::ConferenceDescription::Entry::Purpose::AUDIO_VIDEO:
      out = DescUriPurpose::kAudioVideo;
      break;
    case yealink::ConferenceDescription::Entry::Purpose::APPLICATION_SHARING:
      out = DescUriPurpose::kApplicationSharing;
      break;
    case yealink::ConferenceDescription::Entry::Purpose::CHAT:
      out = DescUriPurpose::kChat;
      break;
    case yealink::ConferenceDescription::Entry::Purpose::COOPSHARE:
      out = DescUriPurpose::kCoopShare;
      break;
    default:
      out = DescUriPurpose::kInvalid;
      break;
  }

  return true;
}
bool StructTraits<DescConfUriInfo>::From(
    DescConfUriInfo& out,
    const yealink::ConferenceDescription::Entry& val) {
  ConvertFrom(out.uri, val.uri);
  ConvertFrom(out.display_text, val.displayText);
  ConvertFrom(out.purpose, val.purpose);

  return true;
}

bool StructTraits<DescOrganizerInfo>::From(
    DescOrganizerInfo& out,
    const yealink::ConferenceDescription::OrganizerInfo& val) {
  ConvertFrom(out.display_text, val.displayText);
  ConvertFrom(out.uid, val.uid);
  ConvertFrom(out.username, val.username);
  ConvertFrom(out.realm, val.realm);
  ConvertFrom(out.phone, val.phone);
  ConvertFrom(out.domain, val.domain);

  return true;
}

bool StructTraits<DescConferenceType>::From(
    DescConferenceType& out,
    const yealink::ConferenceDescription::ConferenceType& val) {
  switch (val) {
    case yealink::ConferenceDescription::ConferenceType::VGCM:
      out = DescConferenceType::kVGCM;
      break;
    case yealink::ConferenceDescription::ConferenceType::VGCP:
      out = DescConferenceType::kVGCP;
      break;
    case yealink::ConferenceDescription::ConferenceType::VMN:
      out = DescConferenceType::kVMN;
      break;
    case yealink::ConferenceDescription::ConferenceType::VSC:
      out = DescConferenceType::kVSC;
      break;
    case yealink::ConferenceDescription::ConferenceType::VSCA:
      out = DescConferenceType::kVSCA;
      break;
    default:
      out = DescConferenceType::kInvalid;
      break;
  }

  return true;
}
bool StructTraits<DescNumberType>::From(
    DescNumberType& out,
    const yealink::ConferenceDescription::ConferenceNumberType& val) {
  switch (val) {
    case yealink::ConferenceDescription::ConferenceNumberType::MEET_NOW:
      out = DescNumberType::kMeetNow;
      break;
    case yealink::ConferenceDescription::ConferenceNumberType::RECURRENCE:
      out = DescNumberType::kRecurrence;
      break;
    case yealink::ConferenceDescription::ConferenceNumberType::VMR:
      out = DescNumberType::kVMR;
      break;
    default:
      out = DescNumberType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<DescAdmissionPolicy>::From(
    DescAdmissionPolicy& out,
    const yealink::ConferenceDescription::AdmissionPolicy& val) {
  switch (val) {
    case yealink::ConferenceDescription::AdmissionPolicy::CLOSED_AUTHENTICATED:
      out = DescAdmissionPolicy::kClosedAuthenticated;
      break;
    case yealink::ConferenceDescription::AdmissionPolicy::OPEN_AUTHENTICATED:
      out = DescAdmissionPolicy::KOpenAuthenticated;
      break;
    case yealink::ConferenceDescription::AdmissionPolicy::ANONYMOUS:
      out = DescAdmissionPolicy::kAnonumous;
      break;
    default:
      out = DescAdmissionPolicy::kInvalid;
      break;
  }

  return true;
}
bool StructTraits<DescAttendeeByPass>::From(
    DescAttendeeByPass& out,
    const yealink::ConferenceDescription::AttendeeByPass& val) {
  switch (val) {
    case yealink::ConferenceDescription::AttendeeByPass::ATTENDEE_BY_PASS_TRUE:
      out = DescAttendeeByPass::kByPassTrue;
      break;
    case yealink::ConferenceDescription::AttendeeByPass::ATTENDEE_BY_PASS_FALSE:
      out = DescAttendeeByPass::KByPassFalse;
      break;
    default:
      out = DescAttendeeByPass::kInvalid;
      break;
  }

  return true;
}
bool StructTraits<DescAutoPromote>::From(
    DescAutoPromote& out,
    const yealink::ConferenceDescription::AutoPromote& val) {
  switch (val) {
    case yealink::ConferenceDescription::AutoPromote::NONE:
      out = DescAutoPromote::kNone;
      break;
    case yealink::ConferenceDescription::AutoPromote::EVERYONE:
      out = DescAutoPromote::kEveryOne;
      break;
    case yealink::ConferenceDescription::AutoPromote::COMPANY:
      out = DescAutoPromote::kCompany;
      break;
    default:
      out = DescAutoPromote::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<DescRecordType>::From(
    DescRecordType& out,
    const yealink::ConferenceDescription::RecordServerType& val) {
  switch (val) {
    case yealink::ConferenceDescription::RecordServerType::YL_RECORD:
      out = DescRecordType::kYealinkRecord;
      break;
    case yealink::ConferenceDescription::RecordServerType::THIRD_PARTY:
      out = DescRecordType::kThirdParty;
      break;
    default:
      out = DescRecordType::kInvalid;
      break;
  }

  return true;
}
bool StructTraits<DescRecordPrivilege>::From(
    DescRecordPrivilege& out,
    const yealink::ConferenceDescription::RecordPrivilege& val) {
  switch (val) {
    case yealink::ConferenceDescription::RecordPrivilege::ORGANIZER:
      out = DescRecordPrivilege::kOrganizer;
      break;
    case yealink::ConferenceDescription::RecordPrivilege::PRESENTER:
      out = DescRecordPrivilege::kPresenter;
      break;
    case yealink::ConferenceDescription::RecordPrivilege::ATTENDEE:
      out = DescRecordPrivilege::kAttendee;
      break;
    default:
      out = DescRecordPrivilege::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<DescInfo>::From(DescInfo& out,
                                  const yealink::ConferenceDescription& val) {
  ConvertFrom(out.subject, val.subject);
  ConvertFrom(out.start_time, val.startTime);
  ConvertFrom(out.banner, val.banner);
  ConvertFrom(out.default_rtmp, val.defaultRtmp);
  ConvertFrom(out.profile, val.profile);
  ConvertFrom(out.record_id, val.recordId);
  ConvertFrom(out.conf_uris, val.confUris);
  ConvertFrom(out.conference_id, val.conferenceId);
  ConvertFrom(out.conference_number, val.conferenceNumber);
  ConvertFrom(out.conference_type, val.conferenceType);
  ConvertFrom(out.conference_number_type, val.conferenceNumberType);
  ConvertFrom(out.book_start_time, val.bookStartTime);
  ConvertFrom(out.book_expiry_time, val.bookExpiryTime);
  ConvertFrom(out.presenter_pin, val.presenterPin);
  ConvertFrom(out.attendee_pin, val.attendeePin);
  ConvertFrom(out.admission_policy, val.admissionPolicy);
  ConvertFrom(out.lobby_capable, val.lobbyCapable);
  ConvertFrom(out.attendee_by_pass, val.attendeeByPass);
  ConvertFrom(out.auto_promote, val.autoPromote);
  ConvertFrom(out.server_mode, val.serverMode);
  ConvertFrom(out.interactive_broadcast_enabled,
              val.interactiveBroadcastEnabled);
  ConvertFrom(out.enterprise_id, val.enterpriseId);
  ConvertFrom(out.video_enable, val.videoEnable);
  ConvertFrom(out.ipcall_enable, val.ipcallEnable);
  ConvertFrom(out.webrtc_enable, val.webrtcEnable);
  ConvertFrom(out.record_server_type, val.recordServerType);
  ConvertFrom(out.record_privilege, val.recordPrivilege);
  ConvertFrom(out.conf_info_url, val.confInfoUrl);

  return true;
}

// state

// users
bool StructTraits<RequesrResult>::From(RequesrResult& out,
                                       const yealink::ConferenceResult& val) {
  switch (val) {
    case yealink::ConferenceResult::CONFERENCE_SUCCESS:
      out = RequesrResult::kSuccess;
      break;
    case yealink::ConferenceResult::CONFERENCE_SIP_FAILURE:
      out = RequesrResult::kSipFailure;
      break;
    case yealink::ConferenceResult::CONFERENCE_INVALID:
      out = RequesrResult::kInvalid;
      break;
    case yealink::ConferenceResult::CONFERENCE_INVALID_PARAMS:
      out = RequesrResult::kInvalidParam;
      break;
    default:
      out = RequesrResult::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<ResponseInfo>::From(ResponseInfo& out,
                                      const yealink::RequestResult& val) {
  ConvertFrom(out.request_id, val.requestId);
  ConvertFrom(out.result, val.requestResult);

  return true;
}

bool StructTraits<ImResponseInfo>::From(ImResponseInfo& out,
                                        const yealink::RoomImResult& val) {
  ConvertFrom(out.biz_code, val.bizCode);
  ConvertFrom(out.entity, val.imEntity);
  ConvertFrom(out.timestamp, val.imTimestamp);

  return true;
}

bool StructTraits<ImMessageInfo>::From(ImMessageInfo& out,
                                       const yealink::RoomImMessage& val) {
  ConvertFrom(out.is_private, val.isPrivate);
  ConvertFrom(out.text, val.imContext);
  ConvertFrom(out.timestamp, val.imTimestamp);
  ConvertFrom(out.version, val.imVersion);
  ConvertFrom(out.sender_entity, val.senderEntity);
  ConvertFrom(out.sender_display_text, val.senderDisplayText);

  return true;
}

bool StructTraits<ImMessageList>::From(ImMessageList& out,
                                       const yealink::RoomImMessageList& val) {
  ConvertFrom(out.biz_code, val.bizCode);
  ConvertFrom(out.messages, val.imInfos);

  return true;
}

bool StructTraits<HttpResponseInfo>::From(HttpResponseInfo& out,
                                          const yealink::RoomHttpResult& val) {
  ConvertFrom(out.biz_code, val.bizCode);
  ConvertFrom(out.result, val.result);

  return true;
}

bool StructTraits<UserProtocolType>::From(
    UserProtocolType& out,
    const yealink::MemberInfo::Protocol& val) {
  switch (val) {
    case yealink::MemberInfo::Protocol::H323:
      out = UserProtocolType::kH323;
      break;
    case yealink::MemberInfo::Protocol::SIP:
      out = UserProtocolType::kSIP;
      break;
    case yealink::MemberInfo::Protocol::RTMP:
      out = UserProtocolType::kRTMP;
      break;
    default:
      out = UserProtocolType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<UserPermissionType>::From(
    UserPermissionType& out,
    const yealink::MemberInfo::Roles::PermissionRole& val) {
  switch (val) {
    case yealink::MemberInfo::Roles::PermissionRole::PERMISSION_ATTENDEE:
      out = UserPermissionType::kAttendee;
      break;
    case yealink::MemberInfo::Roles::PermissionRole::PERMISSION_CAST_VIEWER:
      out = UserPermissionType::kCastviewer;
      break;
    case yealink::MemberInfo::Roles::PermissionRole::PERMISSION_ORGANIZER:
      out = UserPermissionType::kOrganizer;
      break;
    case yealink::MemberInfo::Roles::PermissionRole::PERMISSION_PRESENTER:
      out = UserPermissionType::kPresenter;
      break;
    default:
      out = UserPermissionType::kInvalid;
      break;
  }

  return true;
}
bool StructTraits<UserDemoStateType>::From(
    UserDemoStateType& out,
    const yealink::MemberInfo::Roles::DemoStateRole& val) {
  switch (val) {
    case yealink::MemberInfo::Roles::DemoStateRole::DEMOSTATE_AUDIENCE:
      out = UserDemoStateType::kAudience;
      break;
    case yealink::MemberInfo::Roles::DemoStateRole::DEMOSTATE_DEMONSTRATOR:
      out = UserDemoStateType::kDemonstrator;
      break;
    default:
      out = UserDemoStateType::kInvalid;
      break;
  }

  return true;
}
bool StructTraits<PresenterDemoStateType>::From(
    PresenterDemoStateType& out,
    const yealink::MemberInfo::Roles::PresenterDemoStateRole& val) {
  switch (val) {
    case yealink::MemberInfo::Roles::PresenterDemoStateRole::
        PRESENTER_DEMONSTRATOR:
      out = PresenterDemoStateType::kDemonstrator;
      break;
    case yealink::MemberInfo::Roles::PresenterDemoStateRole::PRESENTER_AUDIENCE:
      out = PresenterDemoStateType::kAudience;
      break;
    default:
      out = PresenterDemoStateType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<UserRolesInfo>::From(UserRolesInfo& out,
                                       const yealink::MemberInfo::Roles& val) {
  ConvertFrom(out.permission, val.permissionRole);
  ConvertFrom(out.demostate, val.demoStateRole);
  ConvertFrom(out.presenter_demostate, val.presenterDemoStateRole);

  return true;
}

bool StructTraits<UserEndpointSeesionType>::From(
    UserEndpointSeesionType& out,
    const yealink::MemberInfo::Endpoint::SessionType& val) {
  switch (val) {
    case yealink::MemberInfo::Endpoint::SessionType::APPLICATION_SHARING:
      out = UserEndpointSeesionType::kApplicationSharing;
      break;
    case yealink::MemberInfo::Endpoint::SessionType::AUDIO_VIDEO:
      out = UserEndpointSeesionType::kAudioVideo;
      break;
    case yealink::MemberInfo::Endpoint::SessionType::CHAT:
      out = UserEndpointSeesionType::kChat;
      break;
    case yealink::MemberInfo::Endpoint::SessionType::COOPSHARE:
      out = UserEndpointSeesionType::kCoopshare;
      break;
    case yealink::MemberInfo::Endpoint::SessionType::FOCUS:
      out = UserEndpointSeesionType::kFocus;
      break;
    default:
      out = UserEndpointSeesionType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<UserEndpointStatusType>::From(
    UserEndpointStatusType& out,
    const yealink::MemberInfo::Endpoint::Status& val) {
  switch (val) {
    case yealink::MemberInfo::Endpoint::Status::CONNECTED:
      out = UserEndpointStatusType::kConnected;
      break;
    case yealink::MemberInfo::Endpoint::Status::DIALING_IN:
      out = UserEndpointStatusType::kDialingIn;
      break;
    case yealink::MemberInfo::Endpoint::Status::DIALING_OUT:
      out = UserEndpointStatusType::kDialingOut;
      break;
    case yealink::MemberInfo::Endpoint::Status::DISCONNECTED:
      out = UserEndpointStatusType::kDisconnected;
      break;
    case yealink::MemberInfo::Endpoint::Status::ON_HOLD:
      out = UserEndpointStatusType::kOnHold;
      break;
    default:
      out = UserEndpointStatusType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<UserJoinMethod>::From(
    UserJoinMethod& out,
    const yealink::MemberInfo::Endpoint::JoiningMethod& val) {
  switch (val) {
    case yealink::MemberInfo::Endpoint::JoiningMethod::DIALED_IN:
      out = UserJoinMethod::kDialedIn;
      break;
    case yealink::MemberInfo::Endpoint::JoiningMethod::DIALED_OUT:
      out = UserJoinMethod::kDialedOut;
      break;
    default:
      out = UserJoinMethod::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<UserMediaType>::From(
    UserMediaType& out,
    const yealink::MemberInfo::Endpoint::Media::Type& val) {
  switch (val) {
    case yealink::MemberInfo::Endpoint::Media::Type::APPLICATION:
      out = UserMediaType::kApplication;
      break;
    case yealink::MemberInfo::Endpoint::Media::Type::AUDIO:
      out = UserMediaType::kAudio;
      break;
    case yealink::MemberInfo::Endpoint::Media::Type::VIDEO:
      out = UserMediaType::kVideo;
      break;
    default:
      out = UserMediaType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<UserMediaLabelType>::From(
    UserMediaLabelType& out,
    const yealink::MemberInfo::Endpoint::Media::Label& val) {
  switch (val) {
    case yealink::MemberInfo::Endpoint::Media::Label::APPLICATIONSHARING:
      out = UserMediaLabelType::kApplication;
      break;
    case yealink::MemberInfo::Endpoint::Media::Label::FECC:
      out = UserMediaLabelType::kFecc;
      break;
    case yealink::MemberInfo::Endpoint::Media::Label::MAIN_AUDIO:
      out = UserMediaLabelType::kMainAudio;
      break;
    case yealink::MemberInfo::Endpoint::Media::Label::MAIN_VIDEO:
      out = UserMediaLabelType::kMainVideo;
      break;
    default:
      out = UserMediaLabelType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<UserMediaDirectionType>::From(
    UserMediaDirectionType& out,
    const yealink::MemberInfo::Endpoint::Media::Status& val) {
  switch (val) {
    case yealink::MemberInfo::Endpoint::Media::Status::INACTIVE:
      out = UserMediaDirectionType::kInactive;
      break;
    case yealink::MemberInfo::Endpoint::Media::Status::RECV_ONLY:
      out = UserMediaDirectionType::kRecvOnly;
      break;
    case yealink::MemberInfo::Endpoint::Media::Status::SEND_ONLY:
      out = UserMediaDirectionType::kSendOnly;
      break;
    case yealink::MemberInfo::Endpoint::Media::Status::SEND_RECV:
      out = UserMediaDirectionType::kSendRecv;
      break;
    default:
      out = UserMediaDirectionType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<UserMediafilterType>::From(
    UserMediafilterType& out,
    const yealink::MemberInfo::Endpoint::Media::MediaFilter& val) {
  switch (val) {
    case yealink::MemberInfo::Endpoint::Media::MediaFilter::BLOCK:
      out = UserMediafilterType::kBlock;
      break;
    case yealink::MemberInfo::Endpoint::Media::MediaFilter::UNBLOCK:
      out = UserMediafilterType::kUnblock;
      break;
    case yealink::MemberInfo::Endpoint::Media::MediaFilter::UNBLOCKING:
      out = UserMediafilterType::kUnblocking;
      break;
    default:
      out = UserMediafilterType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<UserMediaBlockByType>::From(
    UserMediaBlockByType& out,
    const yealink::MemberInfo::Endpoint::Media::BlockBy& val) {
  switch (val) {
    case yealink::MemberInfo::Endpoint::Media::BlockBy::CLIENT:
      out = UserMediaBlockByType::kClient;
      break;
    case yealink::MemberInfo::Endpoint::Media::BlockBy::SERVER:
      out = UserMediaBlockByType::kServer;
      break;
    case yealink::MemberInfo::Endpoint::Media::BlockBy::NONE:
      out = UserMediaBlockByType::kNone;
      break;
    default:
      out = UserMediaBlockByType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<UserMediaInfo>::From(
    UserMediaInfo& out,
    const yealink::MemberInfo::Endpoint::Media& val) {
  ConvertFrom(out.id, val.id);
  ConvertFrom(out.type, val.type);
  ConvertFrom(out.label, val.label);
  ConvertFrom(out.status, val.status);
  ConvertFrom(out.media_egress_block_by, val.mediaEgressBlockBy);
  ConvertFrom(out.media_egress_filter, val.mediaEgressFilter);
  ConvertFrom(out.media_ingress_block_by, val.mediaIngressBlockBy);
  ConvertFrom(out.media_ingress_filter, val.mediaIngressFilter);

  return true;
}

bool StructTraits<UserMediaFilterInfo>::From(
    UserMediaFilterInfo& out,
    const yealink::MemberInfo::Endpoint::Media& val) {
  ConvertFrom(out.media_egress_block_by, val.mediaEgressBlockBy);
  ConvertFrom(out.media_egress_filter, val.mediaEgressFilter);
  ConvertFrom(out.media_ingress_block_by, val.mediaIngressBlockBy);
  ConvertFrom(out.media_ingress_filter, val.mediaIngressFilter);

  return true;
}

bool StructTraits<UserEndpointInfo>::From(
    UserEndpointInfo& out,
    const yealink::MemberInfo::Endpoint& val) {
  ConvertFrom(out.entity, val.entity);
  ConvertFrom(out.session_type, val.sessionType);
  ConvertFrom(out.status, val.status);
  ConvertFrom(out.joining_method, val.joiningMethod);
  ConvertFrom(out.when, val.joiningInfo);
  ConvertFrom(out.mcu_call_id, val.mcuCallId);
  ConvertFrom(out.media, val.mediaList);

  return true;
}

bool StructTraits<UserInfo>::From(UserInfo& out,
                                  const yealink::MemberInfo& val) {
  ConvertFrom(out.entity, val.entity);
  ConvertFrom(out.display_text, val.displayText);
  ConvertFrom(out.display_number, val.displayNumber);
  ConvertFrom(out.display_text_pinyin, val.displayTextPinyin);
  ConvertFrom(out.uid, val.uid);
  ConvertFrom(out.protocol, val.protocol);
  ConvertFrom(out.medium_server_type, val.mediumServerType);
  ConvertFrom(out.ip, val.ip);
  ConvertFrom(out.phone, val.phone);
  ConvertFrom(out.request_uri, val.requestUri);
  ConvertFrom(out.user_agent, val.userAgent);
  ConvertFrom(out.roles, val.roles);
  ConvertFrom(out.endpoint, val.endpointList);

  return true;
}

bool StructTraits<UserMediaDataInfo>::From(
    UserMediaDataInfo& out,
    const yealink::UserMediaDetail& val) {
  ConvertFrom(out.enable, val.enable);
  ConvertFrom(out.ip, val.ip);
  ConvertFrom(out.codec, val.codec);
  ConvertFrom(out.width, val.width);
  ConvertFrom(out.height, val.height);
  ConvertFrom(out.fr, val.fr);
  ConvertFrom(out.sample_rate, val.sampleRate);
  ConvertFrom(out.bandwidth, val.bandwidth);
  ConvertFrom(out.bit_rate, val.bitRate);
  ConvertFrom(out.loss_rate, val.lossRate);
  ConvertFrom(out.packet_lost, val.packetLost);
  ConvertFrom(out.jitter, val.jitter);
  ConvertFrom(out.rtt, val.rtt);

  return true;
}

bool StructTraits<UserStatisticsInfo>::From(UserStatisticsInfo& out,
                                            const yealink::UserMediaInfo& val) {
  ConvertFrom(out.media_id, val.mediaId);
  ConvertFrom(out.label, val.label);
  ConvertFrom(out.send, val.send);
  ConvertFrom(out.recv, val.recv);
  ConvertFrom(out.type, val.type);

  return true;
}

bool StructTraits<RecordStatusType>::From(
    RecordStatusType& out,
    const yealink::RoomRecordStatus& val) {
  switch (val) {
    case yealink::RoomRecordStatus::ROOM_RECORD_STATUS_PAUSE:
      out = RecordStatusType::kPause;
      break;
    case yealink::RoomRecordStatus::ROOM_RECORD_STATUS_PAUSING:
      out = RecordStatusType::kPausing;
      break;
    case yealink::RoomRecordStatus::ROOM_RECORD_STATUS_RESUME:
      out = RecordStatusType::kResume;
      break;
    case yealink::RoomRecordStatus::ROOM_RECORD_STATUS_RESUMING:
      out = RecordStatusType::kResuming;
      break;
    case yealink::RoomRecordStatus::ROOM_RECORD_STATUS_START:
      out = RecordStatusType::kStart;
      break;
    case yealink::RoomRecordStatus::ROOM_RECORD_STATUS_STARTING:
      out = RecordStatusType::kStarting;
      break;
    case yealink::RoomRecordStatus::ROOM_RECORD_STATUS_STOP:
      out = RecordStatusType::kStop;
      break;
    case yealink::RoomRecordStatus::ROOM_RECORD_STATUS_STOPPING:
      out = RecordStatusType::kStopping;
      break;
    default:
      out = RecordStatusType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<RecordUserInfo>::From(
    RecordUserInfo& out,
    const yealink::RoomRecordUserInfo& val) {
  ConvertFrom(out.record_last_start_time, val.recordLastStartTime);
  ConvertFrom(out.record_last_stop_duration, val.recordLastStopDuration);
  ConvertFrom(out.record_status, val.recordStatus);

  return true;
}

bool StructTraits<RecordUsers>::From(RecordUsers& out,
                                     const yealink::RoomRecordUsers& val) {
  ConvertFrom(out.user, val.user);
  ConvertFrom(out.biz_code, val.bizCode);

  return true;
}

bool StructTraits<RtmpStatusType>::From(RtmpStatusType& out,
                                        const yealink::RoomRtmpStatus& val) {
  switch (val) {
    case yealink::RoomRtmpStatus::ROOM_RTMP_STATUS_PAUSE:
      out = RtmpStatusType::kPause;
      break;
    case yealink::RoomRtmpStatus::ROOM_RTMP_STATUS_PAUSING:
      out = RtmpStatusType::kPausing;
      break;
    case yealink::RoomRtmpStatus::ROOM_RTMP_STATUS_RESUME:
      out = RtmpStatusType::kResume;
      break;
    case yealink::RoomRtmpStatus::ROOM_RTMP_STATUS_RESUMING:
      out = RtmpStatusType::kResuming;
      break;
    case yealink::RoomRtmpStatus::ROOM_RTMP_STATUS_START:
      out = RtmpStatusType::kStart;
      break;
    case yealink::RoomRtmpStatus::ROOM_RTMP_STATUS_STARTING:
      out = RtmpStatusType::kStarting;
      break;
    case yealink::RoomRtmpStatus::ROOM_RTMP_STATUS_STOP:
      out = RtmpStatusType::kStop;
      break;
    case yealink::RoomRtmpStatus::ROOM_RTMP_STATUS_STOPPING:
      out = RtmpStatusType::kStopping;
      break;
    default:
      out = RtmpStatusType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<RtmpUserInfo>::From(RtmpUserInfo& out,
                                      const yealink::RoomRtmpUserInfo& val) {
  ConvertFrom(out.entity, val.entity);
  ConvertFrom(out.is_default, val.isDefault);
  ConvertFrom(out.rtmp_last_start_time, val.rtmpLastStartTime);
  ConvertFrom(out.rtmp_last_stop_duration, val.rtmpLastStopDuration);
  ConvertFrom(out.rtmp_status, val.rtmpStatus);

  return true;
}

bool StructTraits<RtmpInfo>::From(RtmpInfo& out,
                                  const yealink::RoomRtmpState& val) {
  ConvertFrom(out.enable, val.rtmpEnable);
  ConvertFrom(out.biz_code, val.bizCode);
  ConvertFrom(out.users, val.users);

  return true;
}

// view
bool StructTraits<ViewSpeakMode>::From(
    ViewSpeakMode& out,
    const yealink::ConferenceViewSpeakMode& val) {
  switch (val) {
    case yealink::ConferenceViewSpeakMode::CONFERENCE_VIEW_SPEAK_MODE_FREE:
      out = ViewSpeakMode::kFree;
      break;
    case yealink::ConferenceViewSpeakMode::CONFERENCE_VIEW_SPEAK_MODE_HAND_UP:
      out = ViewSpeakMode::kHandUp;
      break;
    default:
      out = ViewSpeakMode::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<ViewLayoutType>::From(
    ViewLayoutType& out,
    const yealink::ConferenceView::EntityState::VideoLayout& val) {
  switch (val) {
    case yealink::ConferenceView::EntityState::VideoLayout::
        VIDEO_LAYOUT_EQUALITY:
      out = ViewLayoutType::kEquality;
      break;
    case yealink::ConferenceView::EntityState::VideoLayout::
        VIDEO_LAYOUT_PRESENTATION:
      out = ViewLayoutType::kPresentation;
      break;
    case yealink::ConferenceView::EntityState::VideoLayout::
        VIDEO_LAYOUT_SPEECH_EXCITATION:
      out = ViewLayoutType::kSpeechExcitation;
      break;
    case yealink::ConferenceView::EntityState::VideoLayout::
        VIDEO_LAYOUT_EXCLUSIVE:
      out = ViewLayoutType::kExclusive;
      break;
    default:
      out = ViewLayoutType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<ViewPresenterLayoutType>::From(
    ViewPresenterLayoutType& out,
    const yealink::ConferenceView::EntityState::VideoPresenterLayout& val) {
  switch (val) {
    case yealink::ConferenceView::EntityState::VideoPresenterLayout::
        VIDEO_PRESENTER_LAYOUT_EQUALITY:
      out = ViewPresenterLayoutType::kEquality;
      break;
    case yealink::ConferenceView::EntityState::VideoPresenterLayout::
        VIDEO_PRESENTER_LAYOUT_SPEECH_EXCITATION:
      out = ViewPresenterLayoutType::kSpeechExcitation;
      break;
    case yealink::ConferenceView::EntityState::VideoPresenterLayout::
        VIDEO_PRESENTER_LAYOUT_EXCLUSIVE:
      out = ViewPresenterLayoutType::kExclusive;
      break;
    default:
      out = ViewPresenterLayoutType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<GetLayoutInfo>::From(
    GetLayoutInfo& out,
    const yealink::ConferenceView::EntityState& val) {
  ConvertFrom(out.speak_mode, val.speakMode);
  ConvertFrom(out.video_layout, val.videoLayout);
  ConvertFrom(out.video_max_view, val.videoMaxView);
  ConvertFrom(out.video_presenter_layout, val.videoPresenterLayout);
  ConvertFrom(out.video_presenter_max_view, val.videoPresenterMaxView);
  ConvertFrom(out.video_round_number, val.videoRoundNumber);
  ConvertFrom(out.video_round_interval, val.videoRoundInterval);
  ConvertFrom(out.video_speech_ex_sensitivity, val.videoSpeechExSensitivity);
  ConvertFrom(out.video_round_enable, val.videoRoundEnabled);
  ConvertFrom(out.video_big_round, val.videoBigRound);
  ConvertFrom(out.video_speech_ex_enabled, val.videoSpeechExEnabled);
  ConvertFrom(out.video_data_mix_enabled, val.videoDataMixEnabled);
  ConvertFrom(out.hide_osd_sitename, val.hideOsdSitename);
  ConvertFrom(out.hide_osd_sitestatus, val.hideOsdSitestatus);

  return true;
}

bool StructTraits<ViewFilterRoleType>::From(
    ViewFilterRoleType& out,
    const yealink::ConferenceView::EntityState::MediaFiltersRules::
        InitialFilter::Role& val) {
  switch (val) {
    case yealink::ConferenceView::EntityState::MediaFiltersRules::
        InitialFilter::Role::ATTENDEE:
      out = ViewFilterRoleType::kAttendee;
      break;
    case yealink::ConferenceView::EntityState::MediaFiltersRules::
        InitialFilter::Role::DEFAULT:
      out = ViewFilterRoleType::kDefault;
      break;
    default:
      out = ViewFilterRoleType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<ViewFilterType>::From(
    ViewFilterType& out,
    const yealink::ConferenceView::EntityState::MediaFiltersRules::
        InitialFilter::Filter& val) {
  switch (val) {
    case yealink::ConferenceView::EntityState::MediaFiltersRules::
        InitialFilter::Filter::BLOCK:
      out = ViewFilterType::kBlock;
      break;
    case yealink::ConferenceView::EntityState::MediaFiltersRules::
        InitialFilter::Filter::UNBLOCK:
      out = ViewFilterType::kUnBlock;
      break;
    default:
      out = ViewFilterType::kInvalid;
      break;
  }

  return true;
}

bool StructTraits<ViewFilterRuleInfo>::From(
    ViewFilterRuleInfo& out,
    const yealink::ConferenceView::EntityState::MediaFiltersRules::
        InitialFilter& val) {
  ConvertFrom(out.role, val.role);
  ConvertFrom(out.egress, val.egressFilter);
  ConvertFrom(out.ingress, val.ingressFilter);

  return true;
}

bool StructTraits<StatsAudioCodecType>::From(StatsAudioCodecType& out,
                                             const yealink::AudioCodecs& val) {
  switch (val) {
    case yealink::AudioCodecs::AUDIO_CODEC_AACLC:
      out = StatsAudioCodecType::kAACLC;
      break;
    case yealink::AudioCodecs::AUDIO_CODEC_ARES:
      out = StatsAudioCodecType::kARES;
      break;
    case yealink::AudioCodecs::AUDIO_CODEC_G7221:
      out = StatsAudioCodecType::kG7221;
      break;
    case yealink::AudioCodecs::AUDIO_CODEC_G7221C:
      out = StatsAudioCodecType::kG72221C;
      break;
    case yealink::AudioCodecs::AUDIO_CODEC_G722:
      out = StatsAudioCodecType::kG722;
      break;
    case yealink::AudioCodecs::AUDIO_CODEC_G729:
      out = StatsAudioCodecType::kG729;
      break;
    case yealink::AudioCodecs::AUDIO_CODEC_OPUS:
      out = StatsAudioCodecType::kOPUS;
      break;
    case yealink::AudioCodecs::AUDIO_CODEC_PCMA:
      out = StatsAudioCodecType::kPCMA;
      break;
    case yealink::AudioCodecs::AUDIO_CODEC_PCMU:
      out = StatsAudioCodecType::kPCMU;
      break;
    default:
      out = StatsAudioCodecType::kNone;
      break;
  }

  return true;
}

bool StructTraits<StatsVideoCodecType>::From(StatsVideoCodecType& out,
                                             const yealink::VideoCodecs& val) {
  switch (val) {
    case yealink::VideoCodecs::VIDEO_CODEC_H264:
      out = StatsVideoCodecType::kH264;
      break;
    case yealink::VideoCodecs::VIDEO_CODEC_H263:
      out = StatsVideoCodecType::kH263;
      break;
    default:
      out = StatsVideoCodecType::kNone;
      break;
  }

  return true;
}

bool StructTraits<StatsVideoProfileType>::From(
    StatsVideoProfileType& out,
    const yealink::VideoCodecProfile& val) {
  switch (val) {
    case yealink::VideoCodecProfile::VIDEO_CODEC_PROFILE_BASE:
      out = StatsVideoProfileType::kBase;
      break;
    case yealink::VideoCodecProfile::VIDEO_CODEC_PROFILE_HIGH:
      out = StatsVideoProfileType::kHigh;
      break;
    case yealink::VideoCodecProfile::VIDEO_CODEC_PROFILE_MAIN:
      out = StatsVideoProfileType::kMain;
      break;
    case yealink::VideoCodecProfile::VIDEO_CODEC_PROFILE_MAX:
      out = StatsVideoProfileType::kMax;
      break;
    default:
      out = StatsVideoProfileType::kNone;
      break;
  }

  return true;
}

bool StructTraits<VideoStatsInfo>::From(VideoStatsInfo& out,
                                        const yealink::VideoChannelStats& val) {
  ConvertFrom(out.codec, val.codec);
  ConvertFrom(out.profile, val.profile);
  ConvertFrom(out.width, val.width);
  ConvertFrom(out.height, val.height);
  ConvertFrom(out.frame_rate, val.frameRate);
  ConvertFrom(out.bit_rate, val.bitRate);
  ConvertFrom(out.loss_rate, val.lossRate);
  ConvertFrom(out.total_loss_packets, val.totalLossPackets);
  ConvertFrom(out.jitter, val.jitter);
  ConvertFrom(out.rtt, val.rtt);

  return true;
}

bool StructTraits<RTCVideoStats>::From(RTCVideoStats& out,
                                       const yealink::VideoStreamStats& val) {
  ConvertFrom(out.inbound, val.stRecv);
  ConvertFrom(out.outbound, val.stSend);

  return true;
}

bool StructTraits<RTCAudioStats>::From(RTCAudioStats& out,
                                       const yealink::AudioStreamStats& val) {
  ConvertFrom(out.inbound.bitrate, val.bitrateR);
  ConvertFrom(out.inbound.codec, val.codecR);
  ConvertFrom(out.inbound.samplerate, val.samplerateR);
  ConvertFrom(out.inbound.loss_rate, val.lossRateR);
  ConvertFrom(out.inbound.total_lost_packets, val.totalLostPacketsR);
  ConvertFrom(out.inbound.jitter, val.jitterR);
  ConvertFrom(out.inbound.delay, val.delayR);

  ConvertFrom(out.outbound.bitrate, val.bitrateS);
  ConvertFrom(out.outbound.codec, val.codecS);
  ConvertFrom(out.outbound.samplerate, val.samplerateS);
  ConvertFrom(out.outbound.loss_rate, val.lossRateS);
  ConvertFrom(out.outbound.total_lost_packets, val.totalLostPacketsS);
  ConvertFrom(out.outbound.jitter, val.jitterS);
  ConvertFrom(out.outbound.delay, val.delayS);

  return true;
}

bool StructTraits<RTCStats>::From(RTCStats& out,
                                  const yealink::MediaStreamStats& val) {
  ConvertFrom(out.audio, val.stAudio);
  ConvertFrom(out.video, val.stVideo);
  return true;
}

bool StructTraits<PartyInviteInfos>::From(PartyInviteInfos& out,
                                          const yealink::PartyInviteInfo& val) {
  ConvertFrom(out.applicants, val.applicants);
  ConvertFrom(out.url, val.url);
  return true;
}

}  // namespace rtvc
