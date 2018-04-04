#pragma once

#include <iostream>
#include <string>

#include "defs.h"
#include "Utils.h"

class gameManager;
class primaryMenu;

class secondaryMenu
{
	userChoiceSecondMenu choice = EXIT_GAME;
	gameManager* _gameManager;

public:
	secondaryMenu()
	{
	}


	bool printMenuAndTakeUserChoice(void);
	void setGameManager(gameManager* gm) { _gameManager = gm; }
	bool handleUserChoice(void);
	
private:
	void printMenu(void);
};