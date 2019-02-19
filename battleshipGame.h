#ifndef BATTLESHIP_GAME
#define BATTLESHIP_GAME

#include <iostream>
#include <vector>
#include <graphics.h>
#include <ctime>

using namespace std;

namespace battleshipGameNamespace {
	
	static const int PLACING_MODE = 1,
					 BATTLE_MODE = 2,
					 RESUME_MODE = 3,
					 BEFORE_YOUR_STEP_MODE = 1,
					 AFTER_YOUR_STEP_MODE = 2,
					 BEFORE_OPPONENT_STEP_MODE = 3,
					 AFTER_OPPONENT_STEP_MODE = 4,
					 
					 BESIDE_SHOT = 1,
					 INJURE_SHOT = 2,
					 SINK_SHOT = 3,
					 
					 BATTLE_FIELD_SIZE = 10,
					 NUMBER_OF_SHIPS = 10,
					 NUMBER_OF_DIFFERENT_SHIPS = 4,
					 NUMBER_OF_1_DECKED = 4,
					 NUMBER_OF_2_DECKED = 3,
					 NUMBER_OF_3_DECKED = 2,
					 NUMBER_OF_4_DECKED = 1,
					 
					 TIME_FOR_STEP = 2000,
					 TIME_AFTER_STEP = 2000;
			  
	enum SquareState {
		NOT_ATTACKED, 
		ATTACKED, 
		ATTACKED_WITH_SUCCESS
	};
	
	class Square {
			
		private:
			
		int x, y;
		
		public:
			
		Square();
		Square(int, int);
		static Square makeSquare(int, int);
		int getX();
		void setX(int);
		int getY();
		void setY(int);
		bool operator == (Square);
	};
	
	class Ship {
		
		private:
			
		vector <Square> squares;
		int hP;
		
		public:
		
		Ship(Square startSquare, int shipSize, bool orientation);
		int getHP();
		void setHP(int);
		vector <Square> getSquares();
	};
	
	class Fleet {
		
		private:
		
		vector <Ship> ships;
		SquareState squaresState[BATTLE_FIELD_SIZE][BATTLE_FIELD_SIZE];
		
		public:
			
		Fleet();
		int findShipIndex(Square);
		bool checkPositionForSquare(Square);
		bool checkPositionForShip(Square startSquare, int shipSize, bool orientation);
		void addShip(Ship);
		int fire(Square);
		bool hasAttacked(Square);
		int getHP();
		SquareState setSquareState(int x, int y, SquareState squareState);
		SquareState getSquareState(int x, int y);
		vector <Ship> getShips();
		void clear();
	};
	
	static int gameMode;
	static Fleet yourFleet, opponentFleet;
	static Square currentSquare;
	
	static int shipLast[NUMBER_OF_DIFFERENT_SHIPS + 1];
	static bool isShipSelected;
	static int selectedShipSize;
	static bool selectedShipOrientation;
	
	static bool isStepYours;
	static int battleMode;
	static int resultOfStep;
	
	static bool isYouWinner;
	                 
	class Plotter {
		
		private:
			
		static const int MAX_HEIGHT = 600, MAX_WIDTH = 700,
		 				 SQUARE_SIDE = 20,
		 				 POINT_RADIUS = SQUARE_SIDE / 10,
		 				 
	                 	 BACKGROUND_COLOR = WHITE,
	                 	 TEXT_COLOR = BLACK, 
						 FIELD_GRID_COLOR = LIGHTGRAY, FIELD_BORDER_COLOR = BLACK,
	                 	 HELP_TEXT_COLOR = RED, 
						 SHIP_COLOR = BLUE, 
						 HIGHLIGHT_COLOR = YELLOW, 
						 ATACK_COLOR = RED,
						 
						 YOUR_FIELD_X = 3, YOUR_FIELD_Y = 3,
	                 	 OPPONENT_FIELD_X = 17, OPPONENT_FIELD_Y = YOUR_FIELD_Y,
						 FIRST_HELP_X = 5, FIRST_HELP_Y = 18, 
						 SECOND_HELP_X = 5, SECOND_HELP_Y = 20, 
						 THIRD_HELP_X = 5, THIRD_HELP_Y = 22, 
						 FIRST_GAME_STATE_X = 5, FIRST_GAME_STATE_Y = 24, 
						 SECOND_GAME_STATE_X = 5, SECOND_GAME_STATE_Y = 26,
						 THIRD_GAME_STATE_X = 5, THIRD_GAME_STATE_Y = 28,
						 
						 MAIN_FONT = 3, MAIN_FONT_SIZE = 2;

		void drawBackground();
		void drawFrame(int startX, int startY, int finalX, int finalY, 
		               int color, int width);
		void printText(int fieldX, int fieldY, string text, int color);
		void drawField(int x, int y, string name);
		void drawFleetsFields();
		void drawShip(Ship ship, int fieldX, int fieldY);
		void printHelpText(string firstHelpLine, string secondHelpLine, 
		                   string thirdHelpLine);
		void printGameStateText(string firstStateLine, string secondStateLine, 
		                        string thirdStateLine);
		void printPlacingHelp();
		void drawPoint(int fieldX, int fieldY);
		void drawCross(int fieldX, int fieldY);
		void drawFleetState(bool isYour, int fieldX, int fieldY);
		void drawYourFleetState();
		void drawOpponentFleetState();
		void printBattleHelp();
		void printResumeHelp();
		void highlightSquare(Square square, int fieldX, int fieldY);
		void drawPlacing();
		void drawBattle();
		void drawResume();
		Square getFleetSquareFrom(int x, int y, int startY, int startX);
		Square getYourFleetSquare(int x, int y);
		Square getOpponentFleetSquare(int x, int y);
		
		public:
			
		void initialize();
		void draw();
	};
	
	class Interface {
		
		private:
			
		static const char SHIFT_UP = 'w',
		                  SHIFT_DOWN = 's',
		                  SHIFT_LEFT = 'a',
		                  SHIFT_RIGHT = 'd',
		                  ACCEPT = '\r',
		                  TURN_SHIP = ' ';
		
		Plotter plotter;
			
		void shiftCurrentSquare(char key);
		void placeShips();
		bool isSquareGood(Square);
		Square findBestSquare();
		void randomPlacement(Fleet&);
		void battle();
		void refresh();
		void resume();
		
		public:
			
		void run();
	};
	
	#include "square.h"
	#include "ship.h"
	#include "fleet.h"
	#include "plotter.h"
	#include "interface.h"
}

class BattleshipGame {
	
	public:
		
	void play() {
		battleshipGameNamespace :: Interface gameInterface;	
		
		gameInterface.run();
	}
};

#endif // BATTLESHIP_GAME
