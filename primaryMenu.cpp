#include <iostream>

#include "primaryMenu.h"
#include "gameManager.h"
#include "player.h"

class gameManager;
class player;

/********************************************************************************************************************************
Function Name:			printMenu
Return value:			None
Description:			The name indicates it all...
Dinamically allocated:	None
********************************************************************************************************************************/
void primaryMenu::printMenu(gameManager *manager)
{
	clearScreen();
	std::cout << "[1] Choose names" << std::endl;
	std::cout << "[2] Start the game" << std::endl;
	std::cout << "[3] Start the game in reversed mode" << std::endl;
	std::cout << "[4] Reset score" << std::endl;
	std::cout << "[9] Exit Game" << std::endl;
	manager->printPlayersScore();
}

/********************************************************************************************************************************
Function Name:			printMenuAndTakeUserChoice
Return value:			None
Description:			The function takes and handles the user's choice.
Dinamically allocated:	None
********************************************************************************************************************************/
void primaryMenu::printMenuAndTakeUserChoice(gameManager *manager)
{
	unsigned char userChose = 0;
	printMenu(manager);

	std::cin >> userChose;
	choice = (userChoice)(userChose - '0');
	handleUserChoice(manager);
}

/********************************************************************************************************************************
Function Name:			printMenuAndTakeUserChoice
Return value:			None
Description:			The function handles the user's choice and sets the desired action.
Dinamically allocated:	None
********************************************************************************************************************************/
void primaryMenu::handleUserChoice(gameManager *manager)
{
	unsigned char userChose = 0;

	do
	{
		switch (choice)
		{
		case (CHOOSE_NAMES):
			manager->setPlayersName();
			printMenu(manager);
			break;

		case (START_GAME):
			manager->run(false);
			printMenu(manager);
			break;

		case (REVERSED_MODE):
			manager->run(true);
			printMenu(manager);
			break;

		case (RESET_SCORE):
			manager->resetScore();
			printMenu(manager);
			break;

		case (EXIT):
			std::cout << "Bye Bye..." << std::endl;
			exit(0);
			break;

		default:
			printMenu(manager);
			std::cout << "\nBad Choice! Please try again: ";
			break;
		}
		std::cin >> userChose;
		choice = (userChoice)(userChose - '0');
	} while (true);
}
