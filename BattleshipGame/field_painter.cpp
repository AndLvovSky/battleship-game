#include "battleship_game.h"
#include "field_painter.h"
//#include <graphics.h>

using namespace battleshipGame;

FieldWidget::FieldPainter::FieldPainter(FieldWidget* fw) :
    WidgetPainter(fw), yours(fw->yours) {}

void FieldWidget::FieldPainter::paint() {
    drawField();
    auto game = BattleshipGame::get();
    if (game.mode == BattleshipGame::Mode::PLACING) {
        drawPlacing();
    } else {
        drawBattle();
    }
}

void FieldWidget::FieldPainter::drawPlacing() {
    if (!yours) {
        return;
    }
    drawFleet();
    auto& game = BattleshipGame::get();
    if (!game.squareSelected) {
        return;
    }
    auto& yourFleet = game.getFleet(yours);
    Ship ship(game.square, game.shipSize, game.shipHorizontal);
    if (game.shipsLast[game.shipSize] &&
        yourFleet.checkPositionForShip(ship)) {
        drawShip(ship, CORRECT_COLOR);
    } else {
        drawShip(ship , INCORRECT_COLOR);
    }
}

void FieldWidget::FieldPainter::drawBattle() {
    //...
}

void FieldWidget::FieldPainter::drawFleet() {
    auto& game = BattleshipGame::get();
    auto& fleet = game.getFleet(yours);
    for (auto ship: fleet.getShips()) {
        if (yours || ship.isSunk()) {
            drawShip(ship, SHIP_COLOR);
        }
    }
}

void FieldWidget::FieldPainter::drawShip(Ship ship, QColor color) {
    auto stp = point(ship.getStartSquare());
    auto ssize = ship.getSize();
    painter->setPen(QPen(color, THICK_STROKE));
    if (ship.isHorizontal()) {
        painter->drawRect(stp.x(), stp.y(), SQ * ssize, SQ);
    } else {
        painter->drawRect(stp.x(), stp.y(), SQ, SQ * ssize);
    }
}

void FieldWidget::FieldPainter::drawField() {
    const auto SIDE = FieldWidget::SIDE;
    const auto SQ = SIDE / 10;
    painter->setPen(FIELD_COLOR);
    for (int i = 1; i < 10; i++) {
        painter->drawLine(SQ * i, 0, SQ * i, SIDE);
        painter->drawLine(0, SQ * i, SIDE, SQ * i);
    }
}

void FieldWidget::FieldPainter::drawSquare(Square square, QColor color) {
    painter->setPen(QPen(color, THICK_STROKE));
    QPoint lt = point(square);
    painter->drawRect(lt.x(), lt.y(), SQ, SQ);
}

QPoint FieldWidget::FieldPainter::point(Square square) {
    return QPoint(square.getX() * SQ, square.getY() * SQ);
}

/*

void Plotter :: 
drawPoint(int fieldX, int fieldY) {
	setcolor(ATACK_COLOR);
	setfillstyle(SOLID_FILL, ATACK_COLOR);
	
	fillellipse(fieldX * SQUARE_SIDE + SQUARE_SIDE / 2,
				fieldY * SQUARE_SIDE + SQUARE_SIDE / 2,
				POINT_RADIUS, POINT_RADIUS);
}

void Plotter :: 
drawCross(int fieldX, int fieldY) {
	setcolor(ATACK_COLOR);
	setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
	
	line(fieldX * SQUARE_SIDE, fieldY * SQUARE_SIDE,
	     (fieldX + 1) * SQUARE_SIDE, (fieldY + 1) * SQUARE_SIDE);
	line(fieldX * SQUARE_SIDE, (fieldY + 1) * SQUARE_SIDE,
	     (fieldX + 1) * SQUARE_SIDE, fieldY * SQUARE_SIDE);
}

void Plotter :: 
drawFleetState(bool isYour, int fieldX, int fieldY) {
	Fleet &fleet = (isYour ? yourFleet : opponentFleet);
	
	for (int i = 0; i < fleet.getShips().size(); i++) {
		if (!fleet.getShips()[i].getHP() || isYour) {
			drawShip(fleet.getShips()[i], fieldX, fieldY);
		}
	}
	
	for (int i = 0; i < BATTLE_FIELD_SIZE; i++) {
		for (int j = 0; j < BATTLE_FIELD_SIZE; j++) {
			switch (fleet.getSquareState(i, j)) {
				case ATTACKED : {
					drawPoint(i + fieldX, j + fieldY);
					break;
				}
				case ATTACKED_WITH_SUCCESS : {
					drawCross(i + fieldX, j + fieldY);
					break;
				}
				default : break;
			}
		}
	}
}
*/
