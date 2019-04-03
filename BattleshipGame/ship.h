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

    Ship(Square startSquare, int shipSize, bool orientation);
    int getHP();
    void setHP(int);
    vector <Square> getSquares();
};

}

#endif // SHIP_H
