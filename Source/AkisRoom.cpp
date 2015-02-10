#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"
#include "DefaultObjEvents.hpp"
using namespace std;

static enum OBJECTS { NO_OBJECT, SOUTH_DOOR, BED, SMALL_SHELF, TV, AKI_DESK, AKI_CHAIR, VY_DESK, VY_CHAIR, RIGHT_HALF_WALL, BOTTOM_HALF_WALL };

// Event forward declarations //
static void bed_Use(Obj::Template* obj);

void BuildAkisRoom(Room::Template* room)
{
    // Create Objects //
    Obj::Template southDoor("South Door", '#', SOUTH_DOOR);
    Obj::Template bed("Bed", (char)206, BED);
    Obj::Template shelf("Small Shelf", '=', SMALL_SHELF);
    Obj::Template tv("Television", (char)127, TV);
    Obj::Template akiDesk("Akrion's desk", (char)209, AKI_DESK);
    Obj::Template akiChair("Akrion's chair", (char)147, AKI_CHAIR);
    Obj::Template vyDesk("Siivyra's desk", (char)203, VY_DESK);
    Obj::Template vyChair("Siivyra's chair", (char)148, VY_CHAIR);

    // Describe Room //
    room->SetDescription("A relatively cramped room;\n"
                         "there is little that doesn't utilize all available space.\n"
                         "The floor is carpet and hair.");

    // Describe Objects //
    southDoor.SetDescription("A featureless wooden door that leads to the Basement Hallway.");
    southDoor.SetExamine("You search the door but find nothing of interest.");

    bed.SetDescription("A full size bed; you can rest in it to restore your health.");
    bed.SetExamine("You examine the bed and find the mattress is a foam mattress unlike\n"
                   "the typical spring mattress one might expect.\n"
                   "You find nothing else of interest.");

    shelf.SetDescription("Two 3 foot high white shelves stand side by side atop a series of\n"
                         "white end tables.");
    shelf.SetExamine("Closer examination of the shelves reveals plethora of miscellaneous items.");

    tv.SetDescription("A 28 inch flat-tube television.");
    tv.SetExamine("Turning on the television you notice the screen is misaligned.\n"
                  "All attempts to fix the misalignment are unsuccessful.");

    akiDesk.SetDescription("A black computer desk with metal legs and a wood top.");
    akiDesk.SetExamine("Two wide screen monitors, a blank Unicomp keyboard, and a Sidewinder mouse \n"
                       "share the desk with a random assortment of cans and bottles.");

    akiChair.SetDescription("A moderately small, black, torn-the-fuck-up office chair.");
    akiChair.SetExamine("You search the chair but find nothing of interest.");

    vyDesk.SetDescription("A beige computer desk with wood legs and wood top.");
    vyDesk.SetExamine("The wide screen / normal screen setup on this desk is rather uninteresting \n"
                      "when next to them rests a 50 gallon fish tank containing a Jungle Carpet Python.");

    vyChair.SetDescription("A large black office chair.");
    vyChair.SetExamine("You search the chair but find nothing of interest.");

    // Add Events //
    southDoor.Event(OPEN, &DefaultOpenDoorEvent);
    southDoor.Event(CLOSE, &DefaultCloseDoorEvent);

    bed.Event(USE, &bed_Use);

    // Add Objects //
    room->AddObject(southDoor);
    room->AddObject(bed);
    room->AddObject(shelf);
    room->AddObject(tv);
    room->AddObject(akiDesk);
    room->AddObject(akiChair);
    room->AddObject(vyDesk);
    room->AddObject(vyChair);
    room->AddObject(Obj::Template("", (char)222, RIGHT_HALF_WALL));
    room->AddObject(Obj::Template("", (char)220, BOTTOM_HALF_WALL));


    // Place Objects //
    room->PlaceObject(RIGHT_HALF_WALL, Obj::Coords(5, 3));
    room->PlaceObject(BOTTOM_HALF_WALL, Obj::Coords(6, 3));

    room->PlaceObject(SOUTH_DOOR, Obj::Coords(3, 4));

    room->PlaceObject(BED, Obj::Coords(1, 1));
    room->PlaceObject(BED, Obj::Coords(2, 1));
    room->PlaceObject(BED, Obj::Coords(1, 2));
    room->PlaceObject(BED, Obj::Coords(2, 2));

    room->PlaceObject(SMALL_SHELF, Obj::Coords(1, 3));
    room->PlaceObject(SMALL_SHELF, Obj::Coords(2, 3));

    room->PlaceObject(TV, Obj::Coords(3, 1));

    room->PlaceObject(AKI_DESK, Obj::Coords(4, 1));
    room->PlaceObject(AKI_DESK, Obj::Coords(5, 1));
    room->PlaceObject(AKI_CHAIR, Obj::Coords(4, 2));

    room->PlaceObject(VY_DESK, Obj::Coords(6, 1));
    room->PlaceObject(VY_DESK, Obj::Coords(6, 2));
    room->PlaceObject(VY_CHAIR, Obj::Coords(5, 2));
}

////////////
// EVENTS //
////////////
static void bed_Use(Obj::Template* obj)
{
    bool gotAnswer = false;

    string answer;

    while (!gotAnswer)
    {
        cout << "Would you like to rest? y/n: ";
        getline(cin, answer);

        if (_stricmp(answer.c_str(), "Y") == 0)
        {
            cout << "You rest in the bed..." << endl;
            player.SetCurrentHealth(player.GetMaxHealth());
            cout << "Your health has been fully restored." << endl;
            cout << "But you're still hungry...";

            gotAnswer = true;
        }
        else if (_stricmp(answer.c_str(), "N") == 0)
        {
            cout << "You step away from the bed.";

            gotAnswer = true;
        }
    }
}