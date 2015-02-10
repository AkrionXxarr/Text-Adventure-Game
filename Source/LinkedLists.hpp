#ifndef _LINKED_LISTS_HPP_
#define _LINKED_LISTS_HPP_

#include "RoomClass.hpp"
#include <string>

namespace LinkedLists
{
    class Rooms
    {
    public:
        Rooms(Room::Template startingRoom);
        ~Rooms();

        Room::Template* GetRoom(unsigned int roomID);

    private:
        Room::Template* m_startingRoom;
    };
};

#endif