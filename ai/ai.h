#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

typedef struct Action Action;
struct Action
{
    int x;
    int y;
    char ship;
    int space;
    int pos; /// position
};

int convert_vertical_coor(char y);
int convert_horizontal_coor(char y);
void fire_missile(int result, Action a, char mark[10][10]);
int game_on(char p[10][10]);
int check_hit_exists(Action action, char mark[10][10], int computer);
void play_game();
void init_game();
Action player_turn(char mark[10][10], char buffer[80]);
Action computer_turn(char Cpboard[10][10], char Cpmark[10][10]);
int receive_missile(Action a, char board[10][10]);
Action convert_to_action(char buffer[3]);
int count_remaining(char mark[10][10], int option);

#endif // AI_H_INCLUDED
