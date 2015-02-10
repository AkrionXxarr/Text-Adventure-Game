#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"
#include "DefaultObjEvents.hpp"
using namespace std;

static enum OBJECTS { NO_OBJECT, STAIRS_UP, FLOOR, FURNACE, WATER_HEATER, MISC, FREEZER, FRIDGE,
                   FULL_WALL, SMALL_SHELF, LARGE_SHELF, PIANO, PIANO_CHAIR, BOXES };

static bool usedFridge = false;

// Event forward declarations //
static void fridge_Use(Obj::Template* obj);

void BuildBasementMain(Room::Template* room)
{
    // Create Objects //
    Obj::Template stairsUp("Stairs Up", (char)30, STAIRS_UP);
    Obj::Template floor("", (char)32, FLOOR);
    Obj::Template furnace("Furnace", (char)216, FURNACE);
    Obj::Template waterHeater("Water Heater", (char)153, WATER_HEATER);
    Obj::Template misc("Misc. stuff", (char)176, MISC);
    Obj::Template freezer("Freezer", (char)210, FREEZER);
    Obj::Template fridge("Small Fridge", (char)189, FRIDGE);
    Obj::Template smallShelf("Small Shelf", '=', SMALL_SHELF);
    Obj::Template largeShelf("Large Shelf", (char)240, LARGE_SHELF);
    Obj::Template piano("Piano", (char)185, PIANO);
    Obj::Template pianoChair("Piano Chair", (char)233, PIANO_CHAIR);
    Obj::Template boxes("Boxes", (char)254, BOXES);

    // Describe Room //
    room->SetDescription("This room is the largest of all the rooms in the basement.\n"
                         "It's used as a room for storage, a semi-kitchen, a place for musical\n"
                         "instruments, as well as being where the furnace and water heater are kept.\n"
                         "This room is the most varied in the house.\n"
                         "The floor is smooth concrete.");

    // Describe Objects //
    stairsUp.SetDescription("A relatively steep staircase that hugs the wall;\n"
                            "it doesn't leave much in terms of height.\n"
                            "The stairs lead up to a Landing.");
    stairsUp.SetExamine("You find a fairly thin, somewhat cheap looking carpet lining the top of flight\n"
                        "of boxed wooden stairs. A series of shelves rest underneath the stairs holding\n"
                        "an assortment of items.");

    furnace.SetDescription("An electric furnace takes up the majority of the space near the wall of the\n"
                           "room.");
    furnace.SetExamine("Various tubes go to and from the furnace, with a single ventilation shaft\n"
                       "traveling to the ceiling and splitting off in multiple directions.\n"
                       "A switch is present for the purposes of turning the furnace on and off.");

    waterHeater.SetDescription("Your standard run-of-the-mill cylindrical water heater.");
    waterHeater.SetExamine("You don't find anything one wouldn't expect to find on a water heater.");

    misc.SetDescription("An assortment of various items.");
    misc.SetExamine("You find computer components, extension cords, a vaccume, and various small boxes.");

    freezer.SetDescription("A medium sized standalone freezer, roughly 4 1/2 feet tall, 3 feet wide\n"
                           "and 3 feet deep.");
    freezer.SetExamine("You search the freezer but find nothing of interest.");

    fridge.SetDescription("A small sized standalone refridgerator, roughly 3 feet tall, 2 1/2 feet wide and 2 1/2 feet deep.");
    fridge.SetExamine("You search the refridgerator but find nothing of interest.");

    smallShelf.SetDescription("Black shelves that stand roughly 3 1/2 feet wide and stand from\n"
                              "floor to ceiling.");
    smallShelf.SetExamine("You find boxes of soda on the shelf near the fridge, and various computer parts\n"
                       "on the shelf near the piano.");

    largeShelf.SetDescription("Large industrial warehouse shelves.");
    largeShelf.SetExamine("These shelves are loaded with boxes and containers similar to the\n"
                          "basement storage room.");

    piano.SetDescription("An 88-key electric piano.");
    piano.SetExamine("The piano is much higher quality than your standard electric keyboard.");

    pianoChair.SetDescription("A piano chair.");
    pianoChair.SetExamine("You search the piano chair and find nothing of interest.");

    boxes.SetDescription("Boxes of random crap.");
    boxes.SetExamine("Searching the boxes yields various room decorations.");

    // Add Events //
    fridge.Event(USE, &fridge_Use);

    // Add Objects //
    room->AddObject(stairsUp);
    room->AddObject(floor);
    room->AddObject(furnace);
    room->AddObject(waterHeater);
    room->AddObject(misc);
    room->AddObject(freezer);
    room->AddObject(fridge);
    room->AddObject(Obj::Template("", (char)219, FULL_WALL));
    room->AddObject(smallShelf);
    room->AddObject(largeShelf);
    room->AddObject(piano);
    room->AddObject(pianoChair);
    room->AddObject(boxes);

    // Place Objects //
    room->PlaceObject(STAIRS_UP, Obj::Coords(6, 4));
    room->PlaceObject(FULL_WALL, Obj::Coords(6, 5));

    room->PlaceObject(FLOOR, Obj::Coords(0, 4));
    room->PlaceObject(MISC, Obj::Coords(0, 5));

    room->PlaceObject(FREEZER, Obj::Coords(2, 5));
    room->PlaceObject(FRIDGE, Obj::Coords(1, 1));

    room->PlaceObject(FURNACE, Obj::Coords(3, 4));
    room->PlaceObject(FURNACE, Obj::Coords(4, 4));

    room->PlaceObject(WATER_HEATER, Obj::Coords(5, 4));

    room->PlaceObject(BOXES, Obj::Coords(3, 5));
    room->PlaceObject(BOXES, Obj::Coords(4, 5));
    room->PlaceObject(BOXES, Obj::Coords(5, 5));

    room->PlaceObject(SMALL_SHELF, Obj::Coords(1, 3));

    room->PlaceObject(SMALL_SHELF, Obj::Coords(5, 1));

    room->PlaceObject(LARGE_SHELF, Obj::Coords(2, 1));
    room->PlaceObject(LARGE_SHELF, Obj::Coords(3, 1));
    room->PlaceObject(LARGE_SHELF, Obj::Coords(4, 1));
    room->PlaceObject(LARGE_SHELF, Obj::Coords(4, 2));

    room->PlaceObject(PIANO, Obj::Coords(6, 2));
    room->PlaceObject(PIANO_CHAIR, Obj::Coords(5, 2));
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