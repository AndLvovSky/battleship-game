#include "battleship_game.h"
#include "field_painter.h"
//#include <graphics.h>


using namespace battleshipGame;

FieldWidget::FieldPainter::FieldPainter(FieldWidget* fw) :
    WidgetPainter(fw) {}

void FieldWidget::FieldPainter::paint() {
    const auto SIDE = FieldWidget::SIDE;
    const auto SQ = SIDE / 10;
    painter->setPen(QColor(100, 100, 100));
    for (int i = 1; i < 10; i++) {
        painter->drawLine(SQ * i, 0, SQ * i, SIDE);
        painter->drawLine(0, SQ * i, SIDE, SQ * i);
    }
}

/*
void Plotter :: 
drawBackground() {
	setfillstyle(SOLID_FILL, BACKGROUND_COLOR);
	
	bar(0, 0, MAX_WIDTH, MAX_HEIGHT);
}

void Plotter :: 
drawFrame(int startX, int startY, int finalX, int finalY, 
          int color, int width) {
	setlinestyle(SOLID_LINE, 0, width);
	setcolor(color);
	
	rectangle(startX * SQUARE_SIDE, startY * SQUARE_SIDE,
	          (finalX + 1) * SQUARE_SIDE, (finalY + 1) * SQUARE_SIDE);
}

void Plotter :: 
printText(int fieldX, int fieldY, string text, int color) {
    setbkcolor(BACKGROUND_COLOR);
    setcolor(color);
    settextstyle(MAIN_FONT, 0, MAIN_FONT_SIZE);
    
	outtextxy(fieldX * SQUARE_SIDE, fieldY * SQUARE_SIDE, toCString(text));
}

void Plotter :: 
drawField(int x, int y, string name) {
	for (int i = 0; i < BATTLE_FIELD_SIZE; i++) {
		printText(x - 2, y + i, toCString(i + 1), TEXT_COLOR);
		printText(x + i, y - 2, toCString(char('A' + i)), TEXT_COLOR);
	}
	
	setcolor(FIELD_GRID_COLOR);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	for (int i = 1; i < BATTLE_FIELD_SIZE; i++) {
		line((i + x) * SQUARE_SIDE, y * SQUARE_SIDE, 
		     (i + x) * SQUARE_SIDE, (y + BATTLE_FIELD_SIZE) * SQUARE_SIDE);
		line(x * SQUARE_SIDE, (i + y) * SQUARE_SIDE, 
		     (x + BATTLE_FIELD_SIZE) * SQUARE_SIDE, (i + y) * SQUARE_SIDE);
	}
	
	printText(x, y + BATTLE_FIELD_SIZE + 1, toCString(name), TEXT_COLOR);
	
	drawFrame(x, y, x + BATTLE_FIELD_SIZE - 1, y + BATTLE_FIELD_SIZE - 1, 
	                                   FIELD_BORDER_COLOR, THICK_WIDTH);
}

void Plotter :: 
drawFleetsFields() {
	drawField(YOUR_FIELD_X, YOUR_FIELD_Y, "Your fleet");
	drawField(OPPONENT_FIELD_X, OPPONENT_FIELD_Y, "Opponent fleet");
}

void Plotter :: 
drawShip(Ship ship, int fieldX, int fieldY) {
	Square startSquare, finalSquare;
	startSquare.setX(ship.getSquares()[0].getX() + fieldX);
	startSquare.setY(ship.getSquares()[0].getY() + fieldY);
	finalSquare.setX(ship.getSquares()[ship.getSquares().size() - 1].getX() + fieldX);
	finalSquare.setY(ship.getSquares()[ship.getSquares().size() - 1].getY() + fieldY);
	
	drawFrame(startSquare.getX(), startSquare.getY(),
	          finalSquare.getX(), finalSquare.getY(),
			  SHIP_COLOR, THICK_WIDTH);
}

void Plotter :: 
printHelpText(string firstHelpLine, string secondHelpLine, 
              string thirdHelpLine) {
	printText(FIRST_HELP_X, FIRST_HELP_Y, firstHelpLine, HELP_TEXT_COLOR);
	printText(SECOND_HELP_X, SECOND_HELP_Y, secondHelpLine, HELP_TEXT_COLOR);
	printText(THIRD_HELP_X, THIRD_HELP_Y, thirdHelpLine, HELP_TEXT_COLOR);
}

void Plotter :: 
printGameStateText(string firstStateLine, string secondStateLine, 
                        string thirdStateLine) {
	printText(FIRST_GAME_STATE_X, FIRST_GAME_STATE_Y, firstStateLine, TEXT_COLOR);
	printText(SECOND_GAME_STATE_X, SECOND_GAME_STATE_Y, secondStateLine, TEXT_COLOR);
	printText(THIRD_GAME_STATE_X, THIRD_GAME_STATE_Y, thirdStateLine, TEXT_COLOR);
}

void Plotter :: 
printPlacingHelp() {
	string firstHelpLine, firstStateLine, 
	       secondHelpLine = "", secondStateLine = "",
	       thirdHelpLine = "", thirdStateLine = "";
	       
	if (!isShipSelected) {
		firstHelpLine = "Press key from 1 to 4 to choose ship";
		          
		firstStateLine = "Ships last (from 1-decked to 4-decked): ";
		for (int i = 1; i <= NUMBER_OF_DIFFERENT_SHIPS; i++) {
			firstStateLine += char(shipLast[i] + '0');
			if (i != NUMBER_OF_DIFFERENT_SHIPS) {
				firstStateLine += ", ";
			}
		}
	} else {
		firstHelpLine = "SPACE - change orientation";
		secondHelpLine = "ENTER - place ship";
		thirdHelpLine = "W-S-A-D - change start square"; 
		          
		firstStateLine = "Size of selected ship = ";
		firstStateLine += char(selectedShipSize + '0');
		secondStateLine = (string)"Ship orientation: " + 
		                  (string)(selectedShipOrientation ? "horizontal" : "vertical");	
	}
	
	printHelpText(firstHelpLine, secondHelpLine, thirdHelpLine);
	printGameStateText(firstStateLine, secondStateLine, thirdStateLine);
}

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

void Plotter :: 
drawYourFleetState() {
	drawFleetState(true, YOUR_FIELD_X, YOUR_FIELD_Y);
}

void Plotter :: 
drawOpponentFleetState() {
	drawFleetState(false, OPPONENT_FIELD_X, OPPONENT_FIELD_Y);
}

void Plotter :: 
printBattleHelp() {
	string firstHelpLine, firstStateLine, 
	       secondHelpLine = "", secondStateLine = "",
	       thirdHelpLine = "", thirdStateLine = "";
	       
	switch (battleMode) {
		case BEFORE_YOUR_STEP_MODE : {
			firstHelpLine = "Choose square to fire";
			firstStateLine = "";
			break;
		} 
		case AFTER_YOUR_STEP_MODE : {
			switch (resultOfStep) {
				case BESIDE_SHOT : {
					firstStateLine = "Beside(";
					break;
				}
				case INJURE_SHOT : {
					firstStateLine = "Injured)";
					break;
				}
				case SINK_SHOT : {
					firstStateLine = "Sinked)))";
					break;
				}
			}
			firstHelpLine = "";
			break;
		} 
		case BEFORE_OPPONENT_STEP_MODE : {
			firstHelpLine = "Opponent is thinking...";
			firstStateLine = "";
			break;
		} 
		case AFTER_OPPONENT_STEP_MODE : {
			switch (resultOfStep) {
				case BESIDE_SHOT : {
					firstStateLine = "Beside)";
					break;
				}
				case INJURE_SHOT : {
					firstStateLine = "Injured(";
					break;
				}
				case SINK_SHOT : {
					firstStateLine = "Sinked(((";
					break;
				}
			}
			firstHelpLine = "";
			break;
		}
		default : break; 
	}
	
	printHelpText(firstHelpLine, secondHelpLine, thirdHelpLine);
	printGameStateText(firstStateLine, secondStateLine, thirdStateLine);
}

void Plotter :: 
printResumeHelp() {
	string firstHelpLine, firstStateLine, 
	       secondHelpLine = "", secondStateLine = "",
	       thirdHelpLine = "", thirdStateLine = "";
	       
	firstHelpLine = "Press key ENTER to start again";
	if (isYouWinner) {
		firstStateLine = "You are winner!!!";
	} else {
		firstStateLine = "You are loser(((";
	}
	
	printHelpText(firstHelpLine, secondHelpLine, thirdHelpLine);
	printGameStateText(firstStateLine, secondStateLine, thirdStateLine);
}

void Plotter :: 
highlightSquare(Square square, int fieldX, int fieldY) {
	drawFrame(square.getX() + fieldX, square.getY() + fieldY,
		      square.getX() + fieldX, square.getY() + fieldY,
			  HIGHLIGHT_COLOR, THICK_WIDTH);
}

void Plotter :: 
drawPlacing() {
	drawFleetsFields();
	drawYourFleetState();
	if (isShipSelected) {
		highlightSquare(currentSquare, YOUR_FIELD_X, YOUR_FIELD_Y);
	}
	printPlacingHelp();
}

void Plotter :: drawBattle() {
	drawFleetsFields();
	drawYourFleetState();
	drawOpponentFleetState();
	if (isStepYours) {
		highlightSquare(currentSquare, OPPONENT_FIELD_X, OPPONENT_FIELD_Y);
	}
	printBattleHelp();
}

void Plotter :: 
drawResume() {
	drawFleetsFields();
	drawYourFleetState();
	drawOpponentFleetState();
	printResumeHelp();
}

Square 
Plotter :: 
getFleetSquareFrom(int x, int y, int startY, int startX) {
	for (int i = startX; i < BATTLE_FIELD_SIZE + startX; i++) {
		for (int j = startY; j < BATTLE_FIELD_SIZE + startY; j++) {
			if (x >= i * SQUARE_SIDE && x <= (i + 1) * SQUARE_SIDE &&
			    y >= j * SQUARE_SIDE && y <= (j + 1) * SQUARE_SIDE) {
				return Square :: makeSquare(i - startX, j - startY);    	
			}
		}
	}
	return Square :: makeSquare(-1, -1);
}

Square 
Plotter :: 
getYourFleetSquare(int x, int y) {
	return getFleetSquareFrom(x, y, YOUR_FIELD_X, YOUR_FIELD_Y);
}

Square 
Plotter :: 
getOpponentFleetSquare(int x, int y) {
	return getFleetSquareFrom(x, y, OPPONENT_FIELD_X, OPPONENT_FIELD_Y);
}
	
void Plotter :: 
initialize() {
	initwindow(MAX_WIDTH, MAX_HEIGHT);
}

void Plotter :: 
draw() {
	drawBackground();
	switch (gameMode) {
		case PLACING_MODE : drawPlacing(); break;
		case BATTLE_MODE  : drawBattle();  break;
		case RESUME_MODE  : drawResume();  break;
		default : break;
	}
}
*/
