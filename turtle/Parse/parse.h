#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define MAXNUMTOKENS 100
#define MAXTOKENSIZE 20
#define strsame(A,B) (strcmp (A, B)==0)

struct prog{
    char wds[MAXNUMTOKENS][MAXTOKENSIZE];
    int currentword;//Current Word
};
typedef struct prog Program;

void PROG (Program *p);
void INSLST(Program *p);
void INS(Program *p);


void FWD(Program *p);
void RGT(Program *p);
void COL(Program *p);
void LOOP(Program *p);
void SET(Program *p);


void VARNUM(Program *p);
void VAR(Program *p);
void NUM(Program *p);
void LTR(Program *p);

void WORD(Program *p);

void LST(Program *p);
void ITEMS(Program *p);
void ITEM(Program *p);

void PFIX(Program *p);
void OP(Program *p);
int isop(char *c);

void test(void);


/*
35%:语法对的就说Parse OK，是否执行是interpret的功能
No nested loops
Just Yes or No

25%:Interpreter:Draw screens

chapter 5: colourful version

5%:drawing ->postscript->txt files
system(ls):a shell for itself and execute?
postscipt to pdf 

15%：extension：

20%：how to test?recursive large.
how to test\debug txt\do not do it last

try to make it work now....
~1.2 machine
whiteboard tesing techniques of testing???
convinced Neill about the test 

can change Makefile
*/