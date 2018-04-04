#pragma once
#include <iostream>
#include "defs.h"
#include "Utils.h"

class player;

class checker
{
	types checkerType = BLANK;
	int col = INITIAL_POINT;
	int row = INITIAL_POINT;
	int moveDirRow=0;
	int moveDirCol=0;
	bool canMoveSea = false;
	bool canMoveForest = false;
	bool winningRows[SIZE] = { false };
	bool winningCols[SIZE] = { false };
	types alwaysLose = BLANK;
	types walkedOn = BLANK;
	player *checkerOwner = nullptr;
	
public:
	checker()
	{

	}

	bool moveAux(checker **& gameBoard, types winningFlag, types firstChecker, types secondChecker, types thirdChecker);
	bool move(checker**& gameBoard, types winningFlag, types firstChecker, types secondChecker, types thirdChecker);
	void setCheckerType(types typeToSet) { checkerType = typeToSet; };
	void setPosition(int colToSet, int rowToSet) { col = colToSet; row = rowToSet; };
	types getType(void) { return checkerType; };
	void setDirection(Diraction dir);
	void setMoveSea(bool canMove) { canMoveSea = canMove; }
	void setMoveForest(bool canMove) { canMoveForest = canMove; }
	void stopChecker(int backroundColor);
	void eraseDraw();
	void draw(types sign, int backroundColor);
	void setPlayer(player *playerToSet) { checkerOwner = playerToSet; };
	player* getPlayer(void) { return checkerOwner; };
	void resetChecker(int boardSize);

private:
	bool checkForestOrSea(types nextMove);
	bool collisionWithMyOwn(types nextMove, types firstChecker, types secondChecker, types thirdChecker);
	void setCheckerLogic();
	void setColsAndRowsCheck1();
	void setColsAndRowsCheck2();
	void setColsAndRowsCheck3();
	void battleOpponent(checker *playerAChecker, checker *playerBChecker);
	void erase(checker **& gameBoard);
	void putCheckerInNewLocation(checker **& gameBoard, types typeToPut);
	void copyBeforeNextMove(checker *copyTo, checker** const me) { *copyTo = *this; *me = copyTo; }
	void resetLogic(int boardSize);

	friend class player;
	friend class gameManager;
};