/*
 * @file room_view_component.h
 * @date 2019-03-21
 * 
 * @brief 
 */

#ifndef __ROOM_VIEW_COMPONENT_H__
#define __ROOM_VIEW_COMPONENT_H__
#include "room/room_data.h"
#include "room/room_define.h"
#include "components/base/simplelib/common_marco_define.h"

namespace yealink
{
class VC_EXPORT_API RoomViewComponent
{
    SIMPLE_OBJECT_DECLARE(RoomViewComponent)
public:
    friend class RoomController;

public:
    /**
     * @brief 
     * @return 
     */
    ConferenceView GetConferenceView();

public:
    /**
     * @brief 
     * @param policy 
     * @param attendeeByPass 
     * @param autoPromote 
     * @return 
     */
    RequestResult ModifyConferenceLock(
        ConferenceDescription::AdmissionPolicy policy,
        ConferenceDescription::AttendeeByPass attendeeByPass,
        ConferenceDescription::AutoPromote autoPromote);
    /**
     * @brief 
     * @param layout 
     * @param maxView 
     * @return 
     */
    RequestResult ModifyLayout(ConferenceView::EntityState::VideoLayout layout, uint32_t maxView);
    /**
     * @brief 
     * @return 
     */
    RequestResult MuteAll();
    /**
     * @brief 
     * @return 
     */
    RequestResult UnMuteAll();
    /**
     * @brief 
     * @return 
     */
    RequestResult CancelFocus();
    /**
     * @brief set speak mode
     * @param speakMode speak mode of conference
     * @return 
     */
    RoomHttpResult SetSpeakMode(ConferenceViewSpeakMode speakMode);
};
} // namespace yealink
#endif // __ROOM_VIEW_COMPONENT_H__
