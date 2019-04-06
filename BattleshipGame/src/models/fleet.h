#ifndef FLEET_H
#define FLEET_H

#include "ship.h"
#include "shot.h"
#include <vector>

using namespace std;

namespace battleshipGame {

class Fleet {

    vector<Ship> ships;
    Square::State squaresState[10][10];

    bool checkPositionForSquare(const Square&) const;

public:
    Fleet();
    bool checkPositionForShip(const Ship&) const;
    void addShip(Ship);
    Shot fire(const Square&);
    bool hasAttacked(const Square&) const;
    int getHP() const;
    bool isDestroyed() const;
    Square::State getSquareState(int x, int y) const;
    vector<Ship> getShips() const;
    int findShipIndex(const Square&) const;
};

}

#endif // FLEET_H
