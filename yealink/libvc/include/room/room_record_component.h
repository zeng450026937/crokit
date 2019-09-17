/*
 * @file room_record_component.h
 * @date 2019-09-09
 *
 * @brief 
 */
#ifndef __ROOM_RECORD_COMPONENT_H__
#define __ROOM_RECORD_COMPONENT_H__

#include "components/base/simplelib/common_marco_define.h"
#include "room_data.h"

namespace yealink
{
class VC_EXPORT_API RoomRecordComponent
{
    SIMPLE_OBJECT_DECLARE(RoomRecordComponent)
public:
    friend class RoomController;

public:
    RoomRecordUsers GetRecordUsers();

    RoomHttpResult SetRecordStatus(RoomRecordStatus status);
};

} // namespace yealink

#endif // __ROOM_RECORD_COMPONENT_H__
