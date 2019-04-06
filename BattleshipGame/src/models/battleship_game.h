#ifndef BATTLESHIP_GAME
#define BATTLESHIP_GAME

#include "fleet.h"
#include <map>
#include <memory>

using namespace std;

namespace battleshipGame {

class BattleshipGame {

    shared_ptr<Fleet> yourFleet;
    shared_ptr<Fleet> opponentFleet;

    void randomPlacement(Fleet&) const;
    bool isSquareGood(const Square&) const;

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
    map<int, int> shipsMap;
    map<int, int> shipsLast;

    void start(const map<int, int>& shipsMap);
    void quit();
    Fleet& getFleet(bool yours);
    Square opponentStep() const;
    static BattleshipGame& get();

};

}

#endif // BATTLESHIP_GAME
