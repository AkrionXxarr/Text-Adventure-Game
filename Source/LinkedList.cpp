#include "LinkedLists.hpp"

LinkedLists::Rooms::Rooms(Room::Template startingRoom)
{
    m_startingRoom = new Room::Template(startingRoom);
}

LinkedLists::Rooms::~Rooms()
{
    delete m_startingRoom;
}