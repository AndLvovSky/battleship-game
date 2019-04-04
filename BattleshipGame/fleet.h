#ifndef FLEET_H
#define FLEET_H

#include "ship.h"
#include "shot.h"
#include <vector>

using namespace std;

namespace battleshipGame {

class Fleet {

    private:

    vector <Ship> ships;
    Square::State squaresState[10][10];

    bool checkPositionForSquare(Square);
    int findShipIndex(Square);

    public:

    Fleet();
    bool checkPositionForShip(Square startSquare, int shipSize, bool orientation);
    void addShip(Ship);
    Shot fire(Square);
    bool hasAttacked(Square);
    int getHP();
    Square::State getSquareState(int x, int y);
    vector <Ship> getShips();
};

}

#endif // FLEET_H
