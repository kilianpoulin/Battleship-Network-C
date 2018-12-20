typedef struct Action Action;
struct Action
{
    int x;
    int y;
    char ship;
    int space;
    int pos; /// position
};


void initplate(char tab[10][10]);
void initships(char board[10][10], int t);
int check_space(char board[10][10], Action a);
void write_space(char board[10][10], Action a);
int convert_horizontal_coor(char y);
int convert_vertical_coor(char y);


