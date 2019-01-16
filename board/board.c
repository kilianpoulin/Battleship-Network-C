#include "board.h"

void printBoard(char b1[10][10]){
   int i,j;
   printf("\n Main Board \t\t\tMark Board\n");
   for(i = 0; i < 10; i++){
        if(i!=9)printf(" %d  ", i+1);
	else printf(" %d ", i+1);
	for(j = 0; j < 10; j++)printf("%c ", b1[i][j]);
	printf("\n");
   }
   printf("    A B C D E F G H I J\n\n");
}

void printGame(char b1[10][10], char b2[10][10]){
   int i,j;
//   clear();
   printf("\n Main Board \t\t\tMark Board\n");
   for(i = 0; i < 10; i++){
        if(i!=9)printf(" %d  ", i+1);
	else printf(" %d ", i+1);
	for(j = 0; j < 10; j++)printf("%c ", b1[i][j]);
	printf("	");
	for(j = 0; j < 10; j++)printf("%c ", b2[i][j]);
        printf("\n");
   }
   printf("    A B C D E F G H I J         A B C D E F G H I J\n\n");

}

/// METHOD : check_space
/// Places a ship on the board
void write_space(char board[10][10], Action a){
    int i;
    /// VERTICAL
    if(a.pos == 1){
        for(i = a.y; i < a.space + a.y; i++){
            board[i][a.x] = a.ship;
        }
    }
    else if(a.pos == 0){
        for(i = a.x; i < a.space + a.x; i++){
            board[a.y][i] = a.ship;
        }
    }
}

/// METHOD : check_space
/// Checks if space is available to place a boat
int check_space(char board[10][10], Action a){
    int i;
    if(a.pos != 0 && a.pos != 1)
        return -1;
    /// VERTICAL ----------------------------
        /// checks if it doesn't go out of the board (i == 10) and space is free (== '-')
    if(a.pos == 1){
        for(i = a.y; i < a.space + a.y; i++){
            if(i == 10 || board[i][a.x] != '-')
                return -1;
        }
    } /// HORIZONTAL ------------------------
        /// checks if it doesn't go out of the board (i == 10) and space is free (== '-')
    else if(a.pos == 0){
        for(i = a.x; i < a.space + a.x; i++){

            if(i == 10 || board[a.y][i] != '-')
                return -1;
        }
    }
    else
        return -1;

    write_space(board, a);

    return 1;
}

void initplate(char tab[10][10]){
    int i,j;
    for(i = 0; i < 10; i++)
	for(j = 0; j < 10; j++)tab[i][j] = '-';
}

void init_game(char MyBoard[10][10], char MarkBoard[10][10])
{
	initplate(MyBoard);
    initplate(MarkBoard);
    printGame(MyBoard, MarkBoard);
    int choice = 0;
    printf("Init board\n");
    printf("[0] Manually | [1] Randomly ==> ");
    scanf("%d", &choice);
    if(choice == 0)
        initships(MyBoard, 0);
    else
        initships(MyBoard, 1);

    printGame(MyBoard, MarkBoard);
}
