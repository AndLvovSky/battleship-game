#ifndef SHIP_H
#define SHIP_H

#include "square.h"
#include <vector>

using namespace std;

namespace battleshipGame {

class Ship {

    vector<Square> squares;
    int hP;

public:
    Ship(Square startSquare, int shipSize, bool horizontal);
    Square getStartSquare() const;
    int getSize() const;
    bool isHorizontal() const;
    int getHP() const;
    void setHP(int);
    bool isSunk() const;
    vector<Square> getSquares() const;
};

}

#endif // SHIP_H
