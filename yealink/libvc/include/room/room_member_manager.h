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
#include "components/base/simplelib/common_marco_define.h"

namespace yealink
{
class VC_EXPORT_API RoomMemberManager
{
    SIMPLE_OBJECT_DECLARE(RoomMemberManager)
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
    /**
     * @brief 
     * @param entity 
     * @return 
     */
    RoomMember FindUser(const char* entity) const;

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
    /**
     * @brief 
     * @return 
     */
    RoomHttpResult RejectAllHandUp();
    /**
     * @brief send im message to single member
     * @param member member who be sent message
     * @param context context of message
     * @return result for send message, bizCode == 900200 is success
     */
    RoomImResult SendImInfo(const RoomMember& member, const char* context);
    /**
     * @brief send im message to all member
     * @param context context context of message
     * @return result for send message, bizCode == 900200 is success
     */
    RoomImResult SendImInfoToAll(const char* context);
    /**
     * @brief get all im message, and subscribe this notify
     * @param count max count of message
     * @return 
     */
    RoomImMessageList GetAllImInfo(int32_t count);
};
} // namespace yealink
#endif // __ROOM_MEMBER_MANAGER_H__
