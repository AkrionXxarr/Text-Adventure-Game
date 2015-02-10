#ifndef _ROOM_CLASS_HPP_
#define _ROOM_CLASS_HPP_

#include <string>
#include <vector>
#include "ObjectClass.hpp"
#include "GlobalDefines.hpp"

namespace Room
{
    class Template
    {
    public:
        Template(
            std::string roomName, 
            unsigned int roomID,
            unsigned int roomWidth,
            unsigned int roomHeight
            );
        ~Template();

        void ConnectRoom(Room::Template* room, DIRECTIONS direction);
        void DisplayRoom();

        void AddObject(Obj::Template obj);
        void PlaceObject(unsigned int objID, Obj::Coords coords);
        void ListObjectNames();

        LOCK_STATE CheckLock(DIRECTIONS direction);

        std::string GetName();
        std::string GetDescription();
        unsigned int GetRoomID();
        Obj::Template* GetObject(unsigned int objID);
        Obj::Template* GetObject(std::string command);

        void RemoveObject(unsigned int objID);

        void SetDescription(std::string description);
        void SetLock(DIRECTIONS direction, LOCK_STATE lockState);

        Template* m_north;
        Template* m_east;
        Template* m_south;
        Template* m_west;
        Template* m_up;
        Template* m_down;

    private:
        LOCK_STATE m_northLock,
                    m_eastLock,
                    m_southLock,
                    m_westLock,
                    m_upLock,
                    m_downLock;

        std::string m_roomName;
        std::string m_roomDescription;

        unsigned int m_roomID;
        unsigned int m_roomWidth, m_roomHeight;

        std::vector<std::vector<char> > m_roomData;
        std::vector<std::vector<char> > m_roomTemplate;

        Obj::Template *m_objHead;
        Obj::Template *m_objTail;
        Obj::Template *m_objNull;
    };
};

#endif