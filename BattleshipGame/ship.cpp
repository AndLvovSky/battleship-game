#include <iostream>
#include <vector>
#include "ship.h"

using namespace std;
using namespace battleshipGame;

Ship :: Ship(Square startSquare, int shipSize, bool horizontal) {
    if (horizontal) {
		for (int x = startSquare.getX(); x < startSquare.getX() + shipSize; x++) {
			Square square(x, startSquare.getY());
			this->squares.push_back(square);
		}
	} else {
		for (int y = startSquare.getY(); y < startSquare.getY() + shipSize; y++) {
			Square square(startSquare.getX(), y);
			this->squares.push_back(square);
		}
	}
	this->hP = shipSize;
}

int Ship :: getHP() {
	return this->hP;
}

void Ship :: setHP(int hP) {
	this->hP = hP;
}

vector <Square> Ship :: getSquares() {
	return this->squares;
}

Square Ship::getStartSquare() {
    return squares[0];
}

int Ship::getSize() {
    return  squares.size();
}

bool Ship::isHorizontal() {
    return squares.size() == 1 ||
        squares[0].getY() == squares[1].getY();
}

bool Ship::isSunk() {
    return !hP;
}
