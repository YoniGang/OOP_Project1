#include <iostream>
#include <ctime>
#include <cstdlib>
#include <Windows.h>

#include "board.h"
#include "Utils.h"

/********************************************************************************************************************************
Function Name:			emptyBoard
Return value:			None
Description:			The function sets all the checkers to BLANK types (empty cells).
Dinamically allocated:	None
********************************************************************************************************************************/
void board::emptyBoard(checker**& gameBoard)
{
	int row = 0;
	int col = 0;

	for (row = 0; row < _boardSize + INITIAL_POINT; row++)
		for (col = 0; col < _boardSize + INITIAL_POINT; col++)
		{
			gameBoard[row][col].setCheckerType(BLANK);
			gameBoard[row][col].setPosition(col, row);
		}
}

/********************************************************************************************************************************
Function Name:			setFlags
Return value:			None
Description:			The function sets both flags on the board - default mode (!)
Dinamically allocated:	None
********************************************************************************************************************************/
static void setFlags(checker**& gameBoard) 
{	
	gameBoard[12 + INITIAL_POINT][1 + INITIAL_POINT].setCheckerType(FlgB);
	gameBoard[12 + INITIAL_POINT][1 + INITIAL_POINT].setPosition(1 + INITIAL_POINT, 12 + INITIAL_POINT);
	gameBoard[0 + INITIAL_POINT][10 + INITIAL_POINT].setCheckerType(FlgA);
	gameBoard[0 + INITIAL_POINT][10 + INITIAL_POINT].setPosition(10 + INITIAL_POINT, 0 + INITIAL_POINT);
};

/********************************************************************************************************************************
Function Name:			setForestAndSeaAux
Return value:			None
Description:			Auxilary function to set forest and sea.
Dinamically allocated:	None
********************************************************************************************************************************/
static void setForestAndSeaAux(checker**& gameBoard, int row, int col, types type)
{
	gameBoard[row][col].setCheckerType(type);
	gameBoard[row][col].setPosition(col, row);
}

/********************************************************************************************************************************
Function Name:			setForest
Return value:			None
Description:			The function sets the forest squars - default mode (!)
Dinamically allocated:	None
********************************************************************************************************************************/
static void setForest(checker**& gameBoard)
{
	setForestAndSeaAux(gameBoard, 3 + INITIAL_POINT, 2 + INITIAL_POINT, FR);
	setForestAndSeaAux(gameBoard, 4 + INITIAL_POINT, 2 + INITIAL_POINT, FR);
	setForestAndSeaAux(gameBoard, 5 + INITIAL_POINT, 2 + INITIAL_POINT, FR);
	setForestAndSeaAux(gameBoard, 5 + INITIAL_POINT, 3 + INITIAL_POINT, FR);

	for (int i = 0; i < 4; i++) { setForestAndSeaAux(gameBoard, 6 + INITIAL_POINT, i + INITIAL_POINT, FR); };
	setForestAndSeaAux(gameBoard, 7 + INITIAL_POINT, 0 + INITIAL_POINT, FR);
	setForestAndSeaAux(gameBoard, 7 + INITIAL_POINT, 3 + INITIAL_POINT, FR);
	setForestAndSeaAux(gameBoard, 8 + INITIAL_POINT, 3 + INITIAL_POINT, FR);
}

/********************************************************************************************************************************
Function Name:			setSea
Return value:			None
Description:			The function sets the sea squars - default mode (!)
Dinamically allocated:	None
********************************************************************************************************************************/
static void setSea(checker**& gameBoard)
{
	setForestAndSeaAux(gameBoard, 3 + INITIAL_POINT, 9 + INITIAL_POINT, SEA);
	setForestAndSeaAux(gameBoard, 4 + INITIAL_POINT, 8 + INITIAL_POINT, SEA);
	setForestAndSeaAux(gameBoard, 4 + INITIAL_POINT, 9 + INITIAL_POINT, SEA);

	for (int i = 0; i < 3; i++) { setForestAndSeaAux(gameBoard, 5 + INITIAL_POINT, 7 + i + INITIAL_POINT, SEA); };
	setForestAndSeaAux(gameBoard, 6 + INITIAL_POINT, 9 + INITIAL_POINT, SEA);
	setForestAndSeaAux(gameBoard, 6 + INITIAL_POINT, 10 + INITIAL_POINT, SEA);

	for (int i = 0; i < 3; i++) { setForestAndSeaAux(gameBoard, 7 + INITIAL_POINT, 9 + i + INITIAL_POINT, SEA); };
	setForestAndSeaAux(gameBoard, 8 + INITIAL_POINT, 9 + INITIAL_POINT, SEA);
	setForestAndSeaAux(gameBoard, 8 + INITIAL_POINT, 10 + INITIAL_POINT, SEA);
	setForestAndSeaAux(gameBoard, 9 + INITIAL_POINT, 9 + INITIAL_POINT, SEA);

}

/********************************************************************************************************************************
Function Name:			setForestAndSeaAux
Return value:			checker*
Description:			The function randomises checkers on a ready board.
Dinamically allocated:	None
********************************************************************************************************************************/
checker* board::randomisePlayerChecker(types checkerToRandom)
{
	int offset = 0;
	int randVal = 0;
	char col = 0;
	char row = 0;
	std::srand(std::time(0));

	if (checkerToRandom > CHECK3) { offset = 8; };

	while (true)
	{
		randVal = std::rand();
		row = (randVal % 5) + INITIAL_POINT + offset;
		col = (randVal % _boardSize) + INITIAL_POINT;

		if ((gameBoard[row][col].getType()) == BLANK)
		{
			gameBoard[row][col].setCheckerType(checkerToRandom);
			gameBoard[row][col].setPosition(col, row);
			return &gameBoard[row][col];
		}
	}
}

/********************************************************************************************************************************
Function Name:			printBoard
Return value:			None
Description:			The function prints the board.
Dinamically allocated:	None
********************************************************************************************************************************/
void board::printBoard()
{
	int row = 0;
	int col = 0;

	for (; row < _boardSize+INITIAL_POINT; row++)
	{
		for (col = 0; col <= (_boardSize+INITIAL_POINT)*5; col++)
			std::cout << '-';
		std::cout << std::endl;
		std::cout << '|';

		for (col = 0; col < _boardSize+INITIAL_POINT; col++)
		{
			if (gameBoard[row][col].getType() == BLANK)
			{
				if (col == 0 && row > 0 && row <= 9)
					std::cout << " " << row << "  ";
				else if (col == 0 && row > 0 && row > 9)
					std::cout << " " << row << " ";
				else if (col > 0 && row == 0)
					std::cout << " " << (char)('A' + col - 1) << "  ";
				else
					std::cout << "    ";
			}
			else
				drawWithColor(gameBoard[row][col].getType(), BLACK);

			setTextColor(WHITE);  std::cout << "|";
		}
		std::cout << std::endl;
	}
	for (col = 0; col <= (_boardSize+INITIAL_POINT) * 5; col++)
		std::cout << '-';
	std::cout << std::endl;
}

/********************************************************************************************************************************
Function Name:			needToReset
Return value:			bool
Description:			The function checks if the square needs to be reseted. Returns true if is one of the players checkers.
Dinamically allocated:	None
********************************************************************************************************************************/
static bool needToReset(types check)
{
	if ((check == CHECK1) || (check ==  CHECK2) || (check == CHECK3) || (check == CHECK7) || (check == CHECK8) || (check == CHECK9)) 
		return true; 

	return false;
}

/********************************************************************************************************************************
Function Name:			resetBoard
Return value:			None
Description:			The function resets the board before the next game.
Dinamically allocated:	None
********************************************************************************************************************************/
void board::resetBoard(void)
{
	int row = 0;
	int col = 0;

	for (; row <= _boardSize; row++)
	{
		for (col = 0; col <= _boardSize; col++)
		{
			if (needToReset(gameBoard[row][col].getType()))
				gameBoard[row][col].resetChecker(_boardSize);
		}
	}
}

/********************************************************************************************************************************
Function Name:			createBoard
Return value:			None
Description:			The function creates the board by calling all the checkers setters.
Dinamically allocated:	None
********************************************************************************************************************************/
void board::createBoard(void)
{
	emptyBoard(gameBoard);
	setFlags(gameBoard);
	setForest(gameBoard);
	setSea(gameBoard);
}

/********************************************************************************************************************************
Function Name:			drawWithColor
Return value:			None
Description:			The function draws the checkers with the correct color. Used mostly by the print board function.
Dinamically allocated:	None
********************************************************************************************************************************/
void drawWithColor(types type, int backroundColor)
{
	if (type == BLANK) { setTextColor(BLACK); std::cout << "    ";}
	else if (type == FlgA) { setTextColor(DARK_CYAN); std::cout << ' ' << (char) 223 << (char)186 << ' '; }
	else if (type == FlgB) { setTextColor(RED); std::cout << ' ' << (char)223 << (char)186 << ' '; }
	else if (type == FR) { setTextColor(GREEN, DARK_GREEN); std::cout << " ^^ "; }
	else if (type == SEA) { setTextColor(BLUE, DARK_BLUE);  std::cout << " ~~ "; }
	else
	{
		if ((type == CHECK1) || (type == CHECK2) || (type == CHECK3))
		{
			setTextColor(DARK_CYAN, backroundColor);
			std::cout << " " << type << "  ";
		}
		else
		{
			setTextColor(RED, backroundColor);
			std::cout << " " << type << "  ";
		}
	}
}
