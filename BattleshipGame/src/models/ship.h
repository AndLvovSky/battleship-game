#ifndef SHIP_H
#define SHIP_H

#include "square.h"
#include <vector>

using namespace std;

namespace battleshipGame {

class Ship {

    private:

    vector <Square> squares;
    int hP;

    public:

    Ship(Square startSquare, int shipSize, bool horizontal);
    Square getStartSquare();
    int getSize();
    bool isHorizontal();
    int getHP();
    void setHP(int);
    bool isSunk();
    vector <Square> getSquares();
};

}

#endif // SHIP_H
