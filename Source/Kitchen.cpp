#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"
#include "DefaultObjEvents.hpp"
using namespace std;

static enum OBJECTS { NO_OBJECT, STAIRS_DOWN, OPEN_DOORWAY, TOP_HALF_WALL, FRIDGE, SINK, DISH_WASHER, STOVE, COUNTER, TABLE };

bool usedFridge = false;

// Event forward declarations //
static void fridge_Use(Obj::Template* obj);

void BuildKitchen(Room::Template* room)
{
    // Create Objects //
    Obj::Template stairsDown("Stairs Down", (char)31, STAIRS_DOWN);
    Obj::Template openDoor("Open Doorway", '/', OPEN_DOORWAY);
    Obj::Template fridge("Fridge", (char)178, FRIDGE);
    Obj::Template sink("Kitchen Sink", (char)165, SINK);
    Obj::Template dishWasher("Dish Washer", 'D', DISH_WASHER);
    Obj::Template stove("Stove", (char)228, STOVE);
    Obj::Template counter("Counter", '[', COUNTER);
    Obj::Template table("Susan's Table", (char)209, TABLE);

    // Describe Room //
    room->SetDescription("A pretty standard looking kitchen. There's a microwave/broiler combo\n"
                         "sitting on the counter nearest the stairs which looks significantly newer \n"
                         "than the majority of kitchen appliances in the room.\n"
                         "The floor is linoleum.");

    // Describe Objects //
    stairsDown.SetDescription("A short 4-step staircase beginning just after a doorway.\n"
                              "The stairs lead down to a Landing.\n");
    stairsDown.SetExamine("You don't find anything of interest.");

    openDoor.SetDescription("An open doorway that leads to the Dining Room.");
    openDoor.SetExamine("You search around the doorframe but find nothing of interest.");

    fridge.SetDescription("A standard refridgerator.");
    fridge.SetExamine("You search the refridgerator, but you only find a bunch of word magnets.");

    sink.SetDescription("A typical kitchen sink with a removable faucet head.");
    sink.SetExamine("Aside from some dishes there's nothing in the sink that catches your eye.");

    dishWasher.SetDescription("An old, cheap dishwasher.");
    dishWasher.SetExamine("You examine the dish washer but find nothing of interest.");

    stove.SetDescription("An old beat up stove. It doesn't look to be in the best of\n"
                         "operating conditions.");
    stove.SetExamine("You examine the stove and find all sorts of gunk typical to an old stove.");

    counter.SetDescription("A typical kitchen counter.");
    counter.SetExamine("You examine the counter but find nothing of interest.");

    table.SetDescription("A dining table being used as a computer desk.");
    table.SetExamine("The table is covered in non-dining related stuff, and a computer.");

    // Add Events //
    fridge.Event(USE, &fridge_Use);

    // Add Objects //
    room->AddObject(stairsDown);
    room->AddObject(openDoor);
    room->AddObject(Obj::Template("", (char)223, TOP_HALF_WALL));
    room->AddObject(fridge);
    room->AddObject(sink);
    room->AddObject(dishWasher);
    room->AddObject(stove);
    room->AddObject(counter);
    room->AddObject(table);

    // Place Objects //
    room->PlaceObject(TOP_HALF_WALL, Obj::Coords(1, 2));

    room->PlaceObject(STAIRS_DOWN, Obj::Coords(2, 7));
    room->PlaceObject(OPEN_DOORWAY, Obj::Coords(0, 3));

    room->PlaceObject(COUNTER, Obj::Coords(4, 6));
    room->PlaceObject(DISH_WASHER, Obj::Coords(4, 5));
    room->PlaceObject(SINK, Obj::Coords(4, 4));
    room->PlaceObject(COUNTER, Obj::Coords(4, 3));

    room->PlaceObject(FRIDGE, Obj::Coords(1, 4));
    room->PlaceObject(STOVE, Obj::Coords(1, 5));

    room->PlaceObject(TABLE, Obj::Coords(2, 1));
    room->PlaceObject(TABLE, Obj::Coords(3, 1));
}

////////////
// EVENTS //
////////////
static void fridge_Use(Obj::Template* obj)
{
    bool gotAnswer = false;

    string answer;

    while (!gotAnswer)
    {
        cout << "Would you like to eat something? y/n: ";
        getline(cin, answer);

        if (_stricmp(answer.c_str(), "Y") == 0)
        {
            if (usedFridge)
            {
                cout << "There's nothing left to eat.";
            }
            else
            {
                cout << "You eat some food..." << endl;
                player.SetMaxHealth(player.GetMaxHealth() + 20);
                player.SetCurrentHealth(player.GetMaxHealth());
                cout << "Your max health has increased by 20 points.";
                usedFridge = true;
            }

            gotAnswer = true;
        }
        else if (_stricmp(answer.c_str(), "N") == 0)
        {
            cout << "You step away from the fridge.";

            gotAnswer = true;
        }
    }
}