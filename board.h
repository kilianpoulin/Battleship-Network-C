#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "ai.h"
void initplate(char tab[10][10]);
void printBoard(char b1[10][10]);
void printGame(char b1[10][10], char b2[10][10]);
int check_space(char board[10][10], Action a);
void write_space(char board[10][10], Action a);


#endif // BOARD_H_INCLUDED
