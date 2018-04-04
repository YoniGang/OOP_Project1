
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "player.h"
#include "Utils.h"

/********************************************************************************************************************************
Function Name:			setName
Return value:			None
Description:			The function changes the player's name.
Dinamically allocated:	None
********************************************************************************************************************************/
void player::setName()
{
	std::cout << "Please enter players' name: " << std::endl;
	std::cin >> name;
}

/********************************************************************************************************************************
Function Name:			areAllDead
Return value:			bool
Description:			The function checks if all the checkers has been eaten. Returns true no more checkers to play with.
Dinamically allocated:	None
********************************************************************************************************************************/
bool player::areAllDead(void)
{
	if (numberOfCheckersLive == 0)
		return true;

	return false;
}

void player::addToScore(void)
{
	gotoxyAux(6, 6);
	setTextColor(DARK_BLUE, WHITE);
	std::cout << name << " had won the game!";
	Sleep(2000);
	setTextColor(WHITE, BLACK);
	score++;
}

/********************************************************************************************************************************
Function Name:			getChecker
Return value:			checker*
Description:			The function gets a checker type and returns the pointer to hte object.
Dinamically allocated:	None
********************************************************************************************************************************/
checker * player::getChecker(int cheknum)
{
	if		(1 == cheknum) { return firstChecker; }
	else if (2 == cheknum) { return secondChecker; }
	else if (3 == cheknum) { return thirdChecker; }
	return nullptr;
}

/********************************************************************************************************************************
Function Name:			updatePlayer
Return value:			None
Description:			The function checks if one of the checkers has been eaten and updates the player's members.
Dinamically allocated:	None
********************************************************************************************************************************/
void player::updatePlayer()
{
	if ((nullptr != firstChecker) && (BLANK == firstChecker->getType())) { numberOfCheckersLive--; firstChecker = nullptr; }
	else if ((nullptr != secondChecker) && (BLANK == secondChecker->getType())) { numberOfCheckersLive--; secondChecker = nullptr; }
	else if ((nullptr != thirdChecker) && (BLANK == thirdChecker->getType())) { numberOfCheckersLive--; thirdChecker = nullptr; }
}

/********************************************************************************************************************************
Function Name:			setPointersToCheckers
Return value:			None
Description:			The function sets the owner of the checker as the player.
Dinamically allocated:	None
********************************************************************************************************************************/
void player::setPointersToCheckers(void)
{
	firstChecker->setPlayer(this);
	secondChecker->setPlayer(this);
	thirdChecker->setPlayer(this);
}

/********************************************************************************************************************************
Function Name:			setCheckersLogic
Return value:			None
Description:			Wrapper function. For each checker, the function calls the checker::setCheckerLogic functionc.
Dinamically allocated:	None
********************************************************************************************************************************/
void player::setCheckersLogic(void)
{
	firstChecker->setCheckerLogic();
	secondChecker->setCheckerLogic();
	thirdChecker->setCheckerLogic();
}

/********************************************************************************************************************************
Function Name:			resetPlayer
Return value:			None
Description:			Sets the current checker to nothing (no current checker to move) and the number of live checker to default.
Dinamically allocated:	None
********************************************************************************************************************************/
void player::resetPlayer(void)
{
	currentChecker = BLANK;
	numberOfCheckersLive = CHECKER_NUMBER;
}

/********************************************************************************************************************************
Function Name:			findCurrentChecker
Return value:			checker**
Description:			The function takes the currentChecker member and returns the pointer to the checker.
Dinamically allocated:	None
********************************************************************************************************************************/
checker** player::findCurrentChecker()
{

	if ((nullptr != firstChecker) && (currentChecker == firstChecker->getType()))
		return &firstChecker;
	else if ((nullptr != secondChecker) && (currentChecker == secondChecker->getType()))
		return &secondChecker;
	else if ((nullptr != thirdChecker) && (currentChecker == thirdChecker->getType()))
		return &thirdChecker;
	else
		return nullptr;
}

/********************************************************************************************************************************
Function Name:			setKeys
Return value:			None
Description:			The function sets the moving keys.
Dinamically allocated:	None
********************************************************************************************************************************/
void player::setKeys(char * keysToSet)
{
	char keyToSet = 0;
	int index = 0;

	for (; index < KEYS_NUMBER; index++)	{ gameKeys[index] = keysToSet[index]; }
}

/********************************************************************************************************************************
Function Name:			isCheckerKey
Return value:			bool
Description:			Checkes if the pressed key was a checker key (1,2,3,7,8,9). Returns true if it does.
Dinamically allocated:	None
********************************************************************************************************************************/
bool player::isCheckerKey(char key)
{
	types check = (types)(key - '0');
	int i = 0;

	for (; i < CHECKER_NUMBER; i++)	{ if (check == (gameKeys[KEYS_NUMBER - CHECKER_NUMBER + i] - '0')) { return true; } }

	return false;
}

/********************************************************************************************************************************
Function Name:			updateCheckerAddress
Return value:			None
Description:			Updates a checker to the position on the board.
Dinamically allocated:	None
********************************************************************************************************************************/
void player::updateCheckerAddress(checker**& board, checker **currentChecker)
{
	int row = 0;
	int col = 0;

	row = (*currentChecker)->row;
	col = (*currentChecker)->col;
	
	*currentChecker = &board[row][col];
}

/********************************************************************************************************************************
Function Name:			typeOfChecker
Return value:			types
Description:			Returns the type of the desired square.
Dinamically allocated:	None
********************************************************************************************************************************/
static types typeOfChecker(checker *check)
{
	if (nullptr == check) { return BLANK; }
	else				  { return check->getType(); }
}

/********************************************************************************************************************************
Function Name:			pressesKey
Return value:			bool
Description:			The function handles the user press on the keyboard. if the user pressed checker key - it updates the current checker.
						If the user pressed a moving key - it moves the current checker. Returns true f the player won.
Dinamically allocated:	None
********************************************************************************************************************************/
bool player::pressesKey(checker**& board, char key)
{
	bool returnRes = false;
	checker** checkerToMove = nullptr;

	if (isCheckerKey(key))
	{
		if (currentChecker != BLANK) 
		{ 
			checkerToMove = findCurrentChecker();
			if (nullptr != checkerToMove) { (*checkerToMove)->stopChecker(BLACK); }
		}
		currentChecker = (types)(key - '0');
		return false;
	}

	else if (currentChecker == BLANK) { return false; }

	else
	{	
		checkerToMove = findCurrentChecker();

		if (checkerToMove != nullptr)
		{
			if (key == gameKeys[UP]) { (*checkerToMove)->setDirection(Diraction::UP); }
			else if (key == gameKeys[DOWN]) { (*checkerToMove)->setDirection(Diraction::DOWN); }
			else if (key == gameKeys[LEFT]) { (*checkerToMove)->setDirection(Diraction::LEFT); }
			else if (key == gameKeys[RIGHT]) { (*checkerToMove)->setDirection(Diraction::RIGHT); }

			returnRes = (*checkerToMove)->move(board, winningFlag, typeOfChecker(firstChecker), typeOfChecker(secondChecker), typeOfChecker(thirdChecker));
			if (nullptr != *checkerToMove) { updateCheckerAddress(board, checkerToMove); }
			return returnRes;
		}
		return false;
	}
}

/********************************************************************************************************************************
Function Name:			moveWithoutPressedKey
Return value:			bool
Description:			Moves the current checker with the direction it moved in the last time. Returns true if the player won.
Dinamically allocated:	None
********************************************************************************************************************************/
bool player::moveWithoutPressedKey(checker**& board)
{
	bool returnRes = false;
	checker** checkerToMove = nullptr;

	if (currentChecker == BLANK)
		return false;

	else
	{
		if (nullptr != (checkerToMove = findCurrentChecker()))
		{
			returnRes = (*checkerToMove)->move(board, winningFlag, typeOfChecker(firstChecker), typeOfChecker(secondChecker), typeOfChecker(thirdChecker));
			if (nullptr != *checkerToMove) { updateCheckerAddress(board, checkerToMove); }
			return returnRes;
		}

		return false;
	}
}