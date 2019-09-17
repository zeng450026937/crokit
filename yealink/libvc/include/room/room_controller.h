/*
 * @file room_controller.h
 * @date 2019-03-21
 *
 * @brief
 */

#ifndef __ROOM_CONTROLLER_H__
#define __ROOM_CONTROLLER_H__
#include "access/access_agent.h"
#include "room/room_define.h"
#include "room/room_description_component.h"
#include "room/room_member_manager.h"
#include "room/room_observer.h"
#include "room/room_state_component.h"
#include "room/room_view_component.h"
#include "sip_agent/sip_client.h"
#include "room_rtmp_component.h"
#include "room_record_component.h"

namespace yealink
{
/**
 * @brief room controller, can control a conference, and it's safe for copy.
 */
class ROOM_API RoomController
{
public:
    /**
     * @brief 
     */
    struct ConferenceParam
    {
        SStringA conferenceUri;
        SStringA conferenceEntity;
    };

    /**
     * @brief 
     */
    struct ConferenceContent
    {
        SStringA content;
        SStringA contentType;
    };

public:
    /**
     * @brief create an invalid controller, with need to init.
     */
    RoomController();
    /**
     * @brief 
     */
    ~RoomController();
    /**
     * @brief copy destructor, this is safe for copy.
     * @param other another controller 
     */
    RoomController(const RoomController& other);
    /**
     * @brief equal operator, this is safe for copy.
     * @param other another controller 
     * @return *this
     */
    RoomController& operator=(const RoomController& other);

public:
    /**
     * @brief 
     */
    void Init();
    /**
     * @brief 
     * @param conversationId 
     */
    void SetConversationId(const char* conversationId);
    /**
     * @brief set access agent, before join
     * @param agent 
     */
    void SetAccessAgent(AccessAgent* agent);
    /**
     * @brief 
     * @param observer 
     */
    void AddObserver(RoomObserver* observer);
    /**
     * @brief 
     * @param observer 
     */
    void RemoveObserver(RoomObserver* observer);
    /**
     * @brief 
     * @return 
     */
    bool Available() const;
    /**
     * @brief connect with conference uri and entity
     * @param client sip client
     * @param param struct with conference uri and entity
     * @return connect result
     */
    ConferenceResult Join(SIPClient* client, const ConferenceParam& param);
    /**
     * @brief connect with content and conten type
     * @param client sip client
     * @param content struct with content and content type
     * @return connect result
     */
    ConferenceResult Join(SIPClient* client, const ConferenceContent& content);
    /**
     * @brief connect with meeting now
     * @param client sip client
     * @param subject conference tile
     * @param entityViewList conference entity list, default use empty(equal to audio-video, chat, applicationsharing)
     * @return connect result
     */
    ConferenceResult CreateTempMeeting(SIPClient* client, const char* subject, const Array<SStringA>& entityViewList);
    /**
     * @brief reconnect subscription channel by force
     * @return 
     */
    bool ReconnectSubscriptionForce();
    /**
     * @brief 
     * @param reason 
     * @return 
     */
    ConferenceResult Leave(const char* reason);
    /**
     * @brief 
     * @return 
     */
    ConferenceResult Close();

public:
    /* get component for other function */
    /**
     * @brief 
     * @return 
     */
    RoomDescriptionComponent GetDescriptionComponent();
    /**
     * @brief 
     * @return 
     */
    RoomStateComponent GetStateComponent();
    /**
     * @brief 
     * @return 
     */
    RoomMemberManager GetMemberManager();
    /**
     * @brief 
     * @return 
     */
    RoomViewComponent GetViewComponent();
    RoomRtmpComponent GetRtmpComponent();
    RoomRecordComponent GetRecordComponent();

private:
    RoomController(void* data);
    void Clear();
    void* m_data;
};
} // namespace yealink
#endif // __ROOM_CONTROLLER_H__
