#include <stdio.h>
#include <stdlib.h>
#include "../networking/server.h"
#include "../networking/client.h"
#include "../ai/ai.h"
#include "../ship/ship.h"
#include "../board/board.h"
#include <unistd.h>
#include <time.h>

#define PORT 8080

int main()
{
    srand(time(NULL));
    int choice;
    printf("\n\n \t Battleship game \n\n");

    printf("\t 1. Host a game\n");
    printf("\t 2. Join a game\n");
    printf("\t 3. Challenge the computer\n");

    do {
        printf("\t\n Your choice : ");
        scanf("%d", &choice);
    } while(choice != 1 && choice != 2 && choice != 3);

    if(choice == 1){
        server();
    }
    else if(choice == 2)
        client();
    else if(choice == 3){
        play_game();
     }
    return 0;
}
