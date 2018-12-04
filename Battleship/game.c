#include <stdio.h>
#include "initplate.h"

void printGame(char b1[10][10], char b2[10][10]){
   int i,j;
   system("cls");
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

int main(){


   /*char MyBoard[10][10];
   char MarkBoard[10][10];

   initplate(MyBoard);
   initplate(MarkBoard);
   printGame(MyBoard, MarkBoard);*/
   tryconnect();

   return 0;
}
