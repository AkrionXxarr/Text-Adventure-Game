#ifndef _GLOBAL_DEFINES_HPP_
#define _GLOBAL_DEFINES_HPP_

extern bool _DEBUG_MESSAGES;
extern bool wonGame;

enum CHARACTER_STATUS { DEAD, ALIVE };

// === Steps for adding commands ===
// 1)-Add command to COMMANDS enum in GlobalDefines.hpp
// 2)-Add command to CommandCheck() in UtilityFunctions.cpp
// 3)-Add command to GameLoop.cpp
// 4)-Add command to HelpMessage() in SubCommands.cpp
// -- If command is a targeted command --
// 1.a)-Add a DefaultEvent function for the command in DefaultObjEvents.cpp
// 1.b)--Declare the DefaultEvent function in DefaultObjEvents.hpp
// 2.a)-Add command function pointer to Obj::Template in ObjectClass.hpp
// 2.b)--Assign the pointer to the appropriate DefaultEvent function in the Obj::Template class constructor
// 3.a)-Add command function to ObjectClass.hpp in Obj::Template
// 3.b)--Add command function to ObjectClass.cpp for Obj::Template
// 4)-Add command to Obj::Template::Event() in ObjectClass.cpp
// 5)-Call appropriate room->GetObject()->Command() prototype in GameLoop.cpp
enum COMMANDS { EXAMINE, HELP, INV, LOOK, OPEN, CLOSE, STATUS, TAKE, TALK, USE, UNLOCK, QUIT, INVALID_COMMAND };

enum DIRECTIONS { NORTH, EAST, SOUTH, WEST, UP, DOWN, INVALID_DIRECTION };

enum LOCK_STATE { LOCKED, UNLOCKED, INVALID_LOCK };

enum ROOMS { NO_ROOM, AKIS_ROOM, BASEMENT_BATHROOM, BASEMENT_HALLWAY, BASEMENT_MAIN, BASEMENT_STORAGE, 
             BRETTS_CLOSET, BRETTS_ROOM, BUILD_ROOMS, DINING_ROOM, KITCHEN, LIVING_ROOM, MICHAELS_CLOSET, 
             MICHAELS_ROOM, STAIRWAY_LANDING, UPSTAIRS_BATHROOM, UPSTAIRS_HALLWAY };

enum ITEMS { NO_ITEM, DIRTY_LAUNDRY, WET_LAUNDRY, BRETTS_BEDROOM_KEY, BRETTS_UNKNOWN_KEY, CAT_SPAZ};

namespace Inv
{
    class Inventory;
};
extern Inv::Inventory inventory;

namespace Character
{
    class Template;
};

extern Character::Template player;

#endif
