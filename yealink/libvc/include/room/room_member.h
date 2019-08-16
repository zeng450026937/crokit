/*
 * @file room_member.h
 * @date 2019-03-21
 * 
 * @brief 
 */

#ifndef __ROOM_MEMBER_H__
#define __ROOM_MEMBER_H__

#include "room/room_data.h"
#include "room/room_define.h"

namespace yealink
{
class ROOM_API RoomMember
{
    ROOM_COMPONENT_DECLARE(RoomMember)

public:
    friend class RoomMemberManager;
    /**
     * @brief 
     * @param data 
     * @return 
     */
    static RoomMember CreateMember(void* data);

public:
    /* getter interface */
    /**
     * @brief 
     * @return 
     */
    MemberInfo GetMemberInfo() const;
    /**
     * @brief 
     * @return 
     */
    int64_t GetAnswerTime() const;
    /**
     * @brief 
     * @return 
     */
    SStringA GetUserEntity() const;
    /**
     * @brief get request uri
     * @return request uri(string)
     */
    SStringA GetRequestUri() const;
    /**
     * @brief 
     * @return 
     */
    SStringA GetRequestUuid() const;
    /**
     * @brief 
     * @return 
     */
    bool IsCurrentUser() const;
    /**
     * @brief 
     * @return 
     */
    bool IsHoldOn() const;
    /**
     * @brief 
     * @return 
     */
    bool IsSharing() const;
    /**
     * @brief 
     * @return 
     */
    bool IsFocus() const;
    /**
     * @brief 
     * @return 
     */
    bool IsDialingOut() const;
    /**
     * @brief 
     * @return 
     */
    bool IsDialingIn() const;
    /**
     * @brief 
     * @return 
     */
    MemberInfo::Roles::PermissionRole GetPermissionRole() const;
    /**
     * @brief 
     * @return 
     */
    MemberInfo::Roles::DemoStateRole GetDemoStateRole() const;
    /**
     * @brief 
     * @return 
     */
    MemberInfo::Roles::PresenterDemoStateRole GetPresenterDemoStateRole() const;
    /**
     * @brief 
     * @return 
     */
    MemberInfo::Endpoint::Media::MediaFilter GetAudioIngressFilter() const;
    /**
     * @brief 
     * @return 
     */
    MemberInfo::Endpoint::Media::MediaFilter GetVideoIngressFilter() const;
    /**
     * @brief 
     * @return 
     */
    MemberInfo::Endpoint::Media::MediaFilter GetAudioEgressFilter() const;
    /**
     * @brief 
     * @return 
     */
    MemberInfo::Endpoint::Media::MediaFilter GetVideoEgressFilter() const;
    /**
     * @brief 
     * @return 
     */
    MemberInfo::Endpoint::Media::BlockBy GetAudioIngressBlockBy() const;
    /**
     * @brief 
     * @return 
     */
    RequestResult GetUserCallStats() const;
    /**
     * @brief 
     * @return 
     */
    int64_t GetLobbyTimestamp() const;
    /**
     * @brief 
     * @return 
     */
    int64_t GetHandUpTimestamp() const;

public:
    /* setter interface */
    /**
     * @brief 
     * @param isClose 
     * @return 
     */
    RequestResult SetAudioState(bool isClose);
    /**
     * @brief 
     * @param isClose 
     * @return 
     */
    RequestResult SetVideoState(bool isClose);
    /**
     * @brief 
     * @param isClose 
     * @return 
     */
    RequestResult SetAudioEgressState(bool isClose);
    /**
     * @brief 
     * @return 
     */
    RequestResult KickOut();
    /**
     * @brief 
     * @return 
     */
    RequestResult Hold();
    /**
     * @brief 
     * @param granted 
     * @return 
     */
    RequestResult SetAccess(bool granted);
    /**
     * @brief 
     * @param demoState 
     * @return 
     */
    RequestResult SetDemonstrator(bool demoState);
    /**
     * @brief 
     * @param isFocus 
     * @return 
     */
    RequestResult SetFocus(bool isFocus);
    /**
     * @brief 
     * @param role 
     * @return 
     */
    RequestResult ModifyRole(MemberInfo::Roles::PermissionRole role);
    /**
     * @brief 
     * @param userName 
     * @return 
     */
    RequestResult ModifyUserName(const char* userName);
};
} // namespace yealink
#endif // __ROOM_MEMBER_H__
