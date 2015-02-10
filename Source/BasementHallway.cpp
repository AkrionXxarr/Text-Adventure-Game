#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"
#include "DefaultObjEvents.hpp"
using namespace std;

#include <stdlib.h>
#include <time.h>

static enum OBJECTS { NO_OBJECT, NORTH_DOOR, WEST_DOOR, FLOOR, WASHER, DRYER, RECYCLING, FAN, MISC, CURTAIN, KEY };

static bool didLaundry = false;
static bool gotKey = false;
static bool washer_IsOpen = false;
static bool dryer_IsOpen = false;

// Event forward declarations //
static void curtain_Open(Obj::Template* obj);

static void washer_Open(Obj::Template* obj);
static void washer_Close(Obj::Template* obj);
static void washer_Use(Obj::Template* obj);

static void dryer_Open(Obj::Template* obj);
static void dryer_Close(Obj::Template* obj);
static void dryer_Use(Obj::Template* obj);

// Special Event forward declarations //
static void WasherBattle();

void BuildBasementHallway(Room::Template* room)
{
    // Create Objects //
    Obj::Template northDoor("North Door", '#', NORTH_DOOR);
    Obj::Template westDoor("West Door", '#', WEST_DOOR);
    Obj::Template floor("", (char)32, FLOOR);
    Obj::Template washer("Washing Machine", (char)21, WASHER);
    Obj::Template dryer("Dryer", (char)232, DRYER);
    Obj::Template recycling("Recycling Bin", 'o', RECYCLING);
    Obj::Template fan("Fan", '*', FAN);
    Obj::Template misc("Misc. stuff", (char)176, MISC);
    Obj::Template curtain("Curtain", '|', CURTAIN);

    // Describe Room //
    room->SetDescription("The hallway is somewhat cluttered with various items;\n"
                         "it also doubles as the house's laundry room.\n"
                         "The floor is smoothed concrete.");

    // Describe Objects //
    northDoor.SetDescription("A featureless wooden door that leads to Aki's Room.");
    northDoor.SetExamine("You search the door but find nothing of interest.");

    westDoor.SetDescription("A featureless wooden door that leads to the Bathroom.");
    westDoor.SetExamine("You search the door but find nothing of interest.");

    washer.SetDescription("A standard washing machine.");
    washer.SetExamine("You search the washing machine but find nothing of interest.");

    dryer.SetDescription("A standard dryer.");
    dryer.SetExamine("You search the dryer but find nothing of interest.");

    recycling.SetDescription("A 35-gallon trash bin containing miscellaneous recycling.");
    recycling.SetExamine("The recycling bin consists largely of soda cans.");

    fan.SetDescription("An industrial fan.");
    fan.SetExamine("It looks somewhat old, but still (not anymore!) in decent operating condition.\n");

    misc.SetDescription("An assortment of various items.");
    misc.SetExamine("You find computer components, extension cords, a vacuum,\n"
                    "and various small boxes.");

    curtain.SetDescription("Some basic curtains forming a makeshift wall separating the Basement Hallway\n"
                           "from the Main Basement.");
    curtain.SetExamine("The curtain is hung from a bar spanning between walls,\n"
                       "held in place by pressure. It's currently blocking the way east.");

    // Add Events //
    northDoor.Event(OPEN, &DefaultOpenDoorEvent);
    northDoor.Event(CLOSE, &DefaultCloseDoorEvent);

    westDoor.Event(OPEN, &DefaultOpenDoorEvent);
    westDoor.Event(CLOSE, &DefaultCloseDoorEvent);

    curtain.Event(OPEN, &curtain_Open);

    washer.Event(OPEN, &washer_Open);
    //washer.Event(CLOSE, &washer_Close);
    washer.Event(USE, &washer_Use);

    /*
    dryer.Event(OPEN, &dryer_Open);
    dryer.Event(CLOSE, &dryer_Close);
    dryer.Event(USE, &dryer_Use);
    */

    // Add Objects //
    room->AddObject(northDoor);
    room->AddObject(westDoor);
    room->AddObject(floor);
    room->AddObject(washer);
    room->AddObject(dryer);
    room->AddObject(recycling);
    room->AddObject(fan);
    room->AddObject(misc);
    room->AddObject(curtain);

    // Place Objects //
    room->PlaceObject(NORTH_DOOR, Obj::Coords(3, 0));

    room->PlaceObject(WEST_DOOR, Obj::Coords(0, 1));

    room->PlaceObject(FLOOR, Obj::Coords(7, 1));

    room->PlaceObject(WASHER, Obj::Coords(2, 2));
    room->PlaceObject(RECYCLING, Obj::Coords(4, 2));
    room->PlaceObject(FAN, Obj::Coords(3, 2));
    room->PlaceObject(DRYER, Obj::Coords(5, 2));

    room->PlaceObject(MISC, Obj::Coords(1, 2));
    room->PlaceObject(CURTAIN, Obj::Coords(6, 1));
    room->PlaceObject(CURTAIN, Obj::Coords(6, 2));
    room->PlaceObject(MISC, Obj::Coords(7, 2));

    // Other //
    room->SetLock(EAST, LOCKED);
}

////////////
// EVENTS //
////////////

// Curtain //
static void curtain_Open(Obj::Template* obj)
{
    obj->GetRoomPointer()->PlaceObject(FLOOR, Obj::Coords(6, 1));
    
    obj->GetRoomPointer()->SetLock(EAST, UNLOCKED);
    obj->Event(OPEN, &DefaultOpenEvent);

    obj->SetExamine("The curtain is hung from a bar spanning between walls, held in place by pressure.");

    cout << "You open the curtain." << endl << endl;
    cout << "-- " << obj->GetRoomPointer()->GetName() << " --" << endl;
    obj->GetRoomPointer()->DisplayRoom();
}


// Washing Machine //
static void washer_Open(Obj::Template* obj)
{
    bool gotAnswer = false;
    string answer;

    if (didLaundry)
    {
        if (!gotKey)
        {
            cout << "The key still remains hidden amidst the clothing." << endl;
            while (!gotAnswer)
            {
                cout << "Reach in and grab the key? y/n: ";
                getline(cin, answer);

                if (_stricmp(answer.c_str(), "Y") == 0)
                {
                    gotAnswer = true;
                    WasherBattle();
                }
                else if (_stricmp(answer.c_str(), "N") == 0)
                {
                    gotAnswer = true;
                    cout << "You decide to leave the key for now and close the washing machine.";
                    washer_IsOpen = false;
                }
            }
        }
        else
        {
            cout << "There's nothing but wet clothing inside.";
        }
    }
    else
    {
        cout << "You can't open that.";
    }
}

static void washer_Close(Obj::Template* obj)
{
    if (washer_IsOpen)
    {
        washer_IsOpen = false;
        cout << "You close the washing machine.";
    }
    else
    {
        cout << "The washing machine is already closed.";
    }
}

static void WasherBattle();
static void washer_Use(Obj::Template* obj)
{
    bool gotAnswer = false;
    string answer;

    if (inventory.HasItem(DIRTY_LAUNDRY))
    {
        inventory.RemoveItem(DIRTY_LAUNDRY);
        cout << "You begin putting the dirty laundry in the washing machine" << endl
             << "when you happen to notice a key fall out of one of the pockets." << endl << endl;

        while (!gotAnswer)
        {
            cout << "Reach in and grab the key? y/n: ";
            getline(cin, answer);

            if (_stricmp(answer.c_str(), "Y") == 0)
            {
                gotAnswer = true;
                WasherBattle();
            }
            else if (_stricmp(answer.c_str(), "N") == 0)
            {
                gotAnswer = true;
                cout << "You decide to leave the key for now and close the washing machine.";
                washer_IsOpen = false;
            }
        }

        didLaundry = true;
    }
    else
    {
        cout << "You have nothing to use with the washing machine.";
    }
}

////////////////////
// SPECIAL EVENTS //
////////////////////

static void WasherBattle()
{
    bool gotAnswer = false;
    bool endBattle = false;
    bool playerWon = false;
    bool escaped = false;

    const unsigned int DEFENSE_LOWER_AMT = 10;

    unsigned int enemyDefense = 20;
    unsigned int damage = 0;

    string answer;

    Character::Template clothing;

    clothing.SetCharacterName("Tex Tile");
    clothing.SetMaxHealth(150);
    clothing.SetCurrentHealth(150);

    cout << endl;
    cout << "The key becomes lost amongst the clothing!" << endl << endl;

    cout << "---- Battle Start ----" << endl << endl;

    while (!endBattle)
    {
        cout << "Your health: " << player.GetCurrentHealth() << "/" << player.GetMaxHealth() << endl;
        cout << clothing.GetCharacterName() << "'s health: " << clothing.GetCurrentHealth() << "/" << clothing.GetMaxHealth() << endl;
        cout << clothing.GetCharacterName() << "'s defense: " << enemyDefense << endl;
        cout << endl;
        cout << "You must find the key!" << endl;
        cout << endl;
        cout << "1) Shift Clothing | 2) Dig Around" << endl;
        cout << "---------------------------------" << endl;
        cout << "3) Hit the Washer | 4) Try to run" << endl;
        cout << endl;

        gotAnswer = false;
        srand((unsigned int)time(NULL));
        // Player Attack //
        while (!gotAnswer)
        {
            cout << "What do you do? Number: ";
            getline(cin, answer);

            if (_stricmp(answer.c_str(), "1") == 0)
            {
                damage = 15;
                damage += rand() % 6;

                if (((signed)damage - (signed)enemyDefense) < 0)
                    damage = 0;
                else
                    damage -= enemyDefense;

                clothing.DamageCharacter(damage);
                cout << "You do " << damage << " damage to " << clothing.GetCharacterName() << "." << endl;
                gotAnswer = true;
            }
            else if (_stricmp(answer.c_str(), "2") == 0)
            {
                damage = rand() % 50 + 1;

                if (((signed)damage - (signed)enemyDefense) < 0)
                    damage = 0;
                else
                    damage -= enemyDefense;

                clothing.DamageCharacter(damage);
                cout << "You do " << damage << " damage to " << clothing.GetCharacterName() << "." << endl;
                gotAnswer = true;
            }
            else if (_stricmp(answer.c_str(), "3") == 0)
            {
                cout << "You hit the washing machine, lowering " << clothing.GetCharacterName() << "'s defense." << endl;
                

                if ((signed)enemyDefense - (signed)DEFENSE_LOWER_AMT >= 0)
                {
                    cout << "You lower " << clothing.GetCharacterName() << "'s defense by " << DEFENSE_LOWER_AMT << "." << endl;
                    enemyDefense -= DEFENSE_LOWER_AMT;
                }
                else
                {
                    cout << clothing.GetCharacterName() << "'s defense can't go any lower." << endl;
                }

                gotAnswer = true;
            }
            else if (_stricmp(answer.c_str(), "4") == 0)
            {
                cout << "You attempt to escape..." << endl;

                if ((rand() % 2) == 0)
                {
                    cout << "You successfully escape." << endl << endl;
                    escaped = true;
                }
                else
                {
                    cout << "You failed to escape." << endl;
                }
                gotAnswer = true;
            }
        }
        ///////////////////

        if (escaped)
        {
            endBattle = true;
            playerWon = false;
            continue;
        }

        if (clothing.GetStatus() == DEAD)
        {
            endBattle = true;
            playerWon = true;
            continue;
        }

        srand((unsigned int)time(NULL));
        // Enemy Attack //
        switch (rand() % 3)
        {
        case 0:
            srand((unsigned int)time(NULL));
            cout << clothing.GetCharacterName() << " uses tangled pantlegs." << endl;

            damage = 10;
            damage += rand() % 11;

            break;

        case 1:
            srand((unsigned int)time(NULL));
            cout << clothing.GetCharacterName() << " uses falling washing machine lid." << endl;
            damage = rand() % 30 + 1;

            break;

        case 2:
            srand((unsigned int)time(NULL));
            cout << clothing.GetCharacterName() << " uses splash of cold water." << endl;
            damage = rand() % 10 + 1;

            break;
        }       

        cout << clothing.GetCharacterName() << " does " << damage << " damage to you." << endl;

        player.DamageCharacter(damage);

        if (player.GetStatus() == DEAD)
        {
            endBattle = true;
            playerWon = false;
            continue;
        }
    }

    if (playerWon)
    {
        cout << "You defeated " << clothing.GetCharacterName() << " and got the key." << endl
             << "Maybe Brett will know what the key is for." << endl << endl;
        inventory.AddItem(Inv::Item(BRETTS_UNKNOWN_KEY, "Unknown Key"));
        gotKey = true;
    }
    else if (!escaped)
    {
        cout << "You have been defeated." << endl << endl;
    }

    cout << "----- Battle End -----";
}