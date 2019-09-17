/*
 * @file room_rtmp_component.h
 * @date 2019-09-09
 *
 * @brief 
 */
#ifndef __ROOM_RTMP_COMPONENT_H__
#define __ROOM_RTMP_COMPONENT_H__

#include "components/base/simplelib/common_marco_define.h"
#include "room_data.h"

namespace yealink
{
class VC_EXPORT_API RoomRtmpComponent
{
    SIMPLE_OBJECT_DECLARE(RoomRtmpComponent)
public:
    friend class RoomController;

public:
    RoomRtmpState GetRtmpState();

    RoomHttpResult SetRtmpState(RoomRtmpStatus status);
};
} // namespace yealink

#endif // __ROOM_RTMP_COMPONENT_H__
