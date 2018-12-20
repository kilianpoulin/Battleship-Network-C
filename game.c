#include <stdio.h>
#include "initplate.h"
#include "game.h"
#include <stdlib.h>
#define clear() printf("\033[H\033[J")

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

int main(){
    srand(time(NULL));
    char MyBoard[10][10];
    char MarkBoard[10][10];
    int choice;

   initplate(MyBoard);
   initplate(MarkBoard);
   printGame(MyBoard, MarkBoard);

   printf("Init board\n");
   printf("[0] Manually | [1] Randomly ==> ");
    scanf("%d", &choice);
    if(choice == 0)
        initships(MyBoard, 0);
    else
        initships(MyBoard, 1);

   printGame(MyBoard, MarkBoard);


   return 0;
}
