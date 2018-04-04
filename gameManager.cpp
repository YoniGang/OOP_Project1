#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#include "gameManager.h"
#include "secondaryMenu.h"

#define	ESC_KEY	27

/********************************************************************************************************************************
Function Name:			activateSecondaryMenu
Return value:			bool
Description:			prints the secondary menu modul.
Dinamically allocated:	None
********************************************************************************************************************************/
static bool activateSecondaryMenu(secondaryMenu& sm)
{
	setTextColor(WHITE, BLACK);
	clearScreen();
	return (sm.printMenuAndTakeUserChoice());
}

/********************************************************************************************************************************
Function Name:			connectSecondaryMenu
Return value:			None
Description:			Connects the secondary menu module with the game board module and the primary menu module.
Dinamically allocated:	None
********************************************************************************************************************************/
void gameManager::connectSecondaryMenu(secondaryMenu& sm)
{
	sm.setGameManager(this);
	//sm.setPrimaryMenu(&_primarymenu);
}

/********************************************************************************************************************************
Function Name:			run
Return value:			None
Description:			Runs the game.
Dinamically allocated:	None
********************************************************************************************************************************/
void gameManager::run(bool reversedScore)
{
	time_t i = time(NULL);
	checker**& myGameBoard = gameBoard.getBoard();
	secondaryMenu sm;
	char choice;
	bool breakGame = false;
	connectSecondaryMenu(sm);

	prepareForGame();

	while (true)
	{
		Sleep(150);
		if (_kbhit())
		{
			choice = tolower(_getch());
			if (choice == ESC_KEY) { if (breakGame = activateSecondaryMenu(sm)) { break; } };
			if (playerA.pressesKey(myGameBoard, choice)) { reversedScore ? playerB.addToScore() : playerA.addToScore(); break; }
			if (playerB.pressesKey(myGameBoard, choice)) { reversedScore ? playerA.addToScore() : playerB.addToScore(); break; }
		}
		else
		{
			if (((i++) % 2) == 0)
				{ if (playerA.moveWithoutPressedKey(myGameBoard)) { reversedScore ? playerB.addToScore() : playerA.addToScore(); break; } }
			else 
				{ if (playerB.moveWithoutPressedKey(myGameBoard)) { reversedScore ? playerA.addToScore() : playerB.addToScore(); break; } }
		}

		if (playerA.areAllDead())		{ reversedScore ? playerA.addToScore() : playerB.addToScore(); break; }
		else if (playerB.areAllDead())  { reversedScore ? playerB.addToScore() : playerA.addToScore(); break; }
	}
}

/********************************************************************************************************************************
Function Name:			manageGame
Return value:			None
Description:			Prints the primary menu.
Dinamically allocated:	None
********************************************************************************************************************************/
void gameManager::manageGame(void)
{
	hideCursor();
	_primarymenu.printMenuAndTakeUserChoice(this);
}

/********************************************************************************************************************************
Function Name:			setPlayersName
Return value:			None
Description:			Wrapper function for player::setName
Dinamically allocated:	None
********************************************************************************************************************************/
void gameManager::setPlayersName(void)
{
	std::cout << "First Player: ";
	playerA.setName();
	std::cout << "Second Player: ";
	playerB.setName();
}

/********************************************************************************************************************************
Function Name:			resetScore
Return value:			None
Description:			Wrapper function for player::resetScore
Dinamically allocated:	None
********************************************************************************************************************************/
void gameManager::resetScore(void)
{
	playerA.resetScore();
	playerB.resetScore();
}

/********************************************************************************************************************************
Function Name:			restartBoard
Return value:			None
Description:			The function is called when a user wishes to restart the game.
Dinamically allocated:	None
********************************************************************************************************************************/
void gameManager::restartBoard(void)
{
	int i = 0;
	checker**& myGameBoard = gameBoard.getBoard();
	gameBoard.resetBoard();
	checker *positionsA = playerA.getStartingPosition();
	checker *positionsB = playerB.getStartingPosition();

	for (; i < CHECKER_NUMBER; i++)
	{
		myGameBoard[positionsA[i].row][positionsA[i].col] = positionsA[i];
		myGameBoard[positionsB[i].row][positionsB[i].col] = positionsB[i];
	}

	playerA.setCheckers(&(myGameBoard[positionsA[0].row][positionsA[0].col]), &(myGameBoard[positionsA[1].row][positionsA[1].col]), &(myGameBoard[positionsA[2].row][positionsA[2].col]));
	playerB.setCheckers(&(myGameBoard[positionsB[0].row][positionsB[0].col]), &(myGameBoard[positionsB[1].row][positionsB[1].col]), &(myGameBoard[positionsB[2].row][positionsB[2].col]));
}

/********************************************************************************************************************************
Function Name:			restartGame
Return value:			None
Description:			The function handles all the operation of restarting the game.
Dinamically allocated:	None
********************************************************************************************************************************/
void gameManager::restartGame(void)
{
	gameRestarted = true;

	checker **&myGameBoard = gameBoard.getBoard();
	checker** currCheckerA = playerA.findCurrentChecker();
	checker** currCheckerB = playerB.findCurrentChecker();
	if (nullptr != currCheckerA) { myGameBoard[(*currCheckerA)->row][(*currCheckerA)->col].setCheckerType((*currCheckerA)->walkedOn); }
	if (nullptr != currCheckerB) { myGameBoard[(*currCheckerB)->row][(*currCheckerB)->col].setCheckerType((*currCheckerB)->walkedOn); }

	playerA.resetPlayer();
	playerB.resetPlayer();
	restartBoard();
	clearScreen();
	gameBoard.printBoard();
	printPlayersScore();
}

/********************************************************************************************************************************
Function Name:			ransomiseCheckers
Return value:			None
Description:			The function randomises the checkers for each player.
Dinamically allocated:	None
********************************************************************************************************************************/
void gameManager::ransomiseCheckers(void)
{
	playerA.setCheckers(gameBoard.randomisePlayerChecker(CHECK1), gameBoard.randomisePlayerChecker(CHECK2), gameBoard.randomisePlayerChecker(CHECK3));
	playerB.setCheckers(gameBoard.randomisePlayerChecker(CHECK7), gameBoard.randomisePlayerChecker(CHECK8), gameBoard.randomisePlayerChecker(CHECK9));
}

/********************************************************************************************************************************
Function Name:			setPlayersAbilityToMove
Return value:			None
Description:			Sets the player's checkers the ability to move on top of forest and sea.
Dinamically allocated:	None
********************************************************************************************************************************/
void gameManager::setPlayersAbilityToMove(void)
{
	playerA.getChecker(2)->setMoveForest(true);
	playerA.getChecker(2)->setMoveSea(true);
	playerA.getChecker(3)->setMoveSea(true);
	playerB.getChecker(1)->setMoveForest(true);
	playerB.getChecker(1)->setMoveSea(true);
	playerB.getChecker(2)->setMoveForest(true);
}

/********************************************************************************************************************************
Function Name:			prepareForGame
Return value:			None
Description:			Wrapper function to prepare the board, players and printing the board.
Dinamically allocated:	None
********************************************************************************************************************************/
void gameManager::prepareForGame(void)
{	
	if (!firstGame) 
	{ 
		gameBoard.resetBoard(); 
		playerA.resetPlayer();
		playerB.resetPlayer();
	}
	ransomiseCheckers();
	playerA.setPointersToCheckers();
	playerB.setPointersToCheckers();
	playerA.setCheckersLogic();
	playerB.setCheckersLogic();
	setPlayersAbilityToMove();
	playerA.saveStartingPosition();
	playerB.saveStartingPosition();
	setTextColor(BLACK, BLACK);
	clearScreen();
	gameBoard.printBoard();
	printPlayersScore();
	firstGame = false;
}
