#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"
#include "DefaultObjEvents.hpp"
using namespace std;

#include <stdlib.h>
#include <time.h>

static enum OBJECTS { NO_OBJECT, WEST_DOOR, OPEN_DOORWAY, MICHAELS_DESK, BED, PUNCHING_BAG, SMALL_SHELF, FLOOR_LIGHT, NIGHT_STAND };

static bool lightIsOn = false;
static bool usedPunchingBag = false;

// Event forward declarations //
static void punchingBag_Use(Obj::Template* obj);
static void smallShelf_Use(Obj::Template* obj);
static void floorLight_Use(Obj::Template* obj);
static void nightStand_Examine(Obj::Template* obj);

void BuildMichaelsRoom(Room::Template* room)
{
    // Create Objects //
    Obj::Template westDoor("West Door", '#', WEST_DOOR);
    Obj::Template openDoor("Open Doorway", '/', OPEN_DOORWAY);
    Obj::Template michaelsDesk("Michael's Desk", (char)209, MICHAELS_DESK);
    Obj::Template bed("Bed", (char)206, BED);
    Obj::Template punchingBag("Punching Bag", (char)233, PUNCHING_BAG);
    Obj::Template smallShelf("Small Shelf", '=', SMALL_SHELF);
    Obj::Template floorLight("Floor Light", (char)15, FLOOR_LIGHT);
    Obj::Template nightStand("Night Stand", (char)243, NIGHT_STAND);

    // Describe Room //
    room->SetDescription("A relatively comfortably-sized and furnished bedroom.\n"
                         "The floor is carpet.");

    // Describe Objects //
    westDoor.SetDescription("An old wooden door with a vintage style keyhole."
                            "This door leads to the Hallway.");
    westDoor.SetExamine("You search the door but find nothing of interest.");

    openDoor.SetDescription("An open doorway which leads into a small closet.");
    openDoor.SetExamine("You search around the doorframe but find nothing of interest.");

    michaelsDesk.SetDescription("A long computer desk with a glass top.");
    michaelsDesk.SetExamine("There's a couple large cracks in the glass, must be entirely the fault\n"
                            "of the desk's current owner. SO DESTRUCTIVE.");

    bed.SetDescription("A low black futon.");
    bed.SetExamine("You search the bed but find nothing of interest.");

    punchingBag.SetDescription("A black punching back hanging from a black frame which nearly reaches\n"
                               "the ceiling.");
    punchingBag.SetExamine("You search the punching bag but find nothing of interest.");

    smallShelf.SetDescription("Black shelves that stand roughly 3 1/2 feet wide and stand from\n"
                              "floor to ceiling.");
    smallShelf.SetExamine("You find a stack of networking equipment,\n"
                          "but little else that catches your eye.");

    floorLight.SetDescription("A tall floor light.");
    floorLight.SetExamine("You search the floor light but find nothing of interest.");

    nightStand.SetDescription("A small metal and glass night stand. A laptop sits on top of it.");
    nightStand.SetExamine("You take a closer look at the laptop and find it to be Michael's Alienware.");

    // Add Events //
    punchingBag.Event(USE, &punchingBag_Use);
    smallShelf.Event(USE, &smallShelf_Use);
    floorLight.Event(USE, &floorLight_Use);
    nightStand.Event(EXAMINE, &nightStand_Examine);

    // Add Objects //
    room->AddObject(westDoor);
    room->AddObject(openDoor);
    room->AddObject(michaelsDesk);
    room->AddObject(bed);
    room->AddObject(punchingBag);
    room->AddObject(smallShelf);
    room->AddObject(floorLight);
    room->AddObject(nightStand);

    // Place Objects //
    room->PlaceObject(WEST_DOOR, Obj::Coords(0, 1));
    room->PlaceObject(OPEN_DOORWAY, Obj::Coords(6, 5));

    room->PlaceObject(MICHAELS_DESK, Obj::Coords(2, 5));
    room->PlaceObject(MICHAELS_DESK, Obj::Coords(3, 5));
    room->PlaceObject(MICHAELS_DESK, Obj::Coords(4, 5));

    room->PlaceObject(PUNCHING_BAG, Obj::Coords(5, 4));

    room->PlaceObject(SMALL_SHELF, Obj::Coords(1, 3));

    room->PlaceObject(BED, Obj::Coords(5, 1));
    room->PlaceObject(BED, Obj::Coords(4, 1));

    room->PlaceObject(NIGHT_STAND, Obj::Coords(5, 2));

    room->PlaceObject(FLOOR_LIGHT, Obj::Coords(5, 5));
}

////////////
// EVENTS //
////////////
static void punchingBag_Use(Obj::Template* obj)
{
    bool gotAnswer = false;

    string answer;

    if (usedPunchingBag)
    {
        cout << "The punching bag is tired, you shouldn't bother it anymore.";
    }
    else
    {
        while (!gotAnswer)
        {
            cout << "Take some swings at the punching bag? y/n: ";
            getline(cin, answer);

            if (_stricmp(answer.c_str(), "Y") == 0)
            {
                cout << "You spend a few minutes taking some swings at the punching bag." << endl;
                player.SetMaxHealth(player.GetMaxHealth() + 10);
                player.SetCurrentHealth(player.GetMaxHealth());
                cout << "You feel stronger, your max health has increased by 10 points";  

                usedPunchingBag = true;
                gotAnswer = true;
            }
            else if (_stricmp(answer.c_str(), "N") == 0)
            {
                cout << "You leave the punching bag alone.";

                gotAnswer = true;
            }
        }
    }
}

static void smallShelf_Use(Obj::Template* obj)
{
    cout << "You could turn off the network, but that would put the whole house into an" << endl
         << "unstoppable frenzy.";
}

static void floorLight_Use(Obj::Template* obj)
{
    if (lightIsOn)
    {
        cout << "You turn the light off.";
    }
    else
    {
        cout << "You turn the light on.";
    }
}

static void MichaelBattle();
static void nightStand_Examine(Obj::Template* obj)
{
    bool gotAnswer = false;

    string answer;

    cout << "You take a closer look at the night stand and find Michael's Alienware." << endl
         << "This is what you've set out to get." << endl << endl;

    while (!gotAnswer)
    {
        cout << "Take the laptop? y/n: ";
        getline(cin, answer);

        if (_stricmp(answer.c_str(), "Y") == 0)
        {
            cout << "You pick up the laptop." << endl;
            MichaelBattle();
            gotAnswer = true;
        }
        else if (_stricmp(answer.c_str(), "N") == 0)
        {
            cout << "You leave the laptop alone.";
            gotAnswer = true;
        }
    }
}

////////////////////
// SPECIAL EVENTS //
////////////////////

static void MichaelBattle()
{
    bool gotAnswer = false;
    bool endBattle = false;
    bool playerWon = false;

    unsigned int damage = 0;
    unsigned int moistDamage = 100;

    string answer;

    Character::Template michael;

    michael.SetCharacterName("Michael");
    michael.SetMaxHealth(1000);
    michael.SetCurrentHealth(1000);

    cout << endl;
    cout << "A wild Michael has appeared!" << endl << endl;

    cout << michael.GetCharacterName() << " says: The fuck are you doing with that?" << endl;
    cout << michael.GetCharacterName() << " has taken the form of.." << endl;
    michael.SetCharacterName("Erik the Red");
    cout << michael.GetCharacterName() << "!" << endl << endl;

    cout << "---- Battle Start ----" << endl << endl;

    if (inventory.HasItem(CAT_SPAZ))
    {
        cout << "Spaz appears to have taken a keen interest in " << michael.GetCharacterName() << endl
             << "You decide to throw the cat at him. As Spaz flies through the air he aims" << endl
             << "straight for " << michael.GetCharacterName() << "'s nose and bites down. It's super effective!" << endl
             << "Spaz hits " << michael.GetCharacterName() << " for 800 damage." << endl << endl;

        michael.DamageCharacter(800);
    }

    while (!endBattle)
    {
        cout << "Your health: " << player.GetCurrentHealth() << "/" << player.GetMaxHealth() << endl;
        cout << michael.GetCharacterName() << "'s health: " << michael.GetCurrentHealth() << "/" << michael.GetMaxHealth() << endl;
        cout << endl;
        cout << endl;
        cout << "1) Talk about Mathematics | 2) Call him 'short'" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "3) Talk about Programming | 4) Say 'Moist'" << endl;
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
                cout << "You begin a discussion about various math-related topics." << endl;

                damage = 20;
                damage += rand() % 6;

                michael.DamageCharacter(damage);
                cout << "You do " << damage << " damage to " << michael.GetCharacterName() << "." << endl;
                gotAnswer = true;
            }
            else if (_stricmp(answer.c_str(), "2") == 0)
            {
                cout << "You call " << michael.GetCharacterName() << " short." << endl;

                switch (rand() % 4)
                {
                case 0:
                case 1:
                    cout << "The attack misses." << endl;
                    damage = 0;
                    break;

                case 2:
                case 3:
                    cout << "The attack strikes a glancing blow." << endl;

                    srand((unsigned int)time(NULL));
                    damage = rand() % 11;

                    break;

                case 4:
                    cout << "The attack is devistating." << endl;

                    srand((unsigned int)time(NULL));
                    damage = 75;
                    damage = rand() % 76;

                    break;
                }

                michael.DamageCharacter(damage);
                cout << "You do " << damage << " damage to " << michael.GetCharacterName() << "." << endl;
                gotAnswer = true;
            }
            else if (_stricmp(answer.c_str(), "3") == 0)
            {
                cout << "You begin a discussion about various programming-related topics." << endl;

                damage = rand() % 60 + 1;

                michael.DamageCharacter(damage);
                cout << "You do " << damage << " damage to " << michael.GetCharacterName() << "." << endl;
                gotAnswer = true;
            }
            else if (_stricmp(answer.c_str(), "4") == 0)
            {
                cout << "You say 'Moist' .. This appears to bother " << michael.GetCharacterName() << "." << endl;

                michael.DamageCharacter(moistDamage);
                cout << "You do a set " << moistDamage << " damage to " << michael.GetCharacterName() << "." << endl;
                cout << "The attack won't be as effective next time." << endl;

                if (moistDamage - 10 > 0)
                    moistDamage -= 25;

                gotAnswer = true;
            }
        }
        ///////////////////

        if (michael.GetStatus() == DEAD)
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
            cout << michael.GetCharacterName() << " uses Jesus Fucking Christ." << endl;

            damage = 15;
            damage += rand() % 6;

            break;

        case 1:
            srand((unsigned int)time(NULL));
            cout << michael.GetCharacterName() << " uses Holy Fucking Shit." << endl;
            damage = rand() % 40 + 1;

            break;

        case 2:
            srand((unsigned int)time(NULL));
            cout << michael.GetCharacterName() << " uses Shut The Fuck Up." << endl;
            damage = rand() % 10 + 1;

            break;
        }       

        cout << michael.GetCharacterName() << " does " << damage << " damage to you." << endl;

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
        cout << "You defeated " << michael.GetCharacterName() << " and kept the laptop!" << endl << endl;
        wonGame = true;
    }
    else
    {
        cout << "You have been defeated." << endl << endl;
    }

    cout << "----- Battle End -----";
}