#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"
#include "DefaultObjEvents.hpp"
using namespace std;

static enum OBJECTS { NO_OBJECT, EAST_DOOR, OPEN_DOORWAY, BED, TV, FLOOR_LIGHT, CAT, FLOOR };

static bool lightIsOn = false;

// Event forward declarations //
static void floorLight_Use(Obj::Template* obj);
static void cat_Take(Obj::Template* obj);
static void cat_Talk(Obj::Template* obj);

void BuildBrettsRoom(Room::Template* room)
{
    // Create Objects //
    Obj::Template eastDoor("East Door", '#', EAST_DOOR);
    Obj::Template openDoor("Open Doorway", '/', OPEN_DOORWAY);
    Obj::Template bed("Bed", (char)206, BED);
    Obj::Template tv("Television", (char)127, TV);
    Obj::Template floorLight("Floor Light", (char)15, FLOOR_LIGHT);
    Obj::Template cat("Cat", 'c', CAT);
    Obj::Template floor("", (char)32, FLOOR);

    // Describe Room //
    room->SetDescription("A relatively comfortably-sized and furnished bedroom.\n"
                         "The floor is carpet.");

    // Describe Objects //
    eastDoor.SetDescription("An old wooden door with a vintage style keyhole.\n"
                            "This door leads to the Hallway");
    eastDoor.SetExamine("You search the door but find nothing of interest.");

    openDoor.SetDescription("An open doorway which enters into a walk-in closet.");
    openDoor.SetExamine("You search around the doorframe but find nothing of interest.");

    bed.SetDescription("A standard queen-sized bed.");
    bed.SetExamine("You search the bed but find nothing of interest.");

    tv.SetDescription("A moderately large-sized flat-screen TV.");
    tv.SetExamine("You examine the TV but find nothing of interest.");

    floorLight.SetDescription("A tall floor light.");
    floorLight.SetExamine("You search the floor light but find nothing of interest.");

    cat.SetDescription("A large orange cat known as Spaz.");
    cat.SetExamine("The cat notices that you're paying attention to it and approaches you,\n"
                   "looking for even more.");

    // Add Events //
    floorLight.Event(USE, &floorLight_Use);
    cat.Event(TAKE, &cat_Take);
    cat.Event(TALK, &cat_Talk);

    // Add Objects //
    room->AddObject(eastDoor);
    room->AddObject(openDoor);
    room->AddObject(bed);
    room->AddObject(tv);
    room->AddObject(floorLight);
    room->AddObject(cat);
    room->AddObject(floor);

    // Place Objects //
    room->PlaceObject(EAST_DOOR, Obj::Coords(6, 1));
    room->PlaceObject(OPEN_DOORWAY, Obj::Coords(3, 0));

    room->PlaceObject(TV, Obj::Coords(1, 1));

    room->PlaceObject(BED, Obj::Coords(5, 3));
    room->PlaceObject(BED, Obj::Coords(5, 4));
    room->PlaceObject(BED, Obj::Coords(4, 3));
    room->PlaceObject(BED, Obj::Coords(4, 4));
    room->PlaceObject(BED, Obj::Coords(3, 3));
    room->PlaceObject(BED, Obj::Coords(3, 4));

    room->PlaceObject(FLOOR_LIGHT, Obj::Coords(5, 2));

    room->PlaceObject(CAT, Obj::Coords(1, 3));
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

static void cat_Take(Obj::Template* obj)
{
    Room::Template* roomPtr = obj->GetRoomPointer();
    cout << "You take the cat." << endl << endl;
    inventory.AddItem(Inv::Item(CAT_SPAZ, "Cat"));
    
    roomPtr->PlaceObject(FLOOR, Obj::Coords(1, 3));

    cout << "-- " << roomPtr->GetName() << " --" << endl;
    roomPtr->DisplayRoom();

    roomPtr->RemoveObject(CAT);
}

static void cat_Talk(Obj::Template* obj)
{
    cout << "'Meo-eow' .. The cat has a strange meow.";
}