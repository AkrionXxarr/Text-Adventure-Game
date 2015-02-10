#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"
#include "DefaultObjEvents.hpp"
using namespace std;

static enum OBJECTS { NO_OBJECT, FLOOR, COUCH, TV, EXERCISE_MACHINE, CABINET, MISC, FIRE_PLACE, PERSON_SUSAN };

bool gotLaundry = false;

// Event forward declarations //
static void personSusan_Talk(Obj::Template* obj);

void BuildLivingRoom(Room::Template* room)
{
    // Create Objects //
    Obj::Template floor("", (char)32, FLOOR);
    Obj::Template couch("Couch", (char)20, COUCH);
    Obj::Template tv("Television", (char)227, TV);
    Obj::Template exerciseMchn("Exercise Machine", (char)146, EXERCISE_MACHINE);
    Obj::Template cabinet("Cabinet", (char)203, CABINET);
    Obj::Template misc("Misc. Stuff", (char)176, MISC);
    Obj::Template firePlace("Fire Place", (char)15, FIRE_PLACE);
    Obj::Template personSusan("Susan", '@', PERSON_SUSAN);

    // Describe Room //
    room->SetDescription("Easily the largest room of the house.\n"
                         "It opens to the east into the Dining Room.\n"
                         "The floor is carpet.");

    // Describe Objects //
    couch.SetDescription("An L shaped couch.");
    couch.SetExamine("You search the couch but find nothing of interest.");

    tv.SetDescription("A large television.");
    tv.SetExamine("You search the television but find nothing of interest.");

    exerciseMchn.SetDescription("A strange exercise machine with curved rails atop of which sits a seat\n"
                                "with rollers.");
    exerciseMchn.SetExamine("You search the exercise machine but find nothing of interest.");

    cabinet.SetDescription("A long, hip-high cabinet with multiple doors.");
    cabinet.SetExamine("You search the cabinet but find nothing of interest.");

    misc.SetDescription("An assortment of various items.");
    misc.SetExamine("Stuff. (Need to actually figure out what all is there)");
    
    firePlace.SetDescription("A moderately sized fire place.");
    firePlace.SetExamine("You search the fireplace but find nothing of interest.");

    personSusan.SetDescription("A middle-aged woman.");
    personSusan.SetExamine("You can't quite put your finger on it, but something about this person\n"
                           "puts you on edge. You get the feeling you shouldn't mess with her.");

    // Add Events //
    personSusan.Event(TALK, &personSusan_Talk);

    // Add Objects //
    room->AddObject(floor);
    room->AddObject(couch);
    room->AddObject(tv);
    room->AddObject(exerciseMchn);
    room->AddObject(cabinet);
    room->AddObject(misc);
    room->AddObject(firePlace);
    room->AddObject(personSusan);

    // Place Objects //
    room->PlaceObject(FLOOR, Obj::Coords(9, 8));
    room->PlaceObject(FLOOR, Obj::Coords(9, 7));
    
    room->PlaceObject(TV, Obj::Coords(8, 2));
    room->PlaceObject(TV, Obj::Coords(7, 1));
    room->PlaceObject(MISC, Obj::Coords(8, 1));

    room->PlaceObject(CABINET, Obj::Coords(6, 8));
    room->PlaceObject(CABINET, Obj::Coords(5, 8));
    room->PlaceObject(CABINET, Obj::Coords(4, 8));
    room->PlaceObject(CABINET, Obj::Coords(3, 8));

    room->PlaceObject(COUCH, Obj::Coords(6, 5));
    room->PlaceObject(COUCH, Obj::Coords(5, 5));
    room->PlaceObject(COUCH, Obj::Coords(4, 5));
    room->PlaceObject(COUCH, Obj::Coords(3, 5));
    room->PlaceObject(COUCH, Obj::Coords(3, 4));
    room->PlaceObject(COUCH, Obj::Coords(3, 3));
    room->PlaceObject(COUCH, Obj::Coords(3, 2));
    
    room->PlaceObject(PERSON_SUSAN, Obj::Coords(4, 4));

    room->PlaceObject(EXERCISE_MACHINE, Obj::Coords(1, 1));

    room->PlaceObject(FIRE_PLACE, Obj::Coords(4, 0));
    room->PlaceObject(FIRE_PLACE, Obj::Coords(5, 0));
}

////////////
// EVENTS //
////////////
static void personSusan_Talk(Obj::Template* obj)
{
    bool gotAnswer = false;
    string answer;

    if (!gotLaundry)
    {
        cout << "Susan asks if you can take a basket of laundry down to the basement" << endl
             << "and put the clothes in the washing machine." << endl << endl;

        while (!gotAnswer)
        {
            cout << "Do you help her? y/n: ";
            getline(cin, answer);

            if (_stricmp(answer.c_str(), "Y") == 0)
            {
                cout << "You're given a basket of laundry.";
                inventory.AddItem(Inv::Item(DIRTY_LAUNDRY, "Dirty Laundry"));
                gotAnswer = true;
                gotLaundry = true;
            }
            else if (_stricmp(answer.c_str(), "N") == 0)
            {
                cout << "She seems angry. That probably wasn't a good idea." << endl;
                cout << "You take an earful for 20 damage.";

                player.DamageCharacter(20);
                gotAnswer = true;
            }
        }
    }
    else
    {
        cout << "Susan brings up the latest morbid news story before you even say anything,\n"
                "and then moves onto stories that shouldn't be news but are anyway.\n"
                "One about a cat biting a famous person's nose reminds her of Michael's\n"
                "relationship with Spaz. You run out of things to talk about at this point\n"
                "and decide to move on.";
    }
}