#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"
#include "DefaultObjEvents.hpp"
using namespace std;

static enum OBJECTS { NO_OBJECT, OPEN_DOORWAY, FLOOR_VENT, FLOOR, BRETTS_DESK, BIRD_CAGE, SMALL_SHELF, END_TABLE, PERSON_BRETT };

// Event forward declarations //
static void personBrett_Talk(Obj::Template* obj);

void BuildDiningRoom(Room::Template* room)
{
    // Create Objects //
    Obj::Template openDoor("Open Doorway", '/', OPEN_DOORWAY);
    Obj::Template floor("", (char)32, FLOOR);
    Obj::Template floorVent("Floor Vent", '"', FLOOR_VENT);
    Obj::Template brettsDesk("Brett's Desk", (char)209, BRETTS_DESK);
    Obj::Template birdCage("Bird Cage", '#', BIRD_CAGE);
    Obj::Template smallShelf("Small Shelf", '=', SMALL_SHELF);
    Obj::Template endTable("End Table", (char)246, END_TABLE);
    Obj::Template personBrett("Brett", '@', PERSON_BRETT);

    // Describe Room //
    room->SetDescription("What would normally be a dining room is currently being used\n"
                         "as a computer room. It opens into the Living Room to the west\n"
                         "and a Hallway to the south.\n"
                         "The floor is wood.");

    // Describe Objects //
    openDoor.SetDescription("An open doorway that leads to the Kitchen.");
    openDoor.SetExamine("You search around the doorframe but find nothing of interest.");

    floorVent.SetDescription("A 2 foot by 1 1/2 foot wooden grate heating vent on the floor.");
    floorVent.SetExamine("You search the floor vent but find nothing of interest.");

    brettsDesk.SetDescription("A glass computer desk with a tall black computer tower standing at the side.");
    brettsDesk.SetExamine("You examine the desk and find nothing of interest.");

    birdCage.SetDescription("A roughly 5 foot tall, 4 foot wide, and 5 foot deep bird cage.");
    birdCage.SetExamine("You look into the bird cage and find a white cockatoo.\n"
                        "He stares at you with murderous eyes.");

    smallShelf.SetDescription("A small shelf with glass shelves and a metal frame.");
    smallShelf.SetExamine("You examine the shelf but find nothing of interest.");

    endTable.SetDescription("A 2 1/2 foot high end table");
    endTable.SetExamine("You examine the table but find nothing of interest.");

    personBrett.SetDescription("He's a middle-aged man.");
    personBrett.SetExamine("There appears to be a viking sitting at a computer...\n"
                           "He doesn't seem to be aware of your presence in the room.");

    // Add Event//
    personBrett.Event(TALK, &personBrett_Talk);

    // Add Objects //
    room->AddObject(openDoor);
    room->AddObject(floorVent);
    room->AddObject(floor);
    room->AddObject(brettsDesk);
    room->AddObject(birdCage);
    room->AddObject(smallShelf);
    room->AddObject(endTable);
    room->AddObject(personBrett);

    // Place Objects //
    room->PlaceObject(OPEN_DOORWAY, Obj::Coords(7, 3));

    room->PlaceObject(FLOOR_VENT, Obj::Coords(4, 1));

    room->PlaceObject(FLOOR, Obj::Coords(0, 1));
    room->PlaceObject(FLOOR, Obj::Coords(0, 2));
    room->PlaceObject(FLOOR, Obj::Coords(1, 5));

    room->PlaceObject(END_TABLE, Obj::Coords(2, 4));
    room->PlaceObject(BRETTS_DESK, Obj::Coords(3, 4));
    room->PlaceObject(BRETTS_DESK, Obj::Coords(4, 4));
    room->PlaceObject(BRETTS_DESK, Obj::Coords(5, 4));

    room->PlaceObject(PERSON_BRETT, Obj::Coords(4, 3));

    room->PlaceObject(BIRD_CAGE, Obj::Coords(2, 2));

    room->PlaceObject(SMALL_SHELF, Obj::Coords(6, 1));

}

////////////
// EVENTS //
////////////
static unsigned int counter = 0;
static void personBrett_Talk(Obj::Template* obj)
{
    if (counter > 2)
    {
        if (inventory.HasItem(BRETTS_UNKNOWN_KEY))
        {
            cout << "You ask Brett about the Unknown Key and he explains that it's the key" << endl
                 << "to his bedroom door.";

            inventory.RemoveItem(BRETTS_UNKNOWN_KEY);
            inventory.AddItem(Inv::Item(BRETTS_BEDROOM_KEY, "Brett's Bedroom Key"));
        }
        else if (inventory.HasItem(BRETTS_BEDROOM_KEY))
        {
            cout << "You ask Brett about his Bedroom Key and he explains that it's the key" << endl
                 << "to his bedroom door. He seems oblivious that he's repeating himself." << endl
                 << "You can hear Susan laughing in the Living Room.";
        }
        else
        {
            cout << "You ask Brett what he's doing, to which he responds:" << endl
                 << "'Dealing with idiots' .. You look at his computer screen and can tell" << endl
                 << "that he's in the Battlegrounds on WoW. Something about bad PVPers must" << endl
                 << "really bug him.";
        }
        counter = 0;
    }
    else
    {
        switch (counter)
        {
        case 0:
            cout << "You attempt to talk to Brett, but he doesn't appear to catch anything you say." << endl
                 << "Perhaps you should try again...";
            break;

        case 1:
            cout << "You try talking to Brett again. This time he seems to respond but it doesn't" << endl
                 << "seem to make much sense. You seem to be making progress, though, so perhaps" << endl
                 << "you should keep trying...";
            break;

        case 2:
            cout << "Once again you try getting Brett's attention, and this time you hear" << endl
                 << "Susan's voice coming from the living room..." << endl
                 << "'Brett!' she yells." << endl
                 << "'" << player.GetCharacterName() << " is trying to get your attention!'" << endl << endl;

            cout << "This seems to knock Brett out of his trance." << endl
                 << "Now you might be able to talk to him.";
        }
        counter++;
    }
}