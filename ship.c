#include "ship.h"

/// METHOD : initships
/// initalizes the board manually if t == 0 or randomly if t == 1
void initships(char board[10][10], int t){
    int i, j;
    char tmp;
    char *string;
    Action action[10];
    action[0].ship = 'C';
    action[1].ship = 'B';
    action[2].ship = 'B';
    action[3].ship = 'S';
    action[4].ship = 'S';
    action[5].ship = 'S';
    action[6].ship = 'D';
    action[7].ship = 'D';
    action[8].ship = 'D';
    action[9].ship = 'D';

    for(i = 0; i < 10; i++){
        j = 0;
        char choice[3];
        do{

            switch(action[i].ship){
                case 'C' :
                    string = "Place carrier (5 spaces) : \n";
                    action[i].space = 5;
                    break;
                case 'B':
                    string = "Place battleship (4 spaces) : \n";
                    action[i].space = 4;
                    break;
                case 'S':
                    string = "Place submarine (3 spaces) : \n";
                    action[i].space = 3;
                    break;
                case 'D':
                    string = "Place destroyer (2 spaces) : \n";
                    action[i].space = 2;
                    break;
            }
            if(t == 0){
                /// displaying error --> the user has to enter a new position and gets an error message
                if(j != 0)
                    printf("Error - Space already used or outside the board");

                printf(string);
                printf("Coordinate of starting point (ex : A1) : ");
                scanf("%s", &choice);

                /// Setting X
                action[i].x = convert_vertical_coor(choice[0]); /// converts letter coordinate into number

                /// Setting Y
                if(choice[2] != '\0')
                    action[i].y = 9;
                else
                    action[i].y = convert_horizontal_coor(choice[1]); /// converts char 'number' coordinate into number

                printf("\n\n");

                /// Choosing orientation of ship
                printf("[0] Horizontal | [1] Vertical ==> ");
                scanf("%d", &action[i].pos);

                printf("\n\n");

            }
            else { /// RANDOM
                action[i].x = rand() % 10;
                action[i].y = rand() % 10;
                action[i].pos = rand() % 2;

            }
            j++; /// var to count errors
        } while(check_space(board, action[i]) != 1); /// if no error, while is over

        printBoard(board);
    }

}
