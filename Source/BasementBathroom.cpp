#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"
#include "DefaultObjEvents.hpp"
using namespace std;

static enum OBJECTS { NO_OBJECT, NORTH_DOOR, EAST_DOOR, BATH_TUB, SHOWER_HEAD, TOILET, SINK };

void BuildBasementBathroom(Room::Template* room)
{   
    // Create Objects //
    Obj::Template northDoor("North Door", '#', NORTH_DOOR);
    Obj::Template eastDoor("East Door", '#', EAST_DOOR);
    Obj::Template bathTub("Bath Tub", '0', BATH_TUB);
    Obj::Template showerHead("Shower Head", '*', SHOWER_HEAD);
    Obj::Template toilet("Toilet", (char)234, TOILET);
    Obj::Template sink("Sink", (char)164, SINK);

    // Describe Room //
    room->SetDescription("The room looks surprisingly good for a bathroom in the basement.\n"
                         "The floor is linoleum.");

    // Describe Objects //
    northDoor.SetDescription("A featureless wooden door that leads to the Basement Storage.");
    northDoor.SetExamine("You search the door but find nothing of interest.");

    eastDoor.SetDescription("A featureless wooden door that leads to the Basement Hallway.");
    eastDoor.SetExamine("You search the door but find nothing of interest.");

    bathTub.SetDescription("A mundane bathtub with an annoyingly steep back, making it difficult to truly\n"
                           "relax in.");
    bathTub.SetExamine("Other than a flat rubber stopper, you find nothing in the bath tub.");

    showerHead.SetDescription("A simple removable showerhead.");
    showerHead.SetExamine("Closer examination reveals a series of settings, but nothing more.");

    toilet.SetDescription("A toilet with a seat slightly smaller than the usual toilet.");
    toilet.SetExamine("The fuck is wrong with you?");

    sink.SetDescription("A bowl-shaped sink with some small shelves along either side.");
    sink.SetExamine("Aside from some lime deposits there is nothing in the sink.");

    // Add Objects //
    room->AddObject(northDoor);
    room->AddObject(eastDoor);
    room->AddObject(bathTub);
    room->AddObject(showerHead);
    room->AddObject(toilet);
    room->AddObject(sink);

    // Place Objects //
    room->PlaceObject(NORTH_DOOR, Obj::Coords(2, 0));
    room->PlaceObject(EAST_DOOR, Obj::Coords(4, 1));
    room->PlaceObject(BATH_TUB, Obj::Coords(1, 1));
    room->PlaceObject(SHOWER_HEAD, Obj::Coords(1, 2));
    room->PlaceObject(TOILET, Obj::Coords(2, 2));
    room->PlaceObject(SINK, Obj::Coords(3, 2));
}