#include "parse.h"
#include "test_Parse.h"

void PROG (Program *p){
    if(!strsame(p->wds[p->currentword],"START")){
        fprintf(stderr,"No Begin statement?");
        exit(EXIT_FAILURE);
    }
    p->currentword=p->currentword+1;
    INSLST(p);
}
//==========================INSL================================
void INSLST(Program *p){
    //printf("The INSLST now is:%s\n",p->wds[p->currentword]);
    if(strsame(p->wds[p->currentword],"END")){
        return;//end the whole
    }else{
        INS(p);
        p->currentword=p->currentword+1;
        if (!strsame(p->wds[p->currentword], "END")) {
            INSLST(p);
        }
    }
    return;
}

void INS(Program *p){
    //printf("The INS now is:%s\n",p->wds[p->currentword]);
    if (strsame(p->wds[p->currentword], "FORWARD")) {
        FWD(p);
    } else if (strsame(p->wds[p->currentword], "RIGHT")) {
        RGT(p);
    }else if (strsame(p->wds[p->currentword], "COLOUR")) {
        COL(p);
    }else if (strsame(p->wds[p->currentword], "LOOP")) {
        LOOP(p);
    }else if (strsame(p->wds[p->currentword], "SET")) {
        SET(p);
    }else {
        fprintf(stderr,"Invalid syntax for INS\n");
        exit(EXIT_FAILURE);
    }
}
//============================INSLST=============================
void FWD(Program *p){
    if(!strsame(p->wds[p->currentword],"FORWARD")){
        fprintf(stderr,"Can't find 'FORWARD'\n");
        exit(EXIT_FAILURE);
    }
    p->currentword=p->currentword+1;
    VARNUM(p);
    return;
}

void RGT(Program *p){
    if(!strsame(p->wds[p->currentword],"RIGHT")){
        fprintf(stderr,"Can't find 'RIGHT'\n");
        exit(EXIT_FAILURE);
    }
    p->currentword=p->currentword+1;
    VARNUM(p);
    return;
}
void COL(Program *p){
    if(!strsame(p->wds[p->currentword],"COLOUR")){
        fprintf(stderr,"Can't find 'COLOUR'\n");
        exit(EXIT_FAILURE);
    }
    p->currentword=p->currentword+1;
    //VAR or WORD??
    char* currentword=p->wds[p->currentword];
    if(currentword[0]=='"'){
        WORD(p);
        return;
    }
    if(currentword[0]=='$'){
        VAR(p);
        return;
    }

}
//<LOOP>   ::= "LOOP" <LTR> "OVER" <LST> <INSLST>
void LOOP(Program *p){
    //Check "loop"
   if(!strsame(p->wds[p->currentword],"LOOP")){
        fprintf(stderr,"Can't find 'LOOP'\n");
        exit(EXIT_FAILURE);
    } 

    p->currentword=p->currentword+1;
    LTR(p);
    p->currentword=p->currentword+1;
    if(!strsame(p->wds[p->currentword],"OVER")){
        fprintf(stderr,"Can't find 'OVER'\n");
        exit(EXIT_FAILURE);
    } 
    p->currentword=p->currentword+1;
    LST(p);
    p->currentword=p->currentword+1;
    INSLST(p);
    return;
}
//<SET> ::= "SET" <LTR> "(" <PFIX>
void SET(Program *p){
    //Check SET
    if(!strsame(p->wds[p->currentword],"SET")){
        fprintf(stderr,"Can't find 'SET'\n");
        exit(EXIT_FAILURE);
    } 
    //<LTR>
    p->currentword=p->currentword+1;
    LTR(p);
    p->currentword=p->currentword+1;
    //Check "("
    if(!strsame(p->wds[p->currentword],"(")){
        fprintf(stderr,"Can't find '('\n");
        exit(EXIT_FAILURE);
    }
    //<PFIX>
    p->currentword=p->currentword+1;
    PFIX(p);
    return;
}
//============================VAR&NUM=============================
void VARNUM(Program *p){
    char* currentword=p->wds[p->currentword];
    if(currentword[0]=='-' ||isdigit(currentword[0])){
        NUM(p);
    }
    if(currentword[0]=='$'){
        VAR(p);
    }
    return;
}

void VAR(Program *p){
    char * currentword=p->wds[p->currentword];
    if (currentword[0] == '$') {
        LTR(p);
    } else {
        fprintf(stderr,"Invalid VAR format.\n");
        exit(EXIT_FAILURE);
        // Handle the error or return appropriately
    }
    return;
}
//rewrite.
void NUM(Program *p){
    char *currentword= p->wds[p->currentword];
    char* endptr;
    strtod(currentword, &endptr);
    if(*endptr=='\0' || *endptr ==' '){
        return;
    }else{
        fprintf(stderr,"NUM CHECK ERROR!");
        exit(EXIT_FAILURE);
    }
    //Check for negative
    // if (currentWord[0]=='-') {
    //     if (strchr(currentWord+1, '.') != NULL) {
    //         float negativeFloatValue = -atof(currentWord + 1);
    //         return;
    //     } else {
    //         int negativeIntValue =-atoi(currentWord+1);
    //         return;
    //     }
    // } else {
    //     if (strchr(currentWord, '.') != NULL) {
    //         float floatValue=atof(currentWord);
    //     } else {
    //         int intValue=atoi(currentWord);
    //     }
    //     return;
    // }
}

void LTR(Program *p){
    if (strlen(p->wds[p->currentword])==1 && isupper(p->wds[p->currentword][0])) {
        return;
    }else if(strlen(p->wds[p->currentword])==2 && isupper(p->wds[p->currentword][1])){
        return;
    }else{
        fprintf(stderr,"Invalid LTR format.\n");
        exit(EXIT_FAILURE);
    }
    return;
}
//============================WORD=============================
void WORD(Program *p){
    char* currentword=p->wds[p->currentword];
    int len=strlen(currentword);
    if(len>1 && currentword[0]=='"' && currentword[len - 1] == '"'){
        return;
    }else{
        fprintf(stderr,"WORD CHECK INVALID.\n");
        exit(EXIT_FAILURE);
    }
}

//============================ITEMS=============================
void LST(Program *p){
    if(!strsame(p->wds[p->currentword],"{")){
        fprintf(stderr,"Can't find '{'");
        exit(EXIT_FAILURE);
    }
    p->currentword=p->currentword+1;
    ITEMS(p);
    return;
}
void ITEMS(Program *p){
    if(*p->wds[p->currentword]=='}'){
        return;
    //ITEM -> ITEMS 
    }else{
       //p->currentword=p->currentword+1;
       ITEM(p); 
       p->currentword=p->currentword+1;
       ITEMS(p);
    }
    return;
}
void ITEM(Program *p){
    char* currentword=p->wds[p->currentword];
    if(currentword[0]=='"'){
        WORD(p);
    }else if(currentword[0]=='-' || isdigit(currentword[0]) || currentword[0]=='&'){
        VARNUM(p);
    }else{
        fprintf(stderr,"Can't find valid ITEM?\n");
        exit(EXIT_FAILURE);
    }
    return;
}


//============================OPERATIONS=============================
//<OP><PFIX>|<VARNUM><PFIX>|")"
void PFIX(Program *p){
    //<OP><PFIX>
    char* currentword=p->wds[p->currentword];
    if(isop(currentword)){
        p->currentword=p->currentword+1;
        PFIX(p);
    //<VARNUM><PFIX>
    }else if(currentword[0]=='-' || isdigit(currentword[0]) || currentword[0]=='$'){
        p->currentword=p->currentword+1;
        PFIX(p);
    }else if(strsame(p->wds[p->currentword],")")){
        //p->currentword=p->currentword+1;
        //printf("PFIX-now is :%s\n",p->wds[p->currentword]);
        return;
    }else{
        fprintf(stderr,"PFIX ERROR!\n");
        exit(EXIT_FAILURE);
    }
}
void OP(Program *p){
    char* currentword=p->wds[p->currentword];
    if (*currentword=='+'||*currentword=='-'||*currentword=='/'|| (*currentword== '*') ){
        return;
    }
    fprintf(stderr,"Operations invalid!\n");
    exit(EXIT_FAILURE);  
}

int isop(char *c){
    if (*c=='+' || *c=='-' || *c=='/'|| *c== '*'){
        return 1;
    }
    return 0;
}
//============================TESTS=============================
// void test(void){
// //     Program *p=(Program*)calloc(1,sizeof(Program));
// //     strcpy(p->wds[0],"START");
// // //===============Check the simple functions======================
// //     //Check NUM
// //     strcpy(p->wds[0],"0");
// //     strcpy(p->wds[0],"-19");
// //     strcpy(p->wds[0],"70.0");
// //     strcpy(p->wds[0],"900000");
// //     //Check LTR
// //     strcpy(p->wds[0],"A");
// //     strcpy(p->wds[0],"900");
// //     strcpy(p->wds[0],"a");
// //     strcpy(p->wds[0],"*");
// //     //Check WORD(?????????????)
// //     strcpy(p->wds[0],"000");
// //     //Check OP
// //     strcpy(p->wds[0],"*");
// //     strcpy(p->wds[0],"9");
// //     strcpy(p->wds[0],"+");
// //     strcpy(p->wds[0],"-");
// //     strcpy(p->wds[0],"?");
// //     //
// //     free(p);
// }
//============================MAIN=============================
int main(int argc, char* argv[]){
    test();
    if (argc<2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        printf("Error opening file: %s\n", filename);
        return 1;
    }
    int i=0;
    Program* p = calloc(1,sizeof(Program));

    while(fscanf(f,"%s",p->wds[i++])==1 && i<MAXNUMTOKENS);
    PROG(p);
    free(p);
    fclose(f); 
    return 0;
}







