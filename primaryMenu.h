#pragma once

#include <iostream>
#include <string>

#include "defs.h"
#include "Utils.h"

class gameManager;

class primaryMenu
{
	userChoice choice = EXIT;

public:
	primaryMenu()
	{

	}


	void printMenuAndTakeUserChoice(gameManager* manager);

private:
	void handleUserChoice(gameManager* manager);
	void printMenu(gameManager *manager);
};