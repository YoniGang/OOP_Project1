#include "secondaryMenu.h"
#include "gameManager.h"
#include "primaryMenu.h"


/********************************************************************************************************************************
Function Name:			printMenu
Return value:			None
Description:			The function prints the secondary menu.
Dinamically allocated:	None
********************************************************************************************************************************/
void secondaryMenu::printMenu(void)
{
	std::cout << "[1] Return to the game" << std::endl;
	std::cout << "[2] Start the same game again" << std::endl;
	std::cout << "[8] Go to main menu" << std::endl;
	std::cout << "[9] Exit Game" << std::endl;
}

/********************************************************************************************************************************
Function Name:			printMenuAndTakeUserChoice
Return value:			bool
Description:			The function prints the menu and takes the user choice. Returns true if breaking the current game is needed.
Dinamically allocated:	None
********************************************************************************************************************************/
bool secondaryMenu::printMenuAndTakeUserChoice(void)
{
	unsigned char userChose = 0;

	printMenu();

	_gameManager->printPlayersScore();

	std::cin >> userChose;
	choice = (userChoiceSecondMenu)(userChose - '0');

	return (handleUserChoice());
}

/********************************************************************************************************************************
Function Name:			handleUserChoice
Return value:			bool
Description:			With user's choice, the function decides what is needed to be done.
Dinamically allocated:	None
********************************************************************************************************************************/
bool secondaryMenu::handleUserChoice(void)
{
	unsigned char userChose = 0;
	bool choiceCheck = true;

	while (choiceCheck)
	{
		switch (choice)
		{
		case (RETURN_TO_GAME):
			clearScreen();
			_gameManager->gameBoard.printBoard();
			return false;
			//breaking

		case (EXIT_GAME):
			std::cout << "bye bye..." << std::endl;
			exit(0);
			//breaking

		case (START_AGAIN):
			_gameManager->restartGame();
			return false;

		case (MAIN_MENU):
			return true;

		default:
			clearScreen();
			printMenu();
			_gameManager->printPlayersScore();
			std::cout << "\nBad Choice! Please try again: ";
			break;
		}
		std::cin >> userChose;
		choice = (userChoiceSecondMenu)(userChose - '0');
	}
	return false;
}