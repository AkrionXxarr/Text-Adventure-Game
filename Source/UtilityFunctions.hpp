#ifndef _UTILITY_FUNCTIONS_HPP_
#define _UTILITY_FUNCTIONS_HPP_

Room::Template* BuildRooms();
void DeleteRooms(Room::Template* startRoom);
COMMANDS CommandCheck(std::string command);
std::string FirstCommand(std::string command);
std::string SecondCommand(std::string command);
DIRECTIONS DirectionCheck(std::string command);
void RoomSwitch(Room::Template* curRoom, std::string& command);

#endif
