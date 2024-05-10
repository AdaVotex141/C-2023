# include <stdio.h>
# include <assert.h>
# include <stdbool.h>
# include <stdlib.h>
# define MAXWH 10
# define Queen 'Q'
# define Taken 'X'
# define ListMAX 500000

typedef struct Board {
    char grid[MAXWH][MAXWH];
    int Q_num;
    int width;
    //int parent//The Parent Boards index
    int f;
    int Q_checked[MAXWH][MAXWH];
    /*
    if it is 0, it can be filled and turned the 
    [colmn][]...
    [row][]...
    [x+y][]...
    [x-y+input][]...
*/
}Board;

//Create a void board. 
Board makeboard(int input);
//Create the children of the parent board.
Board create_children(Board parent,int i,int j,int input);

void solve_Board(int input,int argv_flag);
//Check 
bool Check_duplicates(Board b1, Board b2,int input);
// Board Create_parents(Board Boardlist[ListMAX],int input);
// Board create_parent(int input,Board Boardlist[ListMAX]);

bool Check_Q(Board b,int i,int j,int input);

void test(void);
void print_board(Board b);
