#include <stdio.h>
#include "ai.h"
#include <stdlib.h>

int convert_vertical_coor(char y){
    if(y > 96 && y < 107) /// lower case
        return y - 97;
    else if(y > 64 && y < 75) /// upper case
        return y - 65;
    else
        return -1; /// error
}

int convert_horizontal_coor(char y){

    if(y > 48 && y < 58) /// number
        return y - 49;
    else
        return -1; /// error
}

/// METHOD : fire missile
/// updates mark board of player
/// updates board of opponent player
void fire_missile(Action a, char board[10][10], char mark[10][10]){

    /// if there is a ship not hit yet (upper case letter), it is now hit --> lower case letter
    if(board[a.x][a.y] != '-' && board[a.x][a.y] > 64 && board[a.x][a.y] < 91){
        board[a.x][a.y] = board[a.x][a.y] + 32;
        mark[a.x][a.y] = 'X'; /// hit
        printf(" RESULT : Congratulations, it's a hit !\n\n");
    }
    else {
        mark[a.x][a.y] = 'x'; /// missed
        printf(" RESULT : Sorry, you missed !\n\n");
    }
}

/// METHOD : game on
/// checks if player's board has any upper case letters
/// if not, he is the loser
/// returns 0 if loser
int game_on(char p[10][10]){
    int i, j;
    for(i = 0; i < 10; i++){
        for(j = 0; j < 10; j++){
            if(p[i][j] > 64 && p[i][j] < 92)
                return 1;
        }
    }
    return 0;
}

/// METHOD : check_hit_exists
/// checks if the player already fired a missile on this place
/// by checking his mark board
/// returns 0 if doesn't exist
/// returns 1 if exists
int check_hit_exists(Action action, char mark[10][10]){
    if(mark[action.x][action.y] != '-'){
        printf(" WARNING : You have already fired a missile on this spot, please enter another one. \n\n");
        return 1;
    }
    return 0;
}

Action player_turn(char board[10][10], char mark[10][10]){
    Action action;
    char choice[3];
        /// HUMAN PLAYER
        printf("\n \t ----- Player 1 : It's your turn to play ! ----- \n\n");
        do{
            printf("Case where to drop a missile (ex : A1) : ");
            scanf("%s", &choice);

            /// Setting Y
            action.y = convert_vertical_coor(choice[0]); /// converts letter coordinate into number

            /// Setting X
            if(choice[2] != '\0')
                action.x = 9;
            else
                action.x = convert_horizontal_coor(choice[1]); /// converts char 'number' coordinate into number
        /// check if player already hit that place
        } while(check_hit_exists(action, mark) != 0);

        return action;
}

Action computer_turn(char Cpboard[10][10], char Cpmark[10][10]){
    Action action;
    printf("\t ----- Computer's turn to play ! ----- \n\n");
    do{
        action.x = rand()%10;
        action.y = rand()%10;
        /// check if player already hit that place
    } while(check_hit_exists(action, Cpmark) != 0);

    return action;
}
/*
/// METHOD : play game
/// loop continues as long as game_on returns 0
void play_game(char board[10][10], char Cpboard[10][10], char mark[10][10], char Cpmark[10][10]){
{
    Action action;
    printf("\n\n");
    int winner = 0;
    do{
        /// Player's turn
        action = player_turn(board, mark);

        fire_missile(action, Cpboard, mark);
        printGame(board, mark);
        printf("\n\n");

        /// Computer's turn

        action = computer_turn(Cpboard, Cpmark);

        fire_missile(action, board, Cpmark);

        /// Check if there is a winner
        if(game_on(board) == 0)
            printf("Computer wins !!!! ");
        else if(game_on(Cpboard) == 0)
            printf("Player 1  wins !!!");
        else
            winner = 1;

    } while(winner == 1);

}
*/
void init_game(){
    srand(time(NULL));
    char MyBoard[10][10], CpBoard[10][10];
    char MarkBoard[10][10], CpMarkBoard[10][10];
    int choice;

    /// HUMAN PLAYER
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

    /// COMPUTER
    initplate(CpBoard);
    initplate(CpMarkBoard);
    //printGame(CpBoard, CpMarkBoard);
    initships(CpBoard, 1); /// generated randomly

    //play_game(MyBoard, CpBoard, MarkBoard, CpMarkBoard);

}
