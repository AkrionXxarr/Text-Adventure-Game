#include "GlobalHeaders.hpp"
#include "LocalHeaders.hpp"
#include "UtilityFunctions.hpp"
using namespace std;

Room::Template* Move(Room::Template* curRoom, string direction)
{
    Room::Template* lastRoom = curRoom;
    switch (DirectionCheck(direction))
    {
    case NORTH:
        if (curRoom->m_north != NULL)
        {
            if (curRoom->CheckLock(NORTH) == UNLOCKED)
                curRoom = curRoom->m_north;
            else
                cout << "The way is blocked.";
        }
        else
        {
            cout << "You can't go that way.";
        }
        
        break;

    case EAST:
        if (curRoom->m_east != NULL)
        {
            if (curRoom->CheckLock(EAST) == UNLOCKED)
                curRoom = curRoom->m_east;
            else
                cout << "The way is blocked.";
        }
        else
        {
            cout << "You can't go that way.";
        }

        break;

    case SOUTH:
        if (curRoom->m_south != NULL)
        {
            if (curRoom->CheckLock(SOUTH) == UNLOCKED)
                curRoom = curRoom->m_south;
            else
                cout << "The way is blocked.";
        }
        else
        {
            cout << "You can't go that way.";
        }

        break;

    case WEST:
        if (curRoom->m_west != NULL)
        {
            if (curRoom->CheckLock(WEST) == UNLOCKED)
                curRoom = curRoom->m_west;
            else
                cout << "The way is blocked.";
        }
        else
        {
            cout << "You can't go that way.";
        }

        break;

    case UP:
        if (curRoom->m_up != NULL)
        {
            if (curRoom->CheckLock(UP) == UNLOCKED)
                curRoom = curRoom->m_up;
            else
                cout << "The way is blocked.";
        }
        else
        {
            cout << "You can't go that way.";
        }

        break;

    case DOWN:
        if (curRoom->m_down != NULL)
        {
            if (curRoom->CheckLock(DOWN) == UNLOCKED)
                curRoom = curRoom->m_down;
            else
                cout << "The way is blocked.";
        }
        else
        {
            cout << "You can't go that way.";
        }

        break;

    case INVALID_DIRECTION:
        cout << "Invalid direction";
    }

    if (curRoom != lastRoom)
    {
        cout << "-- " << curRoom->GetName() << " --" << endl;
        curRoom->DisplayRoom();
    }

    return curRoom;
}

void HelpMessage()
{
    cout << "=== Targeted Commands ===" << endl;
    cout << "Look At - Inspect your 'target'" << endl;
    cout << "Examine - Make a close inspection of your 'target'" << endl;
    cout << "Open ---- Attempt to open your 'target'" << endl;
    cout << "Close --- Attempt to close your 'target'" << endl;
    cout << "Take ---- Attempt to take your 'target'" << endl;
    cout << "Talk To - Attempt talking to your 'target'" << endl;
    cout << "Use ----- Attempt to 'activate' your 'target' in some way" << endl;
    cout << "Unlock -- Attempt to unlock a locked 'target'" << endl << endl;

    cout << "=== Movement Commands ===" << endl;
    cout << "North, East, South, West, Up, Down" << endl << endl;

    cout << "=== Other Commands ===" << endl;
    cout << "Status -- Displays your character stats" << endl;
    cout << "Inv ----- Displays your inventory" << endl;
    cout << "Help ---- Displays this message" << endl;
    cout << "Quit ---- Quits the game" << endl << endl;

    cout << "Press <ENTER> for next page...";
    cin.ignore(INT_MAX, '\n');
    cout << endl;

    cout << "- How you choose your target -" << endl;
    cout << "Type the command, followed by a colon (:), followed by the object name" << endl;
    cout << "For example..." << endl;
    cout << ">> Look At: South Door" << endl;
    cout << ">> Examine: Bed" << endl;
    cout << ">> Talk To: Sink" << endl << endl;

    cout << "- How you move from room to room -" << endl;
    cout << "Simply type the direction you want to move, with 'North' being the top." << endl;
    cout << "For example..." << endl;
    cout << ">> North" << endl;
    cout << ">> Up" << endl << endl;

    cout << "- Notes -" << endl;
    cout << "* Using the commands (Look At: Room) and (Examine: Room) will display various" << endl;
    cout << "information about the room you're currently in." << endl;
    cout << "* Look At will re-print the overhead view of the room," << endl;
    cout << "and Examine will list all visible objects in the room." << endl;
    cout << "* Commands are NOT case sensitive" << endl << endl;

    cout << "Press <ENTER> to continue...";
    cin.ignore(INT_MAX, '\n');
    cout << endl;
}