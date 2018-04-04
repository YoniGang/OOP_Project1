#pragma once
#include "Checkers.h"
#include "defs.h"

void drawWithColor(types type, int backroundColor);

class board
{
	int _boardSize;
	checker **gameBoard = new checker*[_boardSize + INITIAL_POINT];
public:
	board(int boardSize = SIZE) : _boardSize(boardSize)
	{
		for (int i = 0; i < _boardSize +INITIAL_POINT ; i++)
			gameBoard[i] = new checker[_boardSize +INITIAL_POINT];

		createBoard();
	}

	~board()
	{
		for (int i = 0; i < _boardSize + INITIAL_POINT; i++)
			delete[] gameBoard[i];

		delete[] gameBoard;
	}

	checker**& getBoard(void) { return gameBoard; }
	checker* randomisePlayerChecker(types playerChecker);
	void printBoard(void);
	void resetBoard(void);

private:
	void createBoard(void);
	void emptyBoard(checker**& gameBoard);
};