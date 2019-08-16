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
     * @brief get share info
     * @param language language of share info
     * @return request result, and wait notify
     * @note 
     * English: "en"\n
     * Simplified Chinese: "zh"\n
     * Traditional Chinese: "tw"\n
     * Spanish: "es"\n
     * Polish: "pl"\n
     * Portuguese: "pt"\n
     * Russian: "ru"\n
     */
    RequestResult GetShareInfo(const char* language) const;
};
} // namespace yealink

#endif // __ROOM_DESCRIPTION_COMPONENT_H__
