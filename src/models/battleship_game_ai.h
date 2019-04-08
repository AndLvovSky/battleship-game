#ifndef BATTLESHIP_GAME_AI_H
#define BATTLESHIP_GAME_AI_H

#include "fleet.h"
#include <map>

using namespace battleshipGame;
using namespace std;

class BattleshipGameAI {

    static bool isSquareGood(const Fleet&, const Square&);

public:
    static void placeShips(Fleet&, const map<int, int>&);
    static Square findBestSquare(const Fleet&);
};

#endif // BATTLESHIP_GAME_AI_H
