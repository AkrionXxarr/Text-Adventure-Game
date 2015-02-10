#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"

static enum OBJECTS { NO_OBJECT, OPEN_DOORWAY, LARGE_SHELF, BOX, FULL_WALL };

void BuildBrettsCloset(Room::Template* room)
{
    // Create Objects //
    Obj::Template openDoor("Open Doorway", '/', OPEN_DOORWAY);
    Obj::Template largeShelf("Large Shelf", (char)240, LARGE_SHELF);
    Obj::Template box("Box", (char)254, BOX);

    // Describe Room //
    room->SetDescription("It's a small walk-in closet.\n"
                         "The floor is carpet.");

    // Describe Objects //
    openDoor.SetDescription("An open doorway that leads into Brett's room.");
    openDoor.SetExamine("You search around the doorframe but find nothing of interest.");

    largeShelf.SetDescription("A series of large wooden shelves are up against the wall.");
    largeShelf.SetExamine("You search the large shelf but find nothing of interest.");

    box.SetDescription("A box of crap.");
    box.SetExamine("You search the box but find nothing of interest.");

    // Add Objects //
    room->AddObject(openDoor);
    room->AddObject(largeShelf);
    room->AddObject(box);
    room->AddObject(Obj::Template("", (char)219, FULL_WALL));

    // Place Objects //
    room->PlaceObject(OPEN_DOORWAY, Obj::Coords(2, 3));

    room->PlaceObject(LARGE_SHELF, Obj::Coords(1, 1));
    room->PlaceObject(LARGE_SHELF, Obj::Coords(2, 1));

    room->PlaceObject(BOX, Obj::Coords(3, 2));

    room->PlaceObject(FULL_WALL, Obj::Coords(3, 1));
}
