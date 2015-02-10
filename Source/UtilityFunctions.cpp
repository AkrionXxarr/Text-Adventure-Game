#include "GlobalHeaders.hpp"
#include "LocalHeaders.hpp"
#include "RoomDeclarations.hpp"
using namespace std;

COMMANDS CommandCheck(string command)
{
    if (_stricmp(command.c_str(), "Examine") == 0)
    {
        return EXAMINE;
    }
    else if (_stricmp(command.c_str(), "Help") == 0)
    {
        return HELP;
    }
    else if (_stricmp(command.c_str(), "Inv") == 0)
    {
        return INV;
    }
    else if (_stricmp(command.c_str(), "Look At") == 0)
    {
        return LOOK;
    }
    else if (_stricmp(command.c_str(), "Open") == 0)
    {
        return OPEN;
    }
    else if (_stricmp(command.c_str(), "Close") == 0)
    {
        return CLOSE;
    }
    else if (_stricmp(command.c_str(), "Status") == 0)
    {
        return STATUS;
    }
    else if (_stricmp(command.c_str(), "Take") == 0)
    {
        return TAKE;
    }
    else if (_stricmp(command.c_str(), "Talk To") == 0)
    {
        return TALK;
    }
    else if (_stricmp(command.c_str(), "Use") == 0)
    {
        return USE;
    }
    else if (_stricmp(command.c_str(), "Unlock") == 0)
    {
        return UNLOCK;
    }
    else if (_stricmp(command.c_str(), "Quit") == 0)
    {
        return QUIT;
    }

    return INVALID_COMMAND;
}

string FirstCommand(string command)
{
    string::iterator iterator;
    string firstCommand;

    for (iterator = command.begin(); iterator < command.end(); iterator++)
    {
        if (*iterator == ':')
        {
            break;
        }
        else
        {
            firstCommand.push_back(*iterator);
        }
    }

    return firstCommand;
}

string SecondCommand(string command)
{
    string::iterator iterator;
    string secondCommand;

    bool onSecondCommand = false;

    for (iterator = command.begin(); iterator < command.end(); iterator++)
    {
        if (*iterator == ':' && !onSecondCommand && (iterator + 1) != command.end())
        {
            iterator++;
            while (*iterator == ' ')
            {
                if ((iterator + 1) != command.end())
                    iterator++;
                else
                    break;
            }
            iterator--;
            onSecondCommand = true;
        }
        else if (onSecondCommand)
        {
            secondCommand.push_back(*iterator);
        }
    }

    return secondCommand;
}

DIRECTIONS DirectionCheck(string command)
{
    if (_stricmp(command.c_str(), "North") == 0)
    {
        return NORTH;
    }
    else if (_stricmp(command.c_str(), "East") == 0)
    {
        return EAST;
    }
    else if (_stricmp(command.c_str(), "South") == 0)
    {
        return SOUTH;
    }
    else if (_stricmp(command.c_str(), "West") == 0)
    {
        return WEST;
    }
    else if (_stricmp(command.c_str(), "Up") == 0)
    {
        return UP;
    }
    else if (_stricmp(command.c_str(), "Down") == 0)
    {
        return DOWN;
    }

    return INVALID_DIRECTION;
}

void DeleteRooms(Room::Template* currentRoom, Room::Template* lastRoom);
void DeleteRooms(Room::Template* startRoom)
{
    DeleteRooms(startRoom, NULL);
}

void DeleteRooms(Room::Template* currentRoom, Room::Template* lastRoom)
{
    // DEBUG //
    if (_DEBUG_MESSAGES)
        cout << "DeleteRooms() recursion currentRoom: " << currentRoom->GetName() << endl;
    ///////////

    if (currentRoom->m_north != NULL && currentRoom->m_north != lastRoom)
        DeleteRooms(currentRoom->m_north, currentRoom);

    if (currentRoom->m_east != NULL && currentRoom->m_east != lastRoom)
        DeleteRooms(currentRoom->m_east, currentRoom);

    if (currentRoom->m_south != NULL && currentRoom->m_south != lastRoom)
        DeleteRooms(currentRoom->m_south, currentRoom);

    if (currentRoom->m_west != NULL && currentRoom->m_west != lastRoom)
        DeleteRooms(currentRoom->m_west, currentRoom);

    if (currentRoom->m_up != NULL && currentRoom->m_up != lastRoom)
        DeleteRooms(currentRoom->m_up, currentRoom);

    if (currentRoom->m_down != NULL && currentRoom->m_down != lastRoom)
        DeleteRooms(currentRoom->m_down, currentRoom);

    // DEBUG //
    if (_DEBUG_MESSAGES)
        cout << "Deleting " << currentRoom->GetName() << endl;
    ///////////

    delete currentRoom;
}