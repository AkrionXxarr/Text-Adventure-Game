#ifndef _OBJECTS_HPP_
#define _OBJECTS_HPP_

#include "GlobalDefines.hpp"
#include <string>

namespace Obj
{
    struct Coords;
    struct Pointers;
    class Template;
};

namespace Room
{
    class Template;
};

namespace Obj
{
    struct Coords
    {
        Coords(unsigned int x, unsigned int y) : X(x), Y(y) { }
        unsigned int X;
        unsigned int Y;
    };

    struct Pointers
    {
        Pointers() : next(NULL), prev(NULL) { }
        Obj::Template* next;
        Obj::Template* prev;
    };

    class Template
    {
    public:
        Template(
            std::string name, 
            char icon, 
            unsigned int objID
            );

        // Variables //
        bool m_isHidden;

        // Commands //
        void Examine();
        void LookAt();
        void Open();
        void Close();
        void Take();
        void Talk();
        void Use();
        void Unlock();
        //////////////

        void Event(COMMANDS command, void (*EventFunc)(Obj::Template*));

        //void AddEventList(void (*EventFunc)(COMMANDS));

        std::string GetExamine();
        std::string GetDescription();
        std::string GetName();
        //void GetEvent(COMMANDS command);
        unsigned int GetID();
        char GetIcon();
        Room::Template* GetRoomPointer();

        Pointers& Pointer();

        void SetExamine(std::string description);
        void SetDescription(std::string description);
        void SetRoomPointer(Room::Template *room);
        void SetIcon(char icon);

    private:
        char m_icon;

        unsigned int m_objID;

        Pointers m_Pointers;

        std::string m_name;
        std::string m_description;
        std::string m_examine;

        void (*m_ExamineFunc)(Obj::Template*);
        void (*m_LookFunc)(Obj::Template*);
        void (*m_OpenFunc)(Obj::Template*);
        void (*m_CloseFunc)(Obj::Template*);
        void (*m_TakeFunc)(Obj::Template*);
        void (*m_TalkFunc)(Obj::Template*);
        void (*m_UseFunc)(Obj::Template*);
        void (*m_UnlockFunc)(Obj::Template*);

        Room::Template* m_room;
    };
};
#endif