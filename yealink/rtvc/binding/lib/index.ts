import {
  Bootstrap,
  Connector,
  EnterpriseInfo,
  TurnServerInfo,
  AccountInfo,
  PrimaryAccountInfo,
  AuthenticateInfos,
  InviteInfo,
  SchedulerMetaInfo
} from './bootstrap';
import {
  UserAgent,
  AccountConfig,
} from './user-agent';
import {
  Call,
  CallSvcSubscribeType,
  CallConfig,
  CallMedia,
  CallLocalInfo,
  CallRemoteInfo,
  CallInfo,
  CallAudioStatsInfo,
  CallVideoStatsInfo,
  CallRTCVideoStats,
  CallRTCAudioStats,
  CallRTCStats,
  CallRTCStatsInfo,
  CallVideoSubscribe
} from './call';
import {
  Conference,
  CreateInfo,
  ConferenceChat,
  ConferenceChatMessage,
  ConferenceChatDialog,
  ConferenceDescription,
  ConferenceDescriptionBanner,
  ConferenceDescriptionRtmp,
  ConferenceDescriptionUriInfo,
  ConferenceDescriptionOrganizer,
  ConferenceDescriptionLockInfo,
  ConferenceRecord,
  ConferenceRecordUserInfo,
  ConferenceRecordInfo,
  ConferenceRtmp,
  ConferenceRtmpUserInfo,
  ConferenceRtmpInfo,
  ConferenceState,
  ConferenceUsers,
  ConferenceUser,
  ConferenceUserRoleInfo,
  ConferenceUserMediaInfo,
  ConferenceUserEndpointInfo,
  ConferenceUserFilterInfo,
  ConferenceView,
  ConferenceViewLayoutInfo,
  ConferenceViewFilterInfo
} from './conference'
import {
  Schedule,
  ScheduleItemProfile,
  ScheduleRecurrence,
  ScheduleRecurrenceDaily,
  ScheduleRecurrenceRange,
  ScheduleMemberRole,
  ScheduleMemberType,
  ScheduleRTMPLimitType,
  ScheduleMemberCreateType,
  ScheduleResolutionType,
  SchedulePromptType,
  ScheduleServiceAbility,
  ScheduleRecurrenceInfo,
  ScheduleDaylightStrategy,
  ScheduleTimeZoneRule,
  ScheduleTimeZone,
  ScheduleMember,
  ScheduleRoom,
  ScheduleRTMP,
  ScheduleItemDetail,
  ScheduleItem,
  ScheduleConfig,
  SchedulePlanMember,
  SchedulePlan,
  SchedulePlanConfig,
  ScheduleServiceStatus,
  ScheduleServiceResponse,
} from './schedule';
import {
  CloudContact,
  CloudContactConfig,
  ContactNodeType,
  ContactNode,
  ContactConfig
} from './contact';
import {
  DeviceType,
  Device,
  AudioManager,
  AudioOutputDevice,
  AudioInputDevice,
  AudioDevice,
  ImageFileDevice,
  VideoManager,
  VideoRotation,
  VideoLimitInfo,
  VideoInputDevice,
  VideoDevice
} from './media';
import {
  YTMS,
  TerminalInfo,
  AlarmInfo,
  PackageInfo,
  ConfigurationInfo,
  DownloadInfo,
  UploadLogInfo,
  NetCaptureInfo,
  NetCaptureStatus,
  EventInfo
} from './ytms';

declare const _default : {
  YTMS: YTMS;
  VideoManager: VideoManager;
  AudioManager: AudioManager;
  Contact: CloudContact;
  Schedule: Schedule;
  Conference: Conference;
  Call: Call;
  UserAgent: UserAgent;
  Bootstrap: Bootstrap;
}

export default _default;
