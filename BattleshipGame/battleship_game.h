#ifndef BATTLESHIP_GAME
#define BATTLESHIP_GAME

#include "fleet.h"

using namespace std;

namespace battleshipGame {

class BattleshipGame {

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
    Fleet* yourFleet;
    Fleet* opponentFleet;
    Square currentSquare;
    bool isShipSelected;
    int selectedShipSize;
    bool selectedShipOrientation;
    bool isStepYours;
    int battleMode;
    int resultOfStep;
    bool isYouWinner;

public:
    void start();
    void quit();
    static BattleshipGame& get();
    Fleet& getFleet(bool yours);
    Square getFleetSquareFrom(int x, int y, int startY, int startX);
    Square getYourFleetSquare(int x, int y);
    Square getOpponentFleetSquare(int x, int y);
    void shiftCurrentSquare(char key);
    void placeShips();
    bool isSquareGood(Square);
    Square findBestSquare();
    void randomPlacement(Fleet&);
    void battle();
    void refresh();
    void resume();
};

}

#endif // BATTLESHIP_GAME
