#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "Utils.h"
#include "defs.h"

using namespace std;

void setTextColor(int foreground_color, int background_color) {
	int color = foreground_color | background_color * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void setTextColor(int foreground_color) {
	setTextColor(foreground_color, 0);
}

void clearScreen() {
	system("cls");
}

// function definition -- requires windows.h
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
// function that put the cursor in the right position
void gotoxyAux(int col, int row)
{
	gotoxy(((col*CELL_COL_SIZE) + INITIAL_POINT), ((row*CELL_SIZE_ROW) + INITIAL_POINT));
}

void hideCursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}