#include "LocalHeaders.hpp"
#include "GlobalHeaders.hpp"
#include "RoomBuildDecl.hpp"

Room::Template* BuildRooms()
{
    // Create Rooms //
    Room::Template* akisRoom         = new Room::Template("Aki's Room", AKIS_ROOM, 8, 5);
    Room::Template* basementBathroom = new Room::Template("Basement Bathroom", BASEMENT_BATHROOM, 5, 4);
    Room::Template* basementHall     = new Room::Template("Basement Hallway", BASEMENT_HALLWAY, 8, 4);
    Room::Template* basementMain     = new Room::Template("Main Basement", BASEMENT_MAIN, 8, 7);
    Room::Template* basementStorage  = new Room::Template("Basement Storage Room", BASEMENT_STORAGE, 5, 5);
    Room::Template* brettsCloset     = new Room::Template("Brett's Closet", BRETTS_CLOSET, 5, 4);
    Room::Template* brettsRoom       = new Room::Template("Brett's Room", BRETTS_ROOM, 7, 6);
    Room::Template* diningRoom       = new Room::Template("Dining Room", DINING_ROOM, 8, 6);
    Room::Template* kitchen          = new Room::Template("Kitchen", KITCHEN, 6, 8);
    Room::Template* livingRoom       = new Room::Template("Living Room", LIVING_ROOM, 10, 10);
    Room::Template* michaelsCloset   = new Room::Template("Michael's Closet", MICHAELS_CLOSET, 3, 3);
    Room::Template* michaelsRoom     = new Room::Template("Michael's Room", MICHAELS_ROOM, 7, 7);
    Room::Template* landing          = new Room::Template("Landing", STAIRWAY_LANDING, 5, 3);
    Room::Template* upstairsBathroom = new Room::Template("Upstairs Bathroom", UPSTAIRS_BATHROOM, 4, 5);
    Room::Template* upstairsHall     = new Room::Template("Upstairs Hallway", UPSTAIRS_HALLWAY, 6, 3);
    
    Room::Template* startRoom = akisRoom;

    // Connect Rooms //
    akisRoom->ConnectRoom(basementHall, SOUTH);
    
    basementHall->ConnectRoom(basementBathroom, WEST);
    basementHall->ConnectRoom(basementMain, EAST);

    basementBathroom->ConnectRoom(basementStorage, NORTH);

    basementMain->ConnectRoom(landing, UP);

    landing->ConnectRoom(kitchen, UP);

    kitchen->ConnectRoom(diningRoom, WEST);

    diningRoom->ConnectRoom(livingRoom, WEST);
    diningRoom->ConnectRoom(upstairsHall, SOUTH);

    upstairsHall->ConnectRoom(brettsRoom, WEST);
    upstairsHall->ConnectRoom(upstairsBathroom, SOUTH);
    upstairsHall->ConnectRoom(michaelsRoom, EAST);

    brettsRoom->ConnectRoom(brettsCloset, NORTH);

    michaelsRoom->ConnectRoom(michaelsCloset, EAST);

    // Fill Rooms //
    BuildAkisRoom(akisRoom);
    BuildBasementBathroom(basementBathroom);
    BuildBasementHallway(basementHall);
    BuildBasementMain(basementMain);
    BuildBasementStorage(basementStorage);
    BuildBrettsRoom(brettsRoom);
    BuildBrettsCloset(brettsCloset);
    BuildDiningRoom(diningRoom);
    BuildKitchen(kitchen);
    BuildLivingRoom(livingRoom);
    BuildMichaelsRoom(michaelsRoom);
    BuildMichaelsCloset(michaelsCloset);
    BuildStairwayLanding(landing);
    BuildUpstairsBathroom(upstairsBathroom);
    BuildUpstairsHallway(upstairsHall);

    return startRoom;
}