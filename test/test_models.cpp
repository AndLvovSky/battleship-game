#include "test_models.h"
#include "square.h"

using namespace battleshipGame;

void TestModels::testSquare() {
    Square sq(3, 5);
    QVERIFY(sq.getX() == 3);
    QVERIFY(sq.getY() == 5);
}

QTEST_APPLESS_MAIN(TestModels)
