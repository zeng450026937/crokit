/*
 * @file room_state_component.h
 * @date 2019-03-21
 * 
 * @brief 
 */

#ifndef __ROOM_STATE_COMPONENT_H__
#define __ROOM_STATE_COMPONENT_H__
#include "room/room_define.h"
#include "room/room_data.h"
#include "components/base/simplelib/common_marco_define.h"

namespace yealink
{
class VC_EXPORT_API RoomStateComponent
{
    SIMPLE_OBJECT_DECLARE(RoomStateComponent)
public:
    friend class RoomController;

public:
    /**
     * @brief 
     * @return 
     */
    ConferenceState GetConferenceState() const;
};
} // namespace yealink
#endif // __ROOM_STATE_COMPONENT_H__
