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
    Square findBestSquare();

public:
    enum class Mode {
        PLACING,
        BATTLE,
        RESUME,
        BEFORE_YOUR_STEP,
        AFTER_YOUR_STEP,
        BEFORE_OPPONENT_STEP,
        AFTER_OPPONENT_STEP
    };

    Mode mode;
    Square square;
    bool squareSelected;
    int shipSize;
    bool shipHorizontal;
    bool stepYours;
    bool youWinner;
    map <int, int> shipsLast;

    void start();
    void quit();
    void battle();
    static BattleshipGame& get();
    Fleet& getFleet(bool yours);
    void makeOpponentStep();

};

}

#endif // BATTLESHIP_GAME
