#include <iostream>
#include "square.h"

using namespace std;
using namespace battleshipGame;

Square :: Square() {
	x = y = 0;
}
	
Square :: Square(int x, int y) {
	this->x = x;
	this->y = y;
}

Square 
Square :: makeSquare(int x, int y) {
	Square square(x, y);
	return square;
}

int Square :: getX() {
	return this->x;
}

void Square :: setX(int x) {
	this->x = x;
}

int Square :: getY() {
	return this->y;
}

void Square :: setY(int y) {
	this->y = y;
}

bool Square :: operator == (Square square) {
	return this->x == square.getX() &&
		   this->y == square.getY();
}
