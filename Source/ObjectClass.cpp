#include "ObjectClass.hpp"
#include "DefaultObjEvents.hpp"

#include <iostream>
using namespace std;

Obj::Template::Template(
                   std::string name, 
                   char icon, 
                   unsigned int objID
                    ) : m_name(name), 
                        m_icon(icon),
                        m_objID(objID),
                        m_isHidden(false)
{
    m_ExamineFunc = &DefaultExamineEvent;
    m_LookFunc    = &DefaultLookEvent;
    m_OpenFunc    = &DefaultOpenEvent;
    m_CloseFunc   = &DefaultCloseEvent;
    m_TakeFunc    = &DefaultTakeEvent;
    m_TalkFunc    = &DefaultTalkEvent;
    m_UseFunc     = &DefaultUseEvent;
    m_UnlockFunc  = &DefaultUnlockEvent;
}

/*
void Obj::Template::AddEventList(void (*EventFunc)(COMMANDS))
{
    m_EventFunc = EventFunc;
    m_haveEventList = true;
}
*/

void Obj::Template::Examine()
{
    m_ExamineFunc(this);
}

void Obj::Template::LookAt()
{
    m_LookFunc(this);
}

void Obj::Template::Open()
{
    m_OpenFunc(this);
}

void Obj::Template::Close()
{
    m_CloseFunc(this);
}

void Obj::Template::Take()
{
    m_TakeFunc(this);
}

void Obj::Template::Talk()
{
    m_TalkFunc(this);
}

void Obj::Template::Use()
{
    m_UseFunc(this);
}

void Obj::Template::Unlock()
{
    m_UnlockFunc(this);
}

void Obj::Template::Event(COMMANDS command, void (*EventFunc)(Obj::Template*))
{
    switch (command)
    {
    case EXAMINE:
        m_ExamineFunc = EventFunc;
        break;

    case LOOK:
        m_LookFunc = EventFunc;
        break;

    case OPEN:
        m_OpenFunc = EventFunc;
        break;

    case CLOSE:
        m_CloseFunc = EventFunc;
        break;

    case TAKE:
        m_TakeFunc = EventFunc;
        break;

    case TALK:
        m_TalkFunc = EventFunc;
        break;

    case USE:
        m_UseFunc = EventFunc;
        break;

    case UNLOCK:
        m_UnlockFunc = EventFunc;
        break;

    default:
        cout << "<Error> Obj::Template::Event() recieved incorrect command" << endl;
        cout << "<Error> With object: " << m_name << endl;
    }
}
 
string Obj::Template::GetExamine() { return m_examine; }
string Obj::Template::GetDescription() { return m_description; }
string Obj::Template::GetName() { return m_name; }
unsigned int Obj::Template::GetID() { return m_objID; }
char Obj::Template::GetIcon() { return m_icon; }
Room::Template* Obj::Template::GetRoomPointer() { return m_room; }

Obj::Pointers& Obj::Template::Pointer() { return m_Pointers; }

void Obj::Template::SetExamine(string description) { m_examine = description; }
void Obj::Template::SetDescription(string description) { m_description = description; }
void Obj::Template::SetRoomPointer(Room::Template *room) { m_room = room; }
void Obj::Template::SetIcon(char icon) { m_icon = icon; }