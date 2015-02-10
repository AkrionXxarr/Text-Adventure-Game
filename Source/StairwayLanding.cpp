#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"
#include "DefaultObjEvents.hpp"
using namespace std;

#include <stdlib.h>
#include <time.h>

static enum OBJECTS { NO_OBJECT, STAIRS_UP, STAIRS_DOWN, DOUBLE_DOORS };

static void doubleDoors_Examine(Obj::Template* obj)
{
    srand((unsigned int)time(NULL));

    switch (rand() % 4)
    {
    case 0:
        cout << "You look out the door and find nothing of interest.";
        break;

    case 1:
        cout << "You look out the door and find a few kittens eating at a bowl of food left\n"
                "outside.";
        break;

    case 2:
        cout << "You look out the door and find a couple racoons snacking away at the cat food.";
        break;

    case 3:
        cout << "You look out the door and find a skunk eating the cat food.";
        break;

        /*
    case 4:
        break;
        */
    }
}

void BuildStairwayLanding(Room::Template* room)
{
    // Create Objects //
    Obj::Template stairsUp("Stairs Up", (char)30, STAIRS_UP);
    Obj::Template stairsDown("Stairs Down", (char)31, STAIRS_DOWN);
    Obj::Template doubleDoors("Double Doors", (char)205, DOUBLE_DOORS);

    // Describe Room //
    room->SetDescription("The stairs briefly level out into a small landing connecting\n"
                         "to the house's back doors.\n"
                         "The floor is carpet.");

    // Describe Objects //
    stairsDown.SetDescription("A relatively steep staircase that hugs the wall;\n"
                              "it doesn't leave much in terms of height.\n"
                              "The stairs lead down to the Basement.");
    stairsDown.SetExamine("You don't find anything of interest.");

    stairsUp.SetDescription("A short 4-step staircase ending just before a doorway.\n"
                            "The stairs lead up to the Kitchen.");
    stairsUp.SetExamine("You don't find anything of interest.");

    doubleDoors.SetDescription("Two doors that lead to the outside.");

    // Add Events //
    doubleDoors.Event(EXAMINE, &doubleDoors_Examine);

    // Add Objects //
    room->AddObject(stairsUp);
    room->AddObject(stairsDown);
    room->AddObject(doubleDoors);

    // Place Objects //
    room->PlaceObject(STAIRS_UP, Obj::Coords(3, 0));
    room->PlaceObject(STAIRS_DOWN, Obj::Coords(1, 0));

    room->PlaceObject(DOUBLE_DOORS, Obj::Coords(1, 2));
    room->PlaceObject(DOUBLE_DOORS, Obj::Coords(2, 2));
    room->PlaceObject(DOUBLE_DOORS, Obj::Coords(3, 2));
}