#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"
#include "DefaultObjEvents.hpp"
using namespace std;

enum OBJECTS { NO_OBJECT, SOUTH_DOOR, WEST_DOOR, EAST_DOOR, FLOOR_VENT, FLOOR };

// Event Forward Declarations //
static void westDoor_Unlock(Obj::Template* obj);

void BuildUpstairsHallway(Room::Template* room)
{
    // Create Objects //
    Obj::Template southDoor("South Door", '#', SOUTH_DOOR);
    Obj::Template westDoor("West Door", '#', WEST_DOOR);
    Obj::Template eastDoor("East Door", '#', EAST_DOOR);
    Obj::Template floorVent("Floor Vent", '"', FLOOR_VENT);
    Obj::Template floor("", (char)32, FLOOR);

    // Describe Room //
    room->SetDescription("This room seems to only barely qualify as a 'hallway'.\n"
                         "Within a space no larger than a small bathroom, there are 3 doors,\n"
                         "a large heating vent on the floor, and an opening into the Dining Room.\n"
                         "The floor is carpet.");

    // Describe Objects //
    southDoor.SetDescription("An old wooden door with a vintage style keyhole.\n"
                             "This door leads to the Bathroom");
    southDoor.SetExamine("You search the door but find nothing of interest.");

    westDoor.SetDescription("An old wooden door with a vintage style keyhole.\n"
                            "This door leads to Brett's room.");
    westDoor.SetExamine("You search the door and find that it's locked.");

    eastDoor.SetDescription("An old wooden door with a vintage style keyhole.\n"
                            "This door leads to Michael's room");
    eastDoor.SetExamine("You search the door but find nothing of interest.");

    floorVent.SetDescription("A 2 foot by 1 1/2 foot wooden grate heating vent on the floor.");
    floorVent.SetExamine("You search the floor vent but find nothing of interest.");

    // Add Events //
    westDoor.Event(UNLOCK, &westDoor_Unlock);

    // Add Objects //
    room->AddObject(southDoor);
    room->AddObject(westDoor);
    room->AddObject(eastDoor);
    room->AddObject(floorVent);
    room->AddObject(floor);

    // Place Objects //
    room->PlaceObject(SOUTH_DOOR, Obj::Coords(2, 2));
    room->PlaceObject(WEST_DOOR, Obj::Coords(0, 1));
    room->PlaceObject(EAST_DOOR, Obj::Coords(5, 1));
    room->PlaceObject(FLOOR_VENT, Obj::Coords(2, 1));
    room->PlaceObject(FLOOR, Obj::Coords(4, 0));

    // Other //
    room->SetLock(WEST, LOCKED);
}

////////////
// EVENTS //
////////////

// West Door //
static void westDoor_Unlock(Obj::Template* obj)
{
    if (obj->GetRoomPointer()->CheckLock(WEST) == LOCKED)
    {
        if (inventory.HasItem(BRETTS_BEDROOM_KEY))
        {
            obj->GetRoomPointer()->SetLock(WEST, UNLOCKED);
            cout << "You unlock the door.";
            obj->Event(UNLOCK, &DefaultUnlockEvent);
            inventory.RemoveItem(BRETTS_BEDROOM_KEY);

            obj->SetExamine("You search the door but find nothing of interest.");
        }
        else if (inventory.HasItem(BRETTS_UNKNOWN_KEY))
        {
            obj->GetRoomPointer()->SetLock(WEST, UNLOCKED);
            cout << "You try the Unknown Key on the door and it unlocks.";
            obj->Event(UNLOCK, &DefaultUnlockEvent);
            inventory.RemoveItem(BRETTS_UNKNOWN_KEY);

            obj->SetExamine("You search the door but find nothing of interest.");
        }
        else
        {
            cout << "You don't have the key to unlock the door.";
        }
    }
    else
    {
        cout << "<Error> westDoor_Unlock() in UpstairsHallway.cpp didn't trigger properly.";
    }
}