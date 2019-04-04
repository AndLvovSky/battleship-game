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
    //randomPlacement(*opponentFleet);
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

/*
void Interface :: shiftCurrentSquare(char key) {
	switch (key) {
		case SHIFT_UP : {
			if (currentSquare.getY() != 0) {
				currentSquare.setY(currentSquare.getY() - 1);
			}
			break;
		}
		case SHIFT_DOWN : {
			if (currentSquare.getY() != BATTLE_FIELD_SIZE - 1) {
				currentSquare.setY(currentSquare.getY() + 1);
			}
			break;
		}
		case SHIFT_LEFT : {
			if (currentSquare.getX() != 0) {
				currentSquare.setX(currentSquare.getX() - 1);
			}
			break;
		}
		case SHIFT_RIGHT : {
			if (currentSquare.getX() != BATTLE_FIELD_SIZE - 1) {
				currentSquare.setX(currentSquare.getX() + 1);
			}
			break;
		}
		default : break;
	}
}
	
void Interface :: placeShips() {
	isShipSelected = false;	
	
	shipLast[1] = NUMBER_OF_1_DECKED;
	shipLast[2] = NUMBER_OF_2_DECKED;
	shipLast[3] = NUMBER_OF_3_DECKED;
	shipLast[4] = NUMBER_OF_4_DECKED;
	
	plotter.draw();
	
	int numberOfShipsLast = NUMBER_OF_SHIPS;
	while (numberOfShipsLast) {
		while (!kbhit()) {}
		int key = getch();
		
		if (isShipSelected) {
			if (key == ACCEPT) {
				if (yourFleet.checkPositionForShip(currentSquare, 
				                                   selectedShipSize, 
											       selectedShipOrientation)) {
					Ship ship(currentSquare, selectedShipSize, 
					          selectedShipOrientation);
					yourFleet.addShip(ship);
					
					shipLast[selectedShipSize]--;
					numberOfShipsLast--;
					
					isShipSelected = false;
				} 	
			} else if (key == TURN_SHIP) {
				selectedShipOrientation = !selectedShipOrientation;
			} else {
				shiftCurrentSquare(key);
			}	
		} else {
			isShipSelected = true;
			selectedShipOrientation = true;
			
			switch (key) {
				case '1' : selectedShipSize = 1;   break;
				case '2' : selectedShipSize = 2;   break;
				case '3' : selectedShipSize = 3;   break;
				case '4' : selectedShipSize = 4;   break;
				default  : isShipSelected = false; break;
			}
			
			if (!isShipSelected) continue;
			
			if (!shipLast[selectedShipSize]) {
				isShipSelected = false;
			} else {
				currentSquare.setX(0);
				currentSquare.setY(0);
			}
		}
		
		plotter.draw();
	}
}

bool Interface :: isSquareGood(Square square) {
	Square squares[4] = {Square :: makeSquare(square.getX(), square.getY() - 1),
	       				 Square :: makeSquare(square.getX(), square.getY() + 1),
	       				 Square :: makeSquare(square.getX() - 1, square.getY()),
	       				 Square :: makeSquare(square.getX() + 1, square.getY())};
	       				 
	bool isInjuriedShip[4];
	for (int i = 0; i < 4; i++) {
		int shipIndex = yourFleet.findShipIndex(squares[i]);
		
		if (!~shipIndex) {
			isInjuriedShip[i] = false;
			continue;
		}
		
		Ship ship = yourFleet.getShips()[shipIndex]; 
		
		isInjuriedShip[i] = ship.getHP() != ship.getSquares().size() && 
		                    ship.getHP() != 0 && 
							yourFleet.getSquareState(squares[i].getX(), 
							                         squares[i].getY()) == 
													 ATTACKED_WITH_SUCCESS;
	}
	
	return isInjuriedShip[0] || isInjuriedShip[1] || 
	       isInjuriedShip[2] || isInjuriedShip[3];
}

Square Interface :: findBestSquare() {
	vector <Square> correctSquares;
	for (int x = 0; x < BATTLE_FIELD_SIZE; x++) {
		for (int y = 0; y < BATTLE_FIELD_SIZE; y++) {
			Square square(x, y);
			if (!yourFleet.hasAttacked(square)) {
				correctSquares.push_back(square);
				if (isSquareGood(square)) {
					return square;
				}
			}
		}
	}
	return correctSquares[rand() % correctSquares.size()];
}

void Interface :: randomPlacement(Fleet& fleet) {
	int countsOfShips[5] = {0, NUMBER_OF_1_DECKED, NUMBER_OF_2_DECKED,
						    NUMBER_OF_3_DECKED, NUMBER_OF_4_DECKED};
						    
	for (int size = NUMBER_OF_DIFFERENT_SHIPS; size > 0; size--) {
		bool isOrientationFixed = false, orientation;
		
		for (int i = 0; i < countsOfShips[size]; i++) {
			if (!isOrientationFixed) {
				orientation = rand() % 2;
			}
			
			vector <Square> correctSquares;
			for (int x = 0; x < BATTLE_FIELD_SIZE; x++) {
				for (int y = 0; y < BATTLE_FIELD_SIZE; y++) {
					Square square(x, y);
					if (fleet.checkPositionForShip(square,
												   size, orientation)) {
						correctSquares.push_back(square);
					}
				}
			}
			
			if (correctSquares.empty()) {
				isOrientationFixed = true;
				orientation = !orientation;
				i--;
				continue;
			}
			
			Ship ship(correctSquares[rand() % correctSquares.size()],
			          size, orientation);
			fleet.addShip(ship);
			isOrientationFixed = false;
		}
	}
}

void Interface :: battle() {
	currentSquare.setX(0);
	currentSquare.setY(0);
	isStepYours = true; 
	battleMode = BEFORE_YOUR_STEP_MODE;
	randomPlacement(opponentFleet);
	plotter.draw();
	
	while (yourFleet.getHP() && opponentFleet.getHP()) {
		if (!isStepYours) {
			Sleep(TIME_AFTER_STEP);
			
			battleMode = BEFORE_OPPONENT_STEP_MODE;
			plotter.draw();
			Sleep(TIME_FOR_STEP);
			
			resultOfStep = yourFleet.fire(findBestSquare()); 
			battleMode = AFTER_OPPONENT_STEP_MODE;
			plotter.draw();
			
			if (resultOfStep == BESIDE_SHOT) {
				Sleep(TIME_AFTER_STEP);
				battleMode = BEFORE_YOUR_STEP_MODE;
				isStepYours = true;
			}
			plotter.draw();
			continue;
		}
		
		while (!kbhit()) {}
		int key = getch();
		
		if (key == ACCEPT) {
			if (!opponentFleet.hasAttacked(currentSquare)) {
				resultOfStep = opponentFleet.fire(currentSquare);
				if (resultOfStep == BESIDE_SHOT) {
					currentSquare.setX(0);
					currentSquare.setY(0);
					battleMode = AFTER_YOUR_STEP_MODE;
					isStepYours = false;
				}
			}
		} else {
			shiftCurrentSquare(key);
		}
		
		plotter.draw();
	}
	
	isYouWinner = yourFleet.getHP();
}

void Interface :: refresh() {
	yourFleet.clear();
	opponentFleet.clear();
	gameMode = PLACING_MODE;
	plotter.draw();
}

void Interface :: resume() {
	plotter.draw();
	
	while (!kbhit() && getch() != ACCEPT) {}
	
	refresh();
}

void Interface :: run() {
	plotter.initialize();
	
	srand(time(NULL));
	
	while (true) {
		gameMode = PLACING_MODE;
		placeShips();

		gameMode = BATTLE_MODE;
		battle();
		
		gameMode = RESUME_MODE;
		resume();
	}	
}
*/
