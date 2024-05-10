#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "../STACK/stack.h"

#define MAXNUMTOKENS 100
#define MAXTOKENSIZE 20
#define MAX_LOOP 10000
#define MAX_POSTX 500
#define MAX_POSTY 500
#define value_MAX 3
#define strsame(A,B) (strcmp (A, B)==0)
#define WIDTH 51
#define HEIGHT 33
#define COLOURNUM 8
#define sub 3
#define PS_X 30.000000
#define PS_Y 40.000000

#define left 0
#define middle 1
#define right 2


//======================STRUCT=====================
typedef enum STATE{
  SCREEN,
  TXTFILE,
  POSTFILE
}STATE;

typedef enum DataType {
    STRING,
    DOUBLE,
    CHAR,
    DOUBLE2,
    INT
}type;

// union DATA{
//     char COMMAND[MAXTOKENSIZE];
//     double POS;
//     char COLOUR;
//     double WCOLOUR;
//     int SCALE_NUM;
//     enum DataType type;
// };
// typedef union DATA DATA;

// typedef struct Node {
//     union DATA data;
//     struct Node *next;
// } Node;

struct Table{
    char name[MAXNUMTOKENS];
    char value[MAXNUMTOKENS];
};
typedef struct Table Table;

struct Exten{
    char LBL[MAXNUMTOKENS];
    int label_POS;
    int pass_flag;
};
typedef struct Exten Exten;



struct prog{
    char wds[MAXNUMTOKENS][MAXTOKENSIZE];
    int currentword;//Current Word
    FILE* ps_out;
};
typedef struct prog Program;


struct Canvas{
    double dir;
    double POSX;
    double POSY;
    char col;
    int table_index;
    int looparray_num;
    Table table[MAX_LOOP];
    char array[HEIGHT][WIDTH];
    double colour[value_MAX];
    //DATA post[MAX_POSTX][MAX_POSTY];
    //DATA colour[COLOURNUM][value_MAX];
    int postROW;
    //Extension:
    Exten exten[MAX_LOOP];
    int ex_ROW;
    };
typedef struct Canvas Canvas;

//======================MAIN-FUNCTION=====================
void PROG (Program *p, Canvas *c,int flag);
void INSLST(Program *p, Canvas *c,int flag);
void INS(Program *p, Canvas *c,int flag);

void FWD(Program *p,Canvas *c,int flag);
void FWD_SCREEN(Program *p,Canvas *c);
void FWD_TXT(Program *p, Canvas *c);
void FWD_POST(Program *p, Canvas *c);


void RGT(Program *p,Canvas *c);
void COL(Program *p,Canvas *c);
void LOOP(Program *p, Canvas *c,int flag);
void SET(Program *p,Canvas *c);
//double normalizeRadians(double radians);

char *VARNUM(Program *p, Canvas *c);
char *VAR(Program *p);
char *NUM(Program *p);
char *LTR(Program *p);
void WORD(Program *p,Canvas *c);
void LST(Program *p,Canvas *c);
void ITEMS(Program *p,Canvas *c);
void ITEM(Program *p,Canvas *c);
struct Stack;
void PFIX(Program *p,Canvas* c, char* cur, stack* s);
void OP(Program *p);
//void test(void);
int isNumeric(const char* str);
//======================SMALL-FUNCTION=====================
void initializeCanvas(Canvas* c,int flag);
int checkVAR(Canvas *c, char* currentword);
//void resetWORD(Canvas* c,char* cur_name);
void setVALUE(Program *p, Canvas *c, char* currentword);
void set_WORD(Canvas *c,char *currentword);
bool isduplicate(char* cur, Canvas* c);
int isop(char *c);
double Calcul(Canvas *c,char* former,char* latter,char* oper);
int isNumeric(const char* str);
void SETRGBCOLOUR(Program *p, Canvas *c);
//neillcol setCOLOUR_NEILL(Canvas *c);
//======================EXTENSON=====================
void GOTO(Program *p, Canvas *c,int flag);
void LABEL(Program *p, Canvas *c, int flag);
int findLabelIndex(char *label,Canvas* c);
bool EXisduplicate(char* cur, Canvas* c);
char* LBL(Program *p);
int isco(char *c);
bool Comparison(Canvas *c,char* former,char* latter,char* oper);
void test(void);
