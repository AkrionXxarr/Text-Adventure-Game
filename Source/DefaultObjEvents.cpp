#include "ObjectClass.hpp"
#include <iostream>
using namespace std;

// Constructor Defaults //
void DefaultExamineEvent(Obj::Template* obj)
{
    if (obj->GetID() == 0)
    {
        cout << "Object not found.";
    }
    else
    {
        cout << obj->GetExamine();
    }
}

void DefaultLookEvent(Obj::Template* obj)
{
    if (obj->GetID() == 0)
    {
        cout << "Object not found.";
    }
    else
    {
        cout << obj->GetDescription();
    }
}

void DefaultOpenEvent(Obj::Template* obj)
{
    if (obj->GetID() == 0)
    {
        cout << "Object not found.";
    }
    else
    {
        cout << "You can't open that.";
    }
}

void DefaultCloseEvent(Obj::Template* obj)
{
    if (obj->GetID() == 0)
    {
        cout << "Object not found.";
    }
    else
    {
        cout << "You can't close that.";
    }
}

void DefaultTakeEvent(Obj::Template* obj)
{
    if (obj->GetID() == 0)
    {
        cout << "Object not found.";
    }
    else
    {
        cout << "You can't take that.";
    }
}

void DefaultTalkEvent(Obj::Template* obj)
{
    if (obj->GetID() == 0)
    {
        cout << "Object not found.";
    }
    else
    {
        cout << obj->GetName() << " doesn't seem to respond...";
    }
}

void DefaultUseEvent(Obj::Template* obj)
{
    if (obj->GetID() == 0)
    {
        cout << "Object not found.";
    }
    else
    {
        cout << "You can't use that.";
    }
}

void DefaultUnlockEvent(Obj::Template* obj)
{
    if (obj->GetID() == 0)
    {
        cout << "Object not found.";
    }
    else
    {
        cout << "You can't unlock that.";
    }
}

// Additional Defaults //
void DefaultOpenDoorEvent(Obj::Template* obj)
{
    cout << "Doors don't need to be opened, you simply move through them.";
}

void DefaultCloseDoorEvent(Obj::Template* obj)
{
    cout << "Doors don't need to be closed, you simply move through them.";
}