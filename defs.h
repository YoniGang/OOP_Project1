#pragma once

#define SIZE			13
#define INITIAL_POINT	1
#define CHECKER_NUMBER  3
#define CELL_SIZE_ROW	2
#define CELL_COL_SIZE	5
enum userChoice { CHOOSE_NAMES = 1, START_GAME = 2, REVERSED_MODE = 3, RESET_SCORE = 4, PRINT_BOARD = 5, EXIT = 9 };
enum userChoiceSecondMenu { RETURN_TO_GAME = 1, START_AGAIN = 2, MAIN_MENU = 8, EXIT_GAME = 9 };
enum types { BLANK = 0, CHECK1 = 1, CHECK2 = 2, CHECK3 = 3, FlgA = 4, FR = 5, FlgB = 6, CHECK7 = 7, CHECK8 = 8, CHECK9 = 9, SEA = 10 };
enum class Diraction { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3 , STOP = 5};
enum keys { UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3, FIRSTCHECKER = 4, SECONDCHECKER = 5, THIRDHECKER = 6, KEYS_NUMBER = 7};