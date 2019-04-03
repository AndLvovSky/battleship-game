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

    public:

    Fleet();
    int findShipIndex(Square);
    bool checkPositionForSquare(Square);
    bool checkPositionForShip(Square startSquare, int shipSize, bool orientation);
    void addShip(Ship);
    Shot fire(Square);
    bool hasAttacked(Square);
    int getHP();
    Square::State setSquareState(int x, int y, Square::State state);
    Square::State getSquareState(int x, int y);
    vector <Ship> getShips();
    void clear();
};

}

#endif // FLEET_H
