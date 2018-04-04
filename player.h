#pragma once

#include <string>
//#include <Windows.h>

#include "defs.h"
#include "Checkers.h"

class checker;

class player
{
	std::string name;
	int			score = 0;
	char		gameKeys[KEYS_NUMBER];
	checker*	firstChecker;
	checker*	secondChecker;
	checker*	thirdChecker;
	types		winningFlag;
	types		currentChecker = BLANK;
	int			numberOfCheckersLive = CHECKER_NUMBER;
	checker		startingPosition[3];

public:
	player(std::string& playerName, types flag) : 
		name(playerName),
		winningFlag(flag)
	{

	}
	
	void setKeys(char *keysToSet);
	bool pressesKey(checker**& gameBoard, char key);
	bool player::moveWithoutPressedKey(checker**& board);
	void setName(void);
	void printName(void) { std::cout << name << std::endl; };
	bool areAllDead(void);
	void addToScore(void);
	checker *getChecker(int cheknum);
	void updatePlayer();
	void setPointersToCheckers(void);
	void setCheckersLogic(void);
	void resetScore(void) { score = 0; }
	void saveStartingPosition(void) 
	{ 
		startingPosition[0] = *firstChecker; 
		startingPosition[1] = *secondChecker; 
		startingPosition[2] = *thirdChecker; 
	};
	checker* getStartingPosition() { return startingPosition; }
	void resetPlayer(void);
	void setCheckers(checker* _firstChecker, checker* _secondChecker, checker* _thirdChecker) 
	{ 
		firstChecker = _firstChecker; 
		secondChecker = _secondChecker; 
		thirdChecker = _thirdChecker; 
		
	}
	int getScore(void) { return score; }
	std::string getName(void) { return name; }
	checker** findCurrentChecker(void);

private:
	bool isCheckerKey(char key);
	void updateCheckerAddress(checker**& board, checker ** currentChecker);
};