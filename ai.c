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

/// METHOD : receive missile
/// updateS board of opponent
// returns 1 if hit
// returns 0 if missed
int receive_missile(Action a, char board[10][10]){

    /// if there is a ship not hit yet (upper case letter), it is now hit --> lower case letter
    if(board[a.x][a.y] != '-' && board[a.x][a.y] > 64 && board[a.x][a.y] < 91){
        board[a.x][a.y] = board[a.x][a.y] + 32;
	return 1;
	
        //mark[a.x][a.y] = 'X'; /// hit
        //printf(" RESULT : Congratulations, it's a hit !\n\n");
    }
    else {
	return 0;
        //mark[a.x][a.y] = 'x'; /// missed
        //printf(" RESULT : Sorry, you missed !\n\n");
    }
}

/// METHOD : fire missile 
/// updates mark board of player
// returns 1 if hit
// returns 0 if missed
void fire_missile(int result, Action a, char mark[10][10]){

    /// if there is a ship not hit yet (upper case letter), it is now hit --> lower case letter
    if(result == 1){
        mark[a.x][a.y] = 'x'; /// hit
        printf(" RESULT : Congratulations, it's a hit !\n\n");
    }
    else if(result == 0) {
        mark[a.x][a.y] = 'X'; /// missed
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

Action convert_to_action(char buffer[3]){
	Action action;
	/// Setting Y
    action.y = convert_vertical_coor(buffer[0]); /// converts letter coordinate into number

    /// Setting X
    if(buffer[2] != '\0')
        action.x = 9;
    else
        action.x = convert_horizontal_coor(buffer[1]);

	return action;

}

Action player_turn(char mark[10][10], char buffer[80]){
	Action action;
        /// HUMAN PLAYER
        printf("\n \t ----- Player : It's your turn to play ! ----- \n\n");
        do{
            printf("Case where to drop a missile (ex : A1) : ");
            scanf("%s", buffer);

            /// Setting Y
            action.y = convert_vertical_coor(buffer[0]); /// converts letter coordinate into number

            /// Setting X
            if(buffer[2] != '\0')
                action.x = 9;
            else
                action.x = convert_horizontal_coor(buffer[1]); /// converts char 'number' coordinate into number
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

/// METHOD : play game
/// loop continues as long as game_on returns 0
void play_game(){

	Action action;
    	printf("\n\n");
    	int winner = 0;
	char MyBoard[10][10], CpBoard[10][10];
        char MarkBoard[10][10], Cpmark[10][10];
        int choice = 0;
	int result = 0;
	char entry[42];

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
        initplate(Cpmark);
        initships(CpBoard, 1); /// generated randomly
    
    do{
        /// Player's turn
        action = player_turn(MarkBoard, entry);

	result = receive_missile(action, CpBoard);
	
        fire_missile(result, action, MarkBoard);

        printGame(MyBoard, MarkBoard);
        printf("\n\n");

        /// Computer's turn

        action = computer_turn(CpBoard, Cpmark);

	result = receive_missile(action, MyBoard);
        fire_missile(result, action, Cpmark);
	

        /// Check if there is a winner
        if(game_on(MyBoard) == 0)
            printf("\n \t Computer wins !!!! \n");
        else if(game_on(CpBoard) == 0)
            printf("\n \tPlayer 1  wins !!! \n");
        else
            winner = 1;

    } while(winner == 1);

}
