#pragma once
#include <iostream>

#include "defs.h"
#include "primaryMenu.h"
#include "board.h"
#include "player.h"
#include "Checkers.h"
#include "Utils.h"

class primaryMenu;
class secondaryMenu;

class gameManager
{
	board gameBoard;
	player playerA = { (std::string)"A", FlgB };
	player playerB = { (std::string)"B", FlgA };
	primaryMenu _primarymenu;
	bool flipScore = false;
	bool gameRestarted = false;
	bool firstGame = true;

public: 
	gameManager()
	{
		playerA.setKeys("waxd123");
		playerB.setKeys("ijml789");
	}

	void manageGame(void);
	void run(bool reversedScore);
	void setPlayersName(void);
	void resetScore(void);
	void restartGame(void);
	void ransomiseCheckers(void);
	void printPlayersScore(void)
	{
		std::cout << playerA.getName() << " score: " << playerA.getScore() << "   " << playerB.getName() << " score: " << playerB.getScore() <<std::endl;
	}

private:
	void setPlayersAbilityToMove(void);
	void prepareForGame(void);
	void connectSecondaryMenu(secondaryMenu& sm);
	void restartBoard(void);

	friend class secondaryMenu;
};