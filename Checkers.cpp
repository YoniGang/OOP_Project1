#include "Checkers.h"
#include "board.h"
#include "player.h"

/********************************************************************************************************************************
	Function Name:			setCheckerLogic	
	Return value:			None
	Description:			The function sets the logic of each checker. The game logic is based on checkers 1,2,3.	
	Dinamically allocated:	None
********************************************************************************************************************************/
void checker::setCheckerLogic()
{
	switch (checkerType)
	{
	case (CHECK1):
		setColsAndRowsCheck1();
		break;

	case (CHECK2):
		setColsAndRowsCheck2();
		break;

	case (CHECK3):
		setColsAndRowsCheck3();
		break;

	default:
		break;
	}
}

/********************************************************************************************************************************
	Function Name:			setColsAndRowsCheck1
	Return value:			None
	Description:			The function sets the game logic for checker 1.
	Dinamically allocated:	None
********************************************************************************************************************************/
void checker::setColsAndRowsCheck1()
{
	int i = 0;
	for (; i < 9+INITIAL_POINT; i++)
		winningRows[i] = true;

	for (i = 0; i < SIZE+INITIAL_POINT; i++)
		winningCols[i] = true;

	winningCols[3+INITIAL_POINT] = false;
	
}

/********************************************************************************************************************************
Function Name:			setColsAndRowsCheck2
Return value:			None
Description:			The function sets the game logic for checker 2.
Dinamically allocated:	None
********************************************************************************************************************************/
void checker::setColsAndRowsCheck2()
{
	winningRows[2] = true;
	winningRows[3] = true;
	winningCols[10] = true;

	alwaysLose = CHECK9;
}

void checker::setColsAndRowsCheck3()
{
	winningRows[7] = true;
	winningCols[6] = true;
}

/********************************************************************************************************************************
Function Name:			setColsAndRowsCheck1
Return value:			None
Description:			The function sets the game logic for checker 3.
Dinamically allocated:	None
********************************************************************************************************************************/
static void swapPlayersPosition(checker **playerAChecker, checker **playerBChecker)
{
	checker *temp = *playerAChecker;
	*playerAChecker = *playerBChecker;
	*playerBChecker = temp;
}

/********************************************************************************************************************************
Function Name:			battleOpponent
Return value:			None
Description:			The function takes two opponent checkers and a battle is occured based on the logic of checkers 1,2,3
Dinamically allocated:	None
********************************************************************************************************************************/
void checker::battleOpponent(checker *playerAChecker, checker *playerBChecker)
{
	checker *playingA = playerAChecker;
	checker *playingB = playerBChecker;
	types checkerAtype = BLANK;  
	types checkerBtype = BLANK;  

	if ((playingA->getType() - CHECK7) >= 0) { swapPlayersPosition(&playingA, &playingB); }
	checkerAtype = playingA->getType();
	checkerBtype = playingB->getType();

	if (playingA->alwaysLose == checkerBtype)
		playingA->setCheckerType(BLANK);

	else if (((playingA->winningCols)[col] == false) || ((playingA->winningRows)[row] == false))
		playingA->setCheckerType(BLANK);

	else
		playingB->setCheckerType(BLANK);

	playingA->getPlayer()->updatePlayer();
	playingB->getPlayer()->updatePlayer();
}

/********************************************************************************************************************************
Function Name:			erase
Return value:			None
Description:			The function sets the current square to the previous state - before any checker waked on the square.
Dinamically allocated:	None
********************************************************************************************************************************/
void checker::erase(checker **& gameBoard)
{
	gameBoard[row][col].setCheckerType(walkedOn);
	eraseDraw();
}

/********************************************************************************************************************************
Function Name:			putCheckerInNewLocation
Return value:			None
Description:			The function sets the current square with the new checker.
Dinamically allocated:	None
********************************************************************************************************************************/
void checker::putCheckerInNewLocation(checker **& gameBoard, types typeToPut)
{
	walkedOn = gameBoard[row][col].getType();
	gameBoard[row][col] = *this;
	gameBoard[row][col].setCheckerType(typeToPut);
	draw(typeToPut, YELLOW);
}

/********************************************************************************************************************************
Function Name:			resetLogic
Return value:			None
Description:			The function resets each checkers winning rows and winning cols.
Dinamically allocated:	None
********************************************************************************************************************************/
void checker::resetLogic(int boardSize)
{
	int i = INITIAL_POINT;

	for (i; i <= boardSize; i++) { winningCols[i] = false; winningRows[i] = false; }
}

/********************************************************************************************************************************
Function Name:			checkBoardLimits
Return value:			bool
Description:			The function checks if the next move will exceed beyond the board limit. returns yes if it does.
Dinamically allocated:	None
********************************************************************************************************************************/
static bool checkBoardLimits(int row, int col, int moveDirRow, int moveDirCol)
{
	if (((moveDirRow + row > SIZE) || (moveDirRow + row < INITIAL_POINT)) || (moveDirCol + col > SIZE) || (moveDirCol + col < INITIAL_POINT))
		return false;

	return true;
}

/********************************************************************************************************************************
Function Name:			eraseDraw
Return value:			None
Description:			Wrapper to draw function.
Dinamically allocated:	None
********************************************************************************************************************************/
void checker::eraseDraw()
{
	draw(walkedOn, BLACK);
}

/********************************************************************************************************************************
Function Name:			stopChecker
Return value:			None
Description:			The function stops the current checker and removes the background color.
Dinamically allocated:	None
********************************************************************************************************************************/
void checker::stopChecker(int backroundColor)
{
	setDirection(Diraction::STOP);
	gotoxyAux(col, row);
	if ((checkerType == CHECK1) || (checkerType == CHECK2) || (checkerType == CHECK3))
	{
		setTextColor(DARK_CYAN, backroundColor);
		std::cout << " " << checkerType << "  ";
	}
	else
	{
		setTextColor(RED, backroundColor);
		std::cout << " " << checkerType << "  ";
	}
}

/********************************************************************************************************************************
Function Name:			draw
Return value:			None
Description:			The function draws the recieved sign in the the checker's position.
Dinamically allocated:	None
********************************************************************************************************************************/
void checker::draw(types sign, int backroundColor)
{
	gotoxyAux(col, row);
	std::cout.flush();

	drawWithColor(sign, backroundColor);

	setTextColor(WHITE);  std::cout << "|";
}

/********************************************************************************************************************************
Function Name:			resetChecker
Return value:			None
Description:			The function resets the checker. everything besides the winning rows and cols.
Dinamically allocated:	None
********************************************************************************************************************************/
void checker::resetChecker(int boardSize)
{
	checkerType = BLANK;
	moveDirRow = 0;
	moveDirCol = 0;
	canMoveSea = false;
	canMoveForest = false;
	resetLogic(boardSize);
	alwaysLose = BLANK;
	walkedOn = BLANK;
	checkerOwner = nullptr;
}

/********************************************************************************************************************************
Function Name:			checkForestOrSea
Return value:			bool
Description:			The function checks if the next move is forest or sea. If it does, it returns true.
Dinamically allocated:	None
********************************************************************************************************************************/
bool checker::checkForestOrSea(types nextMove)
{
	if (((nextMove == SEA) && (true == canMoveSea)) || ((nextMove == FR) && (true == canMoveForest)))
		return true;

	return false;
}

/********************************************************************************************************************************
Function Name:			collisionWithMyOwn
Return value:			bool
Description:			The function checks if the next move is a team-mate checker.If it does, it returns true.
Dinamically allocated:	None
********************************************************************************************************************************/
bool checker::collisionWithMyOwn(types nextMove, types firstChecker, types secondChecker, types thirdChecker)
{
	if ((nextMove == firstChecker) || (nextMove == secondChecker) || (nextMove == thirdChecker))	{ return true; }

	return false;
}

/********************************************************************************************************************************
Function Name:			collisionWithMyOwn
Return value:			bool
Description:			The function checks if the next move is the desired flag. Returns true if it does.
Dinamically allocated:	None
********************************************************************************************************************************/
static bool checkWinning(types nextMove, types winnigFlag)
{
	if (nextMove == winnigFlag) { return true; }

	return false;
}

/********************************************************************************************************************************
Function Name:			collisionWithMyOwn
Return value:			bool
Description:			An auxilary function to the move function.
Dinamically allocated:	None
********************************************************************************************************************************/
bool checker::moveAux(checker**& gameBoard, types winningFlag, types firstChecker, types secondChecker, types thirdChecker)
{
	checker *nextMove = &(gameBoard[row + moveDirRow][col + moveDirCol]);
	types nextMoveType = nextMove->getType();
	types myCurrentType = checkerType;

	if (nextMoveType != BLANK)
	{
		if (collisionWithMyOwn(nextMoveType, firstChecker, secondChecker, thirdChecker))
		{
			stopChecker(YELLOW);
			return false;
		}

		else if ((nextMoveType == FR) || (nextMoveType == SEA))
		{
			if (!(checkForestOrSea(nextMoveType))) { stopChecker(YELLOW); return false; }
		}

		else if ((nextMoveType == FlgA) || (nextMoveType == FlgB))
		{
			if (!checkWinning(nextMoveType, winningFlag)) { stopChecker(YELLOW); return false; }
	
			return true;
		}

		else
		{
			battleOpponent(this, nextMove);
			if (checkerType == BLANK) { stopChecker(BLACK); erase(gameBoard); return false; }
		}
	}
	erase(gameBoard);
	row = row + moveDirRow;
	col = col + moveDirCol;
	putCheckerInNewLocation(gameBoard, myCurrentType);

	return false;
}

/********************************************************************************************************************************
Function Name:			collisionWithMyOwn
Return value:			bool
Description:			The function moves the checker to the desired place. Returns true if the next step is the desired flag.
Dinamically allocated:	None
********************************************************************************************************************************/
bool checker::move(checker**& gameBoard, types winningFlag, types firstChecker, types secondChecker, types thirdChecker)
{
	if (!(checkBoardLimits(row, col, moveDirRow, moveDirCol)))
	{
		stopChecker(YELLOW);
		return false;
	}

	else
		return moveAux(gameBoard, winningFlag, firstChecker, secondChecker, thirdChecker);
}

/********************************************************************************************************************************
Function Name:			setDirection
Return value:			None
Description:			The function sets the walking direction of the checker.
Dinamically allocated:	None
********************************************************************************************************************************/
void checker::setDirection(Diraction dir)
{
	switch (dir)
	{
	case Diraction::UP:
		moveDirRow = -1;
		moveDirCol = 0;
		break;
	case Diraction::DOWN:
		moveDirRow = 1;
		moveDirCol = 0;
		break;
	case Diraction::LEFT:
		moveDirRow = 0;
		moveDirCol = -1;
		break;
	case Diraction::RIGHT:
		moveDirRow = 0;
		moveDirCol = 1;
		break;
	case Diraction::STOP:
		moveDirCol = 0;
		moveDirRow = 0;
		break;
	default:
		break;
	}
}
