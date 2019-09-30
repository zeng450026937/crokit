/*
 * @file chat_dialog.h
 * @date 2019-09-24
 *
 * @brief 
 */
#ifndef __CHAT_DIALOG_H__
#define __CHAT_DIALOG_H__
#include "components/base/simplelib/common_marco_define.h"
#include "room/room_member.h"
#include "chat_message_item.h"

namespace yealink
{
/**
 * @class ChatDialog
 * @brief public dialog or private dialog object
 * @note private dialog will bind to a single
 */
class VC_EXPORT_API ChatDialog
{
    SIMPLE_OBJECT_DECLARE(ChatDialog)
public:
    friend class ChatManager;

public:
    /**
     * @brief check dialog is private
     * @return 
     */
    bool IsPrivate() const;
    /**
     * @brief get member who send to in this dialog
     * @return member object
     */
    RoomMember GetTargetMember() const;
    /**
     * @brief get all message item sort by timestamp
     * @return message items
     * @note this interface will sort message
     */
    Array<ChatMessageItem> GetMessageList() const;
    /**
     * @brief get unread message count
     * @return 
     */
    int64_t GetUnreadCount() const;

    /**
     * @brief set a message to read
     * @param messageItem message which to be read
     * @return 
     */
    bool SetMessageRead(const ChatMessageItem& messageItem);
    /**
     * @brief clear all unread message
     * @return 
     */
    bool ClearUnread();
    /**
     * @brief get message size
     * @return
     * @note this interface without sort
     */
    int64_t GetMessageSize();
};

} // namespace yealink

#endif // __CHAT_DIALOG_H__
