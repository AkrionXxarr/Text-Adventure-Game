#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"
#include "DefaultObjEvents.hpp"
using namespace std;

static enum OBJECTS { NO_OBJECT, OPEN_DOORWAY, BOX };

void BuildMichaelsCloset(Room::Template* room)
{
    // Create Objects //
    Obj::Template openDoor("", '/', OPEN_DOORWAY);
    Obj::Template box("Box", (char)254, BOX);

    // Describe Room //
    room->SetDescription("A small closet that's clearly of an older design, for it has a door\n"
                         "like a walk-in closet but not the space.");

    // Describe Objects //
    openDoor.SetDescription("An open doorway that leads into Michael's room.");
    openDoor.SetExamine("You search around the doorframe but find nothing of interest.");

    box.SetDescription("A box of crap.");
    box.SetExamine("You begin searching the box but Michael has gotten fed up with you in his\n"
                   "room and his attempts to get you to leave distract you from finding anything\n"
                   "of interest.");

    // Add Objects //
    room->AddObject(openDoor);
    room->AddObject(box);

    // Place Objects //
    room->PlaceObject(OPEN_DOORWAY, Obj::Coords(0, 1));
    room->PlaceObject(BOX, Obj::Coords(1, 1));
}