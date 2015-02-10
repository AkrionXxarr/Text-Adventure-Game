#include "RoomClass.hpp"
#include <string>
#include <iostream>
using namespace std;

namespace Room
{
    class Template;
};

//Parameter Constructor//
Room::Template::Template(
                    std::string roomName, 
                    unsigned int roomID,
                    unsigned int roomWidth,
                    unsigned int roomHeight
                    ) : m_roomName(roomName),
                        m_roomID(roomID),
                        m_roomWidth(roomWidth),
                        m_roomHeight(roomHeight)
{
    m_north = NULL;
    m_east = NULL;
    m_south = NULL;
    m_west = NULL;
    m_up = NULL;
    m_down = NULL;

    m_northLock = UNLOCKED;
    m_eastLock = UNLOCKED;
    m_southLock = UNLOCKED;
    m_westLock = UNLOCKED;
    m_upLock = UNLOCKED;
    m_downLock = UNLOCKED;

    m_objHead = new Obj::Template("", 0, 0);
    m_objTail = new Obj::Template("", 0, 0);
    m_objNull = new Obj::Template("", 0, 0);

    m_objHead->Pointer().next = m_objTail;
    m_objHead->Pointer().prev = NULL;
    m_objTail->Pointer().next = NULL;
    m_objTail->Pointer().prev = m_objHead;

    m_roomData.resize(roomHeight, vector<char>(roomWidth));
    m_roomTemplate.resize(roomHeight, vector<char>(roomWidth));

    for (unsigned int row = 0; row < m_roomHeight; row++)
    {
        for (unsigned int col = 0; col < m_roomWidth; col++)
        {
            m_roomData[row][col] = 0;
        }
    }

    for (unsigned int row = 0; row < m_roomHeight; row++)
    {
        for (unsigned int col = 0; col < m_roomWidth; col++)
        {
            //m_roomTemplate[row][col] = (char)178;
            m_roomTemplate[row][col] = (char)219;
        }
    }
    for (unsigned int row = 1; row < (m_roomHeight - 1); row++)
    {
        for (unsigned int col = 1; col < (m_roomWidth - 1); col++)
        {
            //m_roomTemplate[row][col] = (char)219;
            m_roomTemplate[row][col] = (char)32;
        }
    }
}

//Destructor//
Room::Template::~Template()
{
    // DEBUG //
    if (_DEBUG_MESSAGES)
        cout << "In " << m_roomName << " destructor" << endl;
    ///////////

    Obj::Template* objIterator = m_objHead;

    while (objIterator->Pointer().next != NULL)
    {
        objIterator = objIterator->Pointer().next;
        delete objIterator->Pointer().prev;
    }
    delete objIterator;

    delete m_objNull;
}




//Functions//
void Room::Template::ConnectRoom(Room::Template* room, DIRECTIONS direction)
{
    switch (direction)
    {
    case NORTH:
        m_north = room;
        room->m_south = this;
        break;

    case EAST:
        m_east = room;
        room->m_west = this;
        break;
        
    case SOUTH:
        m_south = room;
        room->m_north = this;
        break;
        
    case WEST:
        m_west = room;
        room->m_east = this;
        break;

    case UP:
        m_up = room;
        room->m_down = this;
        break;

    case DOWN:
        m_down = room;
        room->m_up = this;
        break;
    }
}

void Room::Template::DisplayRoom()
{
    for (unsigned int row = 0; row < m_roomHeight; row++)
    {
        for (unsigned int col = 0; col < m_roomWidth; col++)
        {
            if (m_roomData[row][col] != 0)
                cout << m_roomData[row][col];
            else
                cout << m_roomTemplate[row][col];
        }

        if ((row + 1) < m_roomHeight)
            cout << endl;
    }
}

void Room::Template::AddObject(Obj::Template obj)
{
    Obj::Template* iterator = m_objHead;
    Obj::Template* tempObj = new Obj::Template(obj);

    while (iterator->Pointer().next != NULL)
    {
        iterator = iterator->Pointer().next;
    }

    Obj::Template* prevHold = iterator->Pointer().prev;
    Obj::Template* nextHold = iterator;

    tempObj->Pointer().next = nextHold;
    nextHold->Pointer().prev = tempObj;
    tempObj->Pointer().prev = prevHold;
    prevHold->Pointer().next = tempObj;

    tempObj->SetRoomPointer(this);
}

void Room::Template::PlaceObject(unsigned int objID, Obj::Coords coords)
{
    bool gotID(false);
    Obj::Template* iterator = m_objHead;

    while (iterator->Pointer().next != NULL)
    {
        iterator = iterator->Pointer().next;
        if (iterator->GetID() == objID)
        {
            gotID = true;
            break;
        }
    }

    if (gotID && iterator != m_objHead && iterator != m_objTail)
    {
        if (coords.X >= m_roomWidth || coords.Y >= m_roomHeight)
        {
            cout << "<Error> Out of bounds in Room::Template::PlaceObject()" << endl;
            cout << "<Error> In room: " << m_roomName << endl;
            cout << "<Error> With object: " << iterator->GetName() << endl;
            return;
        }

        m_roomData[coords.Y][coords.X] = iterator->GetIcon();
    }
    else
    {
        cout << "<Error> Object ID not found in Room::Template::PlaceObject()" << endl;
        cout << "<Error> In room: " << m_roomName << endl;
        cout << "<Error> With Object ID #" << objID << endl;
    }
}

void Room::Template::ListObjectNames()
{
    Obj::Template* iterator = m_objHead;

    while (iterator->Pointer().next != NULL)
    {
        iterator = iterator->Pointer().next;

        if (iterator->GetName().length() != 0)
        {
            if (iterator->Pointer().prev != m_objHead)
                cout << endl;

            cout << iterator->GetName() << " (" << iterator->GetIcon() << ")";
        }
    }
}

LOCK_STATE Room::Template::CheckLock(DIRECTIONS direction)
{
    switch (direction)
    {
    case NORTH:
        return m_northLock;
        break;

    case EAST:
        return m_eastLock;
        break;
        
    case SOUTH:
        return m_southLock;
        break;
        
    case WEST:
        return m_westLock;
        break;

    case UP:
        return m_upLock;
        break;

    case DOWN:
        return m_downLock;
        break;

    default:
        cout << "<Error> direction not found in Room::Template::CheckLock()" << endl;
        return INVALID_LOCK;
    }
}

std::string Room::Template::GetName() { return m_roomName; }
std::string Room::Template::GetDescription() { return m_roomDescription; }
unsigned int Room::Template::GetRoomID() { return m_roomID; }

Obj::Template* Room::Template::GetObject(unsigned int objID)
{
    bool gotID(false);
    Obj::Template* iterator = m_objHead;

    while (iterator->Pointer().next != NULL)
    {
        iterator = iterator->Pointer().next;
        if (iterator->GetID() == objID)
        {
            gotID = true;
            break;
        }
    }

    if (gotID && iterator != m_objHead && iterator != m_objTail)
    {
        return iterator;
    }
    else
    {
        cout << "<Error> Object ID not found in Room::Template::GetObject()" << endl;
        cout << "<Error> In room: " << m_roomName << endl;
        cout << "<Error> With Object ID #" << objID << endl;
        return NULL;
    }
}

Obj::Template* Room::Template::GetObject(std::string command)
{
    Obj::Template* iterator = m_objHead;

    if (command.length() == 0)
    {
        return m_objNull;
    }

    while (iterator->Pointer().next != NULL)
    {
        iterator = iterator->Pointer().next;
        if (iterator != m_objTail)
        {
            if (_stricmp(command.c_str(), iterator->GetName().c_str()) == 0)
                return iterator;
        }
    }

    return m_objNull;
}

void Room::Template::RemoveObject(unsigned int objID)
{
    bool gotID(false);
    Obj::Template* iterator = m_objHead;

    while (iterator->Pointer().next != NULL)
    {
        iterator = iterator->Pointer().next;
        if (iterator->GetID() == objID)
        {
            gotID = true;
            break;
        }
    }

    if (gotID && iterator != m_objHead && iterator != m_objTail)
    {
        iterator->Pointer().prev->Pointer().next = iterator->Pointer().next;
        iterator->Pointer().next->Pointer().prev = iterator->Pointer().prev;

        delete iterator;
    }
    else
    {
        cout << "<Error> Object ID not found in Room::Template::GetObject()" << endl;
        cout << "<Error> In room: " << m_roomName << endl;
        cout << "<Error> With Object ID #" << objID << endl;
    }
}

void Room::Template::SetDescription(std::string description) { m_roomDescription = description; }

void Room::Template::SetLock(DIRECTIONS direction, LOCK_STATE lockState)
{
    switch (direction)
    {
    case NORTH:
        m_northLock = lockState;
        break;

    case EAST:
        m_eastLock = lockState;
        break;
        
    case SOUTH:
        m_southLock = lockState;
        break;
        
    case WEST:
        m_westLock = lockState;
        break;

    case UP:
        m_upLock = lockState;
        break;

    case DOWN:
        m_downLock = lockState;
        break;
    }
}
