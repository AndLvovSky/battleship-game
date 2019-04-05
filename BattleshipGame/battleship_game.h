#ifndef BATTLESHIP_GAME
#define BATTLESHIP_GAME

#include "fleet.h"
#include <map>

using namespace std;

namespace battleshipGame {

class BattleshipGame {

    Fleet* yourFleet;
    Fleet* opponentFleet;

    void randomPlacement(Fleet&);
    bool isSquareGood(Square);

public:
    enum class Mode {
        PLACING,
        BATTLE,
        RESUME
    };

    Mode mode;
    Square square;
    bool squareSelected;
    int shipSize;
    bool shipHorizontal;
    bool stepYours;
    bool youWon;
    map <int, int> shipsLast;

    void start();
    void quit();
    void battle();
    static BattleshipGame& get();
    Fleet& getFleet(bool yours);
    Square opponentStep();

};

}

#endif // BATTLESHIP_GAME
