#include "test_square.h"
#include "square.h"

using namespace battleshipGame;

void TestSquare::testGetters() {
    Square sq(3, 5);
    QVERIFY(sq.getX() == 3);
    QVERIFY(sq.getY() == 5);
}
