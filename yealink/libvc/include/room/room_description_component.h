/*
 * @file room_description_component.h
 * @date 2019-03-21
 * 
 * @brief 
 */

#ifndef __ROOM_DESCRIPTION_COMPONENT_H__
#define __ROOM_DESCRIPTION_COMPONENT_H__
#include "room/room_data.h"
#include "room/room_define.h"

namespace yealink
{
class ROOM_API RoomDescriptionComponent
{
    ROOM_COMPONENT_DECLARE(RoomDescriptionComponent)
public:
    friend class RoomController;

    /**
     * @brief 
     * @return 
     */
    ConferenceDescription GetConferenceDescription() const;
    /**
     * @brief 
     * @return 
     */
    SStringA GetConfInfoUrl() const;
    /**
     * @brief 
     * @return 
     */
    RequestResult GetShareInfo() const;
};
} // namespace yealink

#endif // __ROOM_DESCRIPTION_COMPONENT_H__
