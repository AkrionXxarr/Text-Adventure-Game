#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"
#include "DefaultObjEvents.hpp"
using namespace std;

static enum OBJECTS { NO_OBJECT, NORTH_DOOR, BATH_TUB, SHOWER_HEAD, SINK, TOILET };

void BuildUpstairsBathroom(Room::Template* room)
{
    // Create Objects //
    Obj::Template northDoor("North Door", '#', NORTH_DOOR);
    Obj::Template bathTub("Bath", '0', BATH_TUB);
    Obj::Template showerHead("Shower Head", '*', SHOWER_HEAD);
    Obj::Template sink("Sink", (char)164, SINK);
    Obj::Template toilet("Toilet", (char)234, TOILET);

    // Describe Room //
    room->SetDescription("This Bathroom is on the small side compared to your average modern bathroom.\n"
                         "The floor is linoleum.");

    // Describe Objects //
    northDoor.SetDescription("An old wooden door with a vintage style keyhole.\n"
                             "This door leads to the Hallway.");
    northDoor.SetExamine("You search the door but find nothing of interest.");

    bathTub.SetDescription("A mundane bathtub with an annoyingly steep back, making it difficult to truly\n"
                           "relax in.");
    bathTub.SetExamine("You search the bath tub but find nothing of interest.");

    showerHead.SetDescription("A simple shower head.");
    showerHead.SetExamine("You look more closely at the shower head but find nothing of interest.");

    sink.SetDescription("A bowl-shaped sink with some small shelves along either side.");
    sink.SetExamine("Aside from some lime deposits there is nothing in the sink.");

    toilet.SetDescription("A toilet with a seat slightly smaller than the usual toilet.");
    toilet.SetExamine("...Why?");

    // Add Objects //
    room->AddObject(northDoor);
    room->AddObject(bathTub);
    room->AddObject(showerHead);
    room->AddObject(sink);
    room->AddObject(toilet);

    // Place Objects //
    room->PlaceObject(NORTH_DOOR, Obj::Coords(1, 0));

    room->PlaceObject(BATH_TUB, Obj::Coords(1, 3));
    room->PlaceObject(SHOWER_HEAD, Obj::Coords(2, 3));

    room->PlaceObject(TOILET, Obj::Coords(2, 1));
    room->PlaceObject(SINK, Obj::Coords(2, 2));
}