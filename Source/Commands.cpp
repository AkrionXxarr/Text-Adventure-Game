#ifndef _COMMANDS_HPP_
#define _COMMANDS_HPP_

#include <string>

/*
const std::string EXAMINE = "Examine";
const std::string HELP = "Help";
const std::string INV = "Inv";
const std::string LOOK = "Look";
const std::string MOVE = "Move";
const std::string OPEN = "Open";
const std::string USE = "Use";
*/

enum COMMANDS { EXAMINE, HELP, INV, LOOK, GO, OPEN, STATUS, USE, INVALID };

COMMANDS CommandCheck(std::string message)
{
    if (_stricmp(message.c_str(), "Examine") == 0)
    {
        return EXAMINE;
    }
    else if (_stricmp(message.c_str(), "Help") == 0)
    {
        return HELP;
    }
    else if (_stricmp(message.c_str(), "Inv") == 0)
    {
        return INV;
    }
    else if (_stricmp(message.c_str(), "Look") == 0)
    {
        return LOOK;
    }
    else if (_stricmp(message.c_str(), "Go") == 0)
    {
        return GO;
    }
    else if (_stricmp(message.c_str(), "Open") == 0)
    {
        return OPEN;
    }
    else if (_stricmp(message.c_str(), "Status") == 0)
    {
        return STATUS;
    }
    else if (_stricmp(message.c_str(), "Use") == 0)
    {
        return USE;
    }

    return INVALID;
}
#endif