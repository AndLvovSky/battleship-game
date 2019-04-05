#include "battleship_game.h"
#include "settings.h"

using namespace std;
using namespace battleshipGame;

void BattleshipGame::start() {
    yourFleet = new Fleet();
    opponentFleet = new Fleet();
    squareSelected = false;
    shipSize = 1;
    shipHorizontal = true;
    mode = Mode::PLACING;
    shipsLast = Settings::getInstance().getShipsMap();
    stepYours = true;
    randomPlacement(*opponentFleet);
    /* for battle mode debug */
    //randomPlacement(*yourFleet);
    //for (auto& [decks, number]: shipsLast) number = 0;
}

BattleshipGame& BattleshipGame::get() {
    static BattleshipGame game;
    return game;
}

void BattleshipGame::quit() {
    delete yourFleet;
    delete opponentFleet;
}

Fleet& BattleshipGame::getFleet(bool yours) {
    if (yours) {
        return *yourFleet;
    } else {
        return *opponentFleet;
    }
}

void BattleshipGame::randomPlacement(Fleet& fleet) {
    auto shipsMap = Settings::getInstance().getShipsMap();
    int countsOfShips[5] = {0, shipsMap[1], shipsMap[2],
                            shipsMap[3], shipsMap[4]};

    for (int size = 4; size > 0; size--) {
        bool isOrientationFixed = false, horizontal;

        for (int i = 0; i < countsOfShips[size]; i++) {
            if (!isOrientationFixed) {
                horizontal = rand() % 2;
            }

            vector <Square> correctSquares;
            for (int x = 0; x < 10; x++) {
                for (int y = 0; y < 10; y++) {
                    Square square(x, y);
                    if (fleet.checkPositionForShip(
                          Ship(square, size, horizontal))) {
                        correctSquares.push_back(square);
                    }
                }
            }

            if (correctSquares.empty()) {
                isOrientationFixed = true;
                horizontal = !horizontal;
                i--;
                continue;
            }

            Ship ship(correctSquares[rand() % correctSquares.size()],
                      size, horizontal);
            fleet.addShip(ship);
            isOrientationFixed = false;
        }
    }
}

Square BattleshipGame::opponentStep() {
    vector <Square> correctSquares;
    vector <Square> goodSquares;
    for (int x = 0; x < 10; x++) {
        for (int y = 0; y < 10; y++) {
            Square square(x, y);
            if (!yourFleet->hasAttacked(square)) {
                correctSquares.push_back(square);
                if (isSquareGood(square)) {
                    goodSquares.push_back(square);
                }
            }
        }
    }
    if (goodSquares.empty()) {
        return correctSquares[rand() % correctSquares.size()];
    } else {
        return goodSquares[rand() % goodSquares.size()];
    }
}

bool BattleshipGame::isSquareGood(Square square) {
	Square squares[4] = {Square :: makeSquare(square.getX(), square.getY() - 1),
	       				 Square :: makeSquare(square.getX(), square.getY() + 1),
	       				 Square :: makeSquare(square.getX() - 1, square.getY()),
	       				 Square :: makeSquare(square.getX() + 1, square.getY())};
	       				 
	bool isInjuriedShip[4];
	for (int i = 0; i < 4; i++) {
        int shipIndex = yourFleet->findShipIndex(squares[i]);
		
		if (!~shipIndex) {
			isInjuriedShip[i] = false;
			continue;
		}
		
        Ship ship = yourFleet->getShips()[shipIndex];
		
		isInjuriedShip[i] = ship.getHP() != ship.getSquares().size() && 
		                    ship.getHP() != 0 && 
                            yourFleet->getSquareState(squares[i].getX(),
							                         squares[i].getY()) == 
                                                     Square::ATTACKED_WITH_SUCCESS;
	}
	
	return isInjuriedShip[0] || isInjuriedShip[1] || 
	       isInjuriedShip[2] || isInjuriedShip[3];
}
