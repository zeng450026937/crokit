/*
 * @file chat_manager.h
 * @date 2019-09-17
 *
 * @brief 
 */
#ifndef __CHAT_MANAGER_H__
#define __CHAT_MANAGER_H__
#include "chat_message_item.h"
#include "chat_dialog.h"
#include "chat_observer.h"

#include "components/base/simplelib/common_marco_define.h"
#include "room/room_controller.h"
#include "room/room_member.h"

namespace yealink
{
/**
 * @class ChatManager
 * @brief manager of chat module
 * @note each meeting will has its chat manager
 */
class VC_EXPORT_API ChatManager
{
    SIMPLE_OBJECT_DECLARE(ChatManager)
public:
    /**
     * @brief create a available chat manager
     * @param controller room controller in this meeting
     * @param maxMessageCount max message count of public chat
     * @note each meeting has its chat manager
     */
    ChatManager(const RoomController& controller, int32_t maxMessageCount);

    /**
     * @brief add observer to chat manager to receive notify
     * @param observer 
     */
    void AddObserver(ChatObserver* observer);
    /**
     * @brief remove observer
     * @param observer 
     */
    void RemoveObserver(ChatObserver* observer);

    /**
     * @brief send a message to public dialog
     * @param context context of message
     * @return
     * @note if interface is return, message item is success or fail.
     */
    ChatMessageItem SendMessageToAll(const char* context);
    /**
     * @brief send a message to single member
     * @param member target member
     * @param context context of message
     * @return 
     * @note if interface is return, message item is success or fail.
     */
    ChatMessageItem SendMessageToMember(const RoomMember& member, const char* context);
    /**
     * @brief retry message
     * @param message message item which to retry
     * @return success or failure
     * @note retry will reset timestamp of message
     */
    bool RetryMessage(const ChatMessageItem& message);

    /**
     * @brief get public dialog object
     * @return 
     */
    ChatDialog GetPublicDialog();
    /**
     * @brief get private dialog object list
     * @return 
     */
    Array<ChatDialog> GetPrivateDialogList();
};

} // namespace yealink

#endif // __CHAT_MANAGER_H__
