#include "test_ship.h"
#include "ship.h"

using namespace battleshipGame;

void TestShip::testGetters() {
    Square stSq(1, 2);
    Ship ship(stSq, 3, true);
    QCOMPARE(stSq, ship.getStartSquare());
}
