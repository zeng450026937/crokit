/*
 * @file room_observer.h
 * @date 2019-03-21
 * 
 * @brief 
 */

#ifndef __ROOM_OBSERVER_H__
#define __ROOM_OBSERVER_H__

#include "room/room_member.h"
#include "room/room_data.h"

namespace yealink
{
class RoomObserver
{
public:
    virtual ~RoomObserver()
    {
    }
    /**
     * @brief 
     */
    virtual void OnConnectSuccess()
    {
    }
    /**
     * @brief 
     * @param reason 
     */
    virtual void OnConnectFailure(const char* reason)
    {
        (void)reason;
    }
    /**
     * @brief 
     * @param message 
     */
    virtual void OnReceiveInviteMessage(const char* message)
    {
        (void)message;
    }
    /**
     * @brief 
     * @param message 
     */
    virtual void OnReceiveSubscriptionMessage(const char* message)
    {
        (void)message;
    }
    /**
     * @brief 
     * @param response 
     */
    virtual void OnResponse(const ResponseResult& response)
    {
        (void)response;
    }
    /**
     * @brief notify on subscription disconnect
     */
    virtual void OnSubscriptionDisconnect()
    {
    }
    /**
     * @brief 
     * @param conferenceDescription 
     */
    virtual void OnConferenceDescriptionChange(const ConferenceDescription& conferenceDescription)
    {
        (void)conferenceDescription;
    }
    /**
     * @brief 
     * @param conferenceState 
     */
    virtual void OnConferenceStateChange(const ConferenceState& conferenceState)
    {
        (void)conferenceState;
    }
    /**
     * @brief 
     * @param conferenceView 
     */
    virtual void OnConferenceViewChange(const ConferenceView& conferenceView)
    {
        (void)conferenceView;
    }
    /**
     * @brief 
     * @param memberList 
     */
    virtual void OnUsersLoadAll(const Array<RoomMember>& memberList)
    {
        (void)memberList;
    }
    /**
     * @brief 
     * @param newMemberList 
     * @param modifyMemberList 
     * @param deleteMemberList 
     */
    virtual void OnUserChange(
        const Array<RoomMember>& newMemberList,
        const Array<RoomMember>& modifyMemberList,
        const Array<RoomMember>& deleteMemberList)
    {
        (void)newMemberList;
        (void)modifyMemberList;
        (void)deleteMemberList;
    }
    /**
     * @brief 
     * @param member 
     * @param info 
     */
    virtual void OnGetUserCallStats(const RoomMember& member, const Array<UserMediaInfo>& info)
    {
        (void)member;
        (void)info;
    }
    /**
     * @brief notify on get share info response
     * @param requestId
     * @param shareInfo share info message
     */
    virtual void OnGetShareInfo(int64_t requestId, const char* shareInfo)
    {
        (void)requestId;
        (void)shareInfo;
    }
};

} // namespace yealink
#endif // __ROOM_OBSERVER_H__
