#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"
#include "DefaultObjEvents.hpp"
using namespace std;

static enum OBJECTS { NO_OBJECT, SOUTH_DOOR, BOXES };

void BuildBasementStorage(Room::Template* room)
{
    // Create Objects //
    Obj::Template southDoor("South Door", '#', SOUTH_DOOR);
    Obj::Template boxes("Boxes", (char)254, BOXES);

    // Describe Room //
    room->SetDescription("This room is full of various boxes and containers. You can tell it's\n"
                         "not used for anything but storage even though carpeted like a bedroom.\n"
                         "The floor is carpet.");

    // Describe Objects //
    southDoor.SetDescription("A featureless wooden door.");
    southDoor.SetExamine("You search the door but find nothing of interest.");

    boxes.SetDescription("Boxes of random crap.");
    boxes.SetExamine("Searching through the boxes you find items ranging from power tools\n"
                     "to books. There are also multiple boxes full of computer related stuff.");

    // Add Objects //
    room->AddObject(southDoor);
    room->AddObject(boxes);

    // Place Objects //
    room->PlaceObject(SOUTH_DOOR, Obj::Coords(3, 4));
    
    room->PlaceObject(BOXES, Obj::Coords(1, 1));
    room->PlaceObject(BOXES, Obj::Coords(2, 1));
    room->PlaceObject(BOXES, Obj::Coords(3, 1));
    room->PlaceObject(BOXES, Obj::Coords(1, 2));
    room->PlaceObject(BOXES, Obj::Coords(1, 3));
    room->PlaceObject(BOXES, Obj::Coords(2, 1));
    room->PlaceObject(BOXES, Obj::Coords(2, 2));
    room->PlaceObject(BOXES, Obj::Coords(2, 3));
    room->PlaceObject(BOXES, Obj::Coords(3, 1));
}