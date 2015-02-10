#include "GlobalHeaders.hpp"
#include "LocalHeaders.hpp"
#include "UtilityFunctions.hpp"

using namespace std;

//void MapLoop(Room::Template* curRoom);
void GameLoop(Room::Template* curRoom);

bool _DEBUG_MESSAGES = false;
bool wonGame = false;

int main()
{
    bool quitGame = false;
    bool gotAnswer = false;

    string answer;

    Room::Template* startRoom;
    string playerName;

    cout << "***** *****  ***  ***** ***** ***** ***** ***** ***** " << endl;
    cout << "*       *   *   * *   * *     *   * *  ** *  **   *   " << endl;
    cout << "*****   *   ***** ***** ***   ***** * * * * * *   *   " << endl;
    cout << "    *   *   *   * *  *  *     *  *  **  * **  *   *   " << endl;
    cout << "*****   *   *   * *   * *     *   * ***** *****   *   " << endl;
    cout << endl;
    cout << "========== Game Start ==========" << endl;
    cout << "(v1.1)" << endl << endl;

    do
    {
        cout << "Your Name: "; getline(cin, playerName);

        if (playerName.length() > 30)
            cout << "Name too long" << endl;
    } while (playerName.length() > 30);
    cout << endl;

    player.SetCharacterName(playerName);

    player.SetMaxHealth(100);
    player.SetCurrentHealth(100);

    startRoom = BuildRooms();
    GameLoop(startRoom);
    DeleteRooms(startRoom);


    cout << "~~~~~~ Credits ~~~~~~" << endl;
    cout << "(Stephen 'Akrion' Bloomquist)" << endl
         << "Concept, Programming, Level Design" << endl;
    cout << "--" << endl;
    cout << "(Julia 'Siivyra' Ryer)" << endl
         << "Testing, Proofreading, Dialog Corrections" << endl;
    cout << endl;

    cout << "=========== Game End ===========" << endl << endl;

    cout << "Press <ENTER> to continue...";
    cin.ignore(INT_MAX, '\n');
    cout << endl;

    return 0;
}