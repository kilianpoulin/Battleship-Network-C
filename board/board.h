#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include "../ai/ai.h"
#include <stdio.h>
#include "../ship/ship.h"
void initplate(char tab[10][10]);
void printBoard(char b1[10][10]);
void printGame(char b1[10][10], char b2[10][10]);
int check_space(char board[10][10], Action a);
void write_space(char board[10][10], Action a);
void init_game(char MyBoard[10][10], char MarkBoard[10][10]);

#endif // BOARD_H_INCLUDED
