#include "GlobalHeaders.hpp"
#include "LocalHeaders.hpp"
#include "UtilityFunctions.hpp"
#include "SubCommands.hpp"

using namespace std;

Inv::Inventory inventory;
Character::Template player;

//
// Main Goal:
// - Obtain Michael's Laptop
//
// Basic steps to achieve Main Goal:
// - Need a specific object to defeat Michael
//   after trying to take the laptop.
//   (This specific item is Spaz)
//
// - Spaz can be found in Brett's room, however
//   the room will be locked.
//
// - Brett (at his computer) will hint that the key 
//   was last in another pair of pants. You will need
//   to talk to him repeatedly to get this information.
//
// - Susan (found in the living room) will ask you to 
//   take a load of laundry to the washing machine, 
//   and then move it to the dryer.
//

void GameLoop(Room::Template* curRoom)
{
    bool quitGame(false);
    string command;
    string firstCommand;
    string secondCommand;

    cout << "Goal: Obtain Michael's laptop." << endl << endl;

    cout << "Type 'Help' for a list of commands and instructions." << endl << endl;

    cout << "-- " << curRoom->GetName() << " --" << endl;
    curRoom->DisplayRoom();
    cout << endl << endl;

    while (!quitGame)
    {
        cout << ">> "; getline(cin, command);
        cout << endl;

        firstCommand = FirstCommand(command);
        secondCommand = SecondCommand(command);

        if (DirectionCheck(firstCommand) != INVALID_DIRECTION)
        {
            curRoom = Move(curRoom, firstCommand);
        }
        else
        {
            switch (CommandCheck(firstCommand))
            {
            case EXAMINE:
                if (_stricmp(secondCommand.c_str(), "Room") == 0)
                {
                    cout << curRoom->GetDescription() << endl << endl;
                    curRoom->ListObjectNames();
                }
                else
                {
                    curRoom->GetObject(secondCommand)->Examine();
                }
                break;

            case HELP:
                HelpMessage();

                cout << "-- " << curRoom->GetName() << " --" << endl;
                curRoom->DisplayRoom();
                break;

            case INV:
                inventory.ListItems();
                break;
                
            case LOOK:
                if (_stricmp(secondCommand.c_str(), "Room") == 0)
                {
                    cout << "-- " << curRoom->GetName() << " --" << endl;
                    curRoom->DisplayRoom();
                    cout << endl;
                }
                else
                {
                    curRoom->GetObject(secondCommand)->LookAt();
                }

                break;

            case OPEN:
                curRoom->GetObject(secondCommand)->Open();
                break;

            case CLOSE:
                curRoom->GetObject(secondCommand)->Close();
                break;

            case STATUS:
                cout << "Stats for " << player.GetCharacterName() << endl;
                cout << "Health: " << player.GetCurrentHealth() << "/" << player.GetMaxHealth();
                break;

            case TAKE:
                curRoom->GetObject(secondCommand)->Take();
                break;

            case TALK:
                curRoom->GetObject(secondCommand)->Talk();
                break;

            case USE:
                curRoom->GetObject(secondCommand)->Use();
                break;

            case UNLOCK:
                curRoom->GetObject(secondCommand)->Unlock();
                break;

            case QUIT:
                quitGame = true;
                cout << "Quitting game...";
                break;

            case INVALID_COMMAND:
                cout << "Unknown command";
                break;
            }
        }
        cout << endl << endl;

        if (player.GetStatus() == DEAD)
        {
            cout << "Game Over" << endl << endl;
            quitGame = true;
        }
        else if (wonGame)
        {
            cout << "Congratulations! You beat the game!" << endl << endl;
            quitGame = true;
        }
    }
}

/*
void GameLoop()
{
    cout << "Current commands: Go, Look, Examine, Quit" << endl;
    cout << "Current directions: North, East, South, West, Up, Down" << endl << endl;

    cout << "Usage example:" << endl;
    cout << "> Go" << endl;
    cout << "Go where?" << endl;
    cout << "> North" << endl << endl;

    cout << "Current commands for Look and Examine: Room" << endl;
    cout << "Usage example:" << endl;
    cout << "> Look" << endl;
    cout << "Look at what?" << endl;
    cout << "> Room" << endl << endl;

    cout << "Look to re-print a visual layout of the room, Examine to get a list of objects in the room." << endl;



    //declarations//
    Room::Template *startRoom;
    Room::Template *curRoom;

    bool done(false);
    string command;
    ////////////////

    startRoom = BuildRooms();
    curRoom = startRoom;

    cout << endl << "-- " << curRoom->GetName() << " --" << endl;
    curRoom->DisplayRoom();
    cout << endl;

    while (!done)
    {
        cout << "> "; getline(cin, command);

        switch (CommandCheck(command))
        {
        case GO:
            cout << "Go where?" << endl;
            cout << "> "; getline(cin, command);

            switch (DirectionCheck(command))
            {
            case NORTH:
                if (curRoom->m_north != NULL)
                {
                    curRoom = curRoom->m_north;

                    cout << endl << "-- " << curRoom->GetName() << " --" << endl;
                    curRoom->DisplayRoom();
                    cout << endl << endl;
                }
                
                break;

            case EAST:
                if (curRoom->m_east != NULL)
                {
                    curRoom = curRoom->m_east;

                    cout << endl << "-- " << curRoom->GetName() << " --" << endl;
                    curRoom->DisplayRoom();
                    cout << endl;
                }
                break;

            case SOUTH:
                if (curRoom->m_south != NULL)
                {
                    curRoom = curRoom->m_south;

                    cout << endl << "-- " << curRoom->GetName() << " --" << endl;
                    curRoom->DisplayRoom();
                    cout << endl;
                }
                break;

            case WEST:
                if (curRoom->m_west != NULL)
                {
                    curRoom = curRoom->m_west;

                    cout << endl << "-- " << curRoom->GetName() << " --" << endl;
                    curRoom->DisplayRoom();
                    cout << endl;
                }
                break;

            case UP:
                if (curRoom->m_up != NULL)
                {
                    curRoom = curRoom->m_up;

                    cout << endl << "-- " << curRoom->GetName() << " --" << endl;
                    curRoom->DisplayRoom();
                    cout << endl;
                }
                break;

            case DOWN:
                if (curRoom->m_down != NULL)
                {
                    curRoom = curRoom->m_down;

                    cout << endl << "-- " << curRoom->GetName() << " --" << endl;
                    curRoom->DisplayRoom();
                    cout << endl;
                }
                break;

            case INVALID_DIRECTION:
                cout << "Invalid direction" << endl;
            }
            break;

        case LOOK:
            cout << "Look at what?" << endl;
            cout << "> "; getline(cin, command);

            if (_stricmp(command.c_str(), "Room") == 0)
            {
                cout << endl << "-- " << curRoom->GetName() << " --" << endl;
                curRoom->DisplayRoom();
                cout << endl;
            }
            else
            {
                cout << curRoom->ShortObjectDesc(command) << endl;
            }
            break;

        case EXAMINE:
            cout << "Examine what?" << endl;
            cout << "> "; getline(cin, command);

            if (_stricmp(command.c_str(), "Room") == 0)
            {
                cout << endl << "Objects:" << endl; 
                curRoom->ListObjectNames();
            }
            else
            {
                cout << curRoom->LongObjectDesc(command) << endl;
            }

            break;

        case QUIT:
            done = true;
            break;

        case INVALID_COMMAND:
            cout << "Invalid command" << endl;
        }
        cout << endl;
    }

    DeleteRooms(startRoom);
}
*/