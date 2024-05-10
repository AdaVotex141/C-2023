#include "interp.h"
#include <assert.h>
#define TOLERANCE 1e-10
void test(void){

int flag=TXTFILE;
// void initializeCanvas(Canvas* c,int flag);
Canvas* c;
char* cur;

c=calloc(1,sizeof(Canvas));
initializeCanvas(c,flag);
assert((int)c->POSX==WIDTH/2+1);
assert((int)c->POSY==HEIGHT/2+1);
assert(c->col=='W');
assert(c->looparray_num==0);

// int checkVAR(Canvas *c, char* currentword);
//find the index of the VARname.
strcpy(c->table[c->looparray_num].name, "A");
strcpy(c->table[c->looparray_num].value,"2");
c->looparray_num++;
strcpy(c->table[c->looparray_num].name, "B");
strcpy(c->table[c->looparray_num].value,"3.5");
c->looparray_num++;
strcpy(c->table[c->looparray_num].name, "$C");
strcpy(c->table[c->looparray_num].value,"10000");
c->looparray_num++;
assert(checkVAR(c,"A")==0);
assert(checkVAR(c,"B")==1);
assert(checkVAR(c,"D")==-1);
assert(checkVAR(c,"$C")==2);
assert(checkVAR(c,"@C")==-1);

// bool isduplicate(char* cur, Canvas* c);
assert(isduplicate("A",c));
assert(!isduplicate("E",c));
assert(!isduplicate("",c));
assert(!isduplicate("090909",c));
assert(!isduplicate("+",c));
// void set_WORD(Canvas *c,char *currentword);
cur="\"BLACK\"";
set_WORD(c,cur);
assert(c->col=='K');
cur="RED";
assert(c->col!='R');
cur="\"RED\"";
set_WORD(c,cur);
assert(c->col='R');
cur="\"GREEN\"";
set_WORD(c,cur);
assert(c->col=='G');
cur="\"BLUE\"";
set_WORD(c,cur);
assert(c->col=='B');
cur="\"YELLOW\"";
set_WORD(c,cur);
assert(c->col=='Y');
cur="\"CYAN\"";
set_WORD(c,cur);
assert(c->col=='C');
cur="\"MAGENTA\"";
set_WORD(c,cur);
assert(c->col=='M');

// int isop(char *c);
cur="A";
assert(isop(cur)==0);
cur="+";
assert(isop(cur)==1);
cur="-";
assert(isop(cur)==1);
cur="=";
assert(isop(cur)==0);
cur="/";
assert(isop(cur)==1);
cur="*";
assert(isop(cur)==1);
cur="0";
assert(isop(cur)==0);
assert(isop("") == 0);
assert(isop("+-*/")==0);
// int isNumeric(const char* str);
cur="32";
assert(isNumeric(cur)==1);
cur="9.00";
assert(isNumeric(cur)==1);
cur="1000000000000000";
assert(isNumeric(cur)==1);
cur="-234";
assert(isNumeric(cur)==1);
cur="9/";
assert(isNumeric(cur)==0);
cur="ABC";
assert(isNumeric(cur)==0);
cur="-ABC";
assert(isNumeric(cur)==0);
cur="";
assert(isNumeric(cur)==0);
// double Calcul(Canvas *c,char* former,char* latter,char* oper);
assert((int)(Calcul(c,"A","2","+"))==4);
assert((int)(Calcul(c,"A","2","-"))==0);
assert((int)round((Calcul(c,"A","2.8","*")))==6);
assert((int)(Calcul(c,"A","2","/"))==1);
free(c);

}