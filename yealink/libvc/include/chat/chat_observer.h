/*
 * @file chat_observer.h
 * @date 2019-09-18
 *
 * @brief 
 */
#ifndef __CHAT_OBSERVER_H__
#define __CHAT_OBSERVER_H__
#include "chat_message_item.h"

namespace yealink
{
/**
 * @brief virtual base class to receive notify
 */
class ChatObserver
{
public:
    virtual ~ChatObserver()
    {
    }

    /**
     * @brief notify of receive a new message
     * @param message new message
     */
    virtual void OnReceiveMessage(const ChatMessageItem& message)
    {
        (void)message;
    }

    /**
     * @brief notify of dialog change, such as new dialog, order change
     */
    virtual void OnDialogChange()
    {
    }
};

} // namespace yealink

#endif // __CHAT_OBSERVER_H__
