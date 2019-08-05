/*
 * @file room_member_manager.h
 * @date 2019-03-21
 * 
 * @brief 
 */

#ifndef __ROOM_MEMBER_MANAGER_H__
#define __ROOM_MEMBER_MANAGER_H__
#include "room/room_member.h"
#include "components/base/simplelib/simple_lib.h"
#include "room/room_define.h"

namespace yealink
{
class ROOM_API RoomMemberManager
{
    ROOM_COMPONENT_DECLARE(RoomMemberManager)
public:
    friend class RoomController;

public:
    /* getter interface */
    /**
     * @brief 
     * @return 
     */
    Array<RoomMember> GetMemberList() const;
    /**
     * @brief 
     * @return 
     */
    RoomMember GetOwner() const;

public:
    /* setter interface */
    /**
     * @brief 
     * @param userUri 
     * @return 
     */
    RequestResult InviteUser(const char* userUri);
    /**
     * @brief 
     * @param userUri
     * @param userUuid 
     * @return 
     */
    RequestResult InviteUserWithUuid(const char* userUri, const char* userUuid);
    /**
     * @brief 
     * @param userUriList 
     * @return 
     */
    RequestResult InviteUserList(const Array<SStringA>& userUriList);
    /**
     * @brief 
     * @param memberList 
     * @return 
     */
    RequestResult GrantedLobby(const Array<RoomMember>& memberList);
    /**
     * @brief 
     * @return 
     */
    RequestResult GrantedLobbyAll();
    /**
     * @brief 
     * @param memberList 
     * @return 
     */
    RequestResult DeleteLobby(const Array<RoomMember>& memberList);
    /**
     * @brief 
     * @return 
     */
    RequestResult DeleteLobbyAll();
};
} // namespace yealink
#endif // __ROOM_MEMBER_MANAGER_H__
