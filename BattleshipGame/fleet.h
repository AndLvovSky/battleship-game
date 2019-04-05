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

    public:

    Fleet();
    bool checkPositionForShip(Ship);
    void addShip(Ship);
    Shot fire(Square);
    bool hasAttacked(Square);
    int getHP();
    bool isDestroyed();
    Square::State getSquareState(int x, int y);
    vector <Ship> getShips();
    int findShipIndex(Square);
};

}

#endif // FLEET_H
