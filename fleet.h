#include <iostream>
#include "battleshipGame.h"

using namespace std;

Fleet :: Fleet() {
	for (int i = 0; i < BATTLE_FIELD_SIZE; i++) {
		for (int j = 0; j < BATTLE_FIELD_SIZE; j++) {
			squaresState[i][j] = NOT_ATTACKED;
		}
	}
}

int Fleet :: findShipIndex(Square square) {
	for (int i = 0; i < ships.size(); i++) {
		for (int j = 0; j < ships[i].getSquares().size(); j++) {
			if (ships[i].getSquares()[j] == square) {
				return i;
			}
		}
	}
	return -1;
}

bool Fleet :: checkPositionForSquare(Square square) {
	if (square.getX() < 0 || square.getX() >= BATTLE_FIELD_SIZE ||
		square.getY() < 0 || square.getY() >= BATTLE_FIELD_SIZE ||
		~findShipIndex(square)) {
		return false;		
	}
	
	for (int dX = -1; dX <= 1; dX++) {
		for (int dY = -1; dY <= 1; dY++) {
			if (!(dX || dY)) {
				continue;
			}
			
			Square currentSquare(square.getX() + dX, square.getY() + dY);
			if (currentSquare.getX() >= 0 && currentSquare.getX() < BATTLE_FIELD_SIZE &&
				currentSquare.getY() >= 0 && currentSquare.getY() < BATTLE_FIELD_SIZE &&
				~findShipIndex(currentSquare)) {
				return false;		
			}
		}
	}
	return true;
}

bool Fleet :: checkPositionForShip(Square startSquare, int shipSize, bool orientation) {
	if (orientation) {
		for (int x = startSquare.getX(); x < startSquare.getX() + shipSize; x++) {
			Square square(x, startSquare.getY());
			if (!checkPositionForSquare(square)) {
				return false;
			}
		}
	} else {
		for (int y = startSquare.getY(); y < startSquare.getY() + shipSize; y++) {
			Square square(startSquare.getX(), y);
			if (!checkPositionForSquare(square)) {
				return false;
			}
		}
	}
	return true;
}

void Fleet :: addShip(Ship ship) {
	ships.push_back(ship);
}

int Fleet :: fire(Square square) {
	int attackedShip = findShipIndex(square);
	
	if (attackedShip == -1) {
		squaresState[square.getX()][square.getY()] = ATTACKED;
		return BESIDE_SHOT;
	}
	
	squaresState[square.getX()][square.getY()] = ATTACKED_WITH_SUCCESS;
	ships[attackedShip].setHP(ships[attackedShip].getHP() - 1);
	
	if (!ships[attackedShip].getHP()) {
		for (int i = 0; i < ships[attackedShip].getSquares().size(); i++) {
			Square currentSquare = ships[attackedShip].getSquares()[i];
			for (int dX = -1; dX <= 1; dX++) {
				for (int dY = -1; dY <= 1; dY++) {
					if (!(dX || dY)) {
						continue;
					}
					
					Square adjacenctSquare(currentSquare.getX() + dX, 
					                       currentSquare.getY() + dY);
					if (adjacenctSquare.getX() >= 0 && 
					    adjacenctSquare.getX() < BATTLE_FIELD_SIZE &&
						adjacenctSquare.getY() >= 0 && 
					    adjacenctSquare.getY() < BATTLE_FIELD_SIZE &&
						squaresState[adjacenctSquare.getX()]
						            [adjacenctSquare.getY()] != 
						ATTACKED_WITH_SUCCESS) {
					    squaresState[adjacenctSquare.getX()]
						            [adjacenctSquare.getY()] = ATTACKED;
					}
				}
			}
		}
		return SINK_SHOT; 
	} 
	if (ships[attackedShip].getSquares().size() - 
		       ships[attackedShip].getHP() >= 2) {
		bool orientation = ships[attackedShip].getSquares()[0].getY() ==
					  	   ships[attackedShip].getSquares()[1].getY();
			
		if (orientation) {
			for (int i = 0; i < ships[attackedShip].getSquares().size(); i++) {
				Square currentSquare = ships[attackedShip].getSquares()[i];
				if (squaresState[currentSquare.getX()][currentSquare.getY()] !=
				    ATTACKED_WITH_SUCCESS) {
					continue;    	
				}
				
				if (currentSquare.getY() != 0) {
					squaresState[currentSquare.getX()][currentSquare.getY() - 1] = ATTACKED;
				}
				if (currentSquare.getY() != BATTLE_FIELD_SIZE - 1) {
					squaresState[currentSquare.getX()][currentSquare.getY() + 1] = ATTACKED;
				}
			}
		} else {
			for (int i = 0; i < ships[attackedShip].getSquares().size(); i++) {
				Square currentSquare = ships[attackedShip].getSquares()[i];
				if (squaresState[currentSquare.getX()][currentSquare.getY()] !=
				    ATTACKED_WITH_SUCCESS) {
					continue;    	
				}
				
				if (currentSquare.getX() != 0) {
					squaresState[currentSquare.getX() - 1][currentSquare.getY()] = ATTACKED;
				}
				if (currentSquare.getX() != BATTLE_FIELD_SIZE - 1) {
					squaresState[currentSquare.getX() + 1][currentSquare.getY()] = ATTACKED;
				}
			}
		}
	}
	return INJURE_SHOT;
}

bool Fleet :: hasAttacked(Square square) {
	return squaresState[square.getX()][square.getY()] != NOT_ATTACKED;
}

int Fleet :: getHP() {
	int sumHPs = 0;
	for (int i = 0; i < ships.size(); i++) {
		sumHPs += ships[i].getHP();
	}
	return sumHPs;
}

SquareState Fleet :: setSquareState(int x, int y, SquareState squareState) {
	return this->squaresState[x][y] = squareState;
}

SquareState Fleet :: getSquareState(int x, int y) {
	return this->squaresState[x][y];
}

vector <Ship> Fleet :: getShips() {
	return this->ships;
}

void Fleet :: clear() {
	ships.clear();
	
	for (int i = 0; i < BATTLE_FIELD_SIZE; i++) {
		for (int j = 0; j < BATTLE_FIELD_SIZE; j++) {
			squaresState[i][j] = NOT_ATTACKED;
		}
	}
}
