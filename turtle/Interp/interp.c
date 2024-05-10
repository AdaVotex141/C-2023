#include "interp.h"
#include "../neillsimplescreen.h"
#include "../STACK/stack.h" 
#include "test_Interp.h"
#define M_PI 3.14159265358979323846

void PROG (Program *p, Canvas *c,int flag){
    if(!strsame(p->wds[p->currentword],"START")){
        fprintf(stderr,"No Begin statement?\n");
        exit(EXIT_FAILURE);
    }
    if(flag==SCREEN){
    //neil simple screen:clean all.
        neillclrscrn();
        p->currentword=p->currentword+1;
        initializeCanvas(c,flag);
        INSLST(p,c,flag);
    //reset
        printf("\033[34;1H");
        neillreset();
    }else if(flag==TXTFILE){
        p->currentword=p->currentword+1;
        initializeCanvas(c,flag);
        INSLST(p,c,flag);
    //reset
    }else if(flag==POSTFILE){
        p->currentword=p->currentword+1;
        initializeCanvas(c,flag);
        INSLST(p,c,flag); 
    }

//neil simple screen:clean all.
}

//==========================initialize=====================
void initializeCanvas(Canvas *c,int flag) {
    int centerX = WIDTH/2+1;
    int centerY = HEIGHT/2+1;
    c->dir=0;
    c->POSX=centerX;
    c->POSY=centerY;
    c->col='W';
    c->looparray_num=0;
    (void)c;

    if(flag==TXTFILE){
        for(int i=0;i<HEIGHT;++i){
            for(int j=0;j<WIDTH;++j){
                c->array[i][j]=' ';
                }
            }
    }else if(flag==POSTFILE){
        c->postROW=0;
        c->POSX=PS_X;
        c->POSY=PS_Y;
    }
}

//==========================INSL================================
void INSLST(Program *p,Canvas *c,int flag){
    if(strsame(p->wds[p->currentword],"END")){
        return;//end the whole
    }else{
        INS(p,c,flag);
        p->currentword=p->currentword+1;
        if (!strsame(p->wds[p->currentword], "END")) {
            INSLST(p,c,flag);
        }
    }
    return;
}

void INS(Program *p, Canvas *c,int flag){
    if (strsame(p->wds[p->currentword], "FORWARD")) {
        FWD(p,c,flag);
    } else if (strsame(p->wds[p->currentword], "RIGHT")) {
        RGT(p,c);
    }else if (strsame(p->wds[p->currentword], "COLOUR")) {
        COL(p,c);
    }else if (strsame(p->wds[p->currentword], "LOOP")) {
        LOOP(p,c,flag);
    }else if (strsame(p->wds[p->currentword], "SET")) {
        SET(p,c);
    }else {
        fprintf(stderr,"Invalid syntax for INS\n");
        exit(EXIT_FAILURE);
    }
}

//============================INSLST=============================
/*
FWD:direction->FWD
direction->0~9 define default:0
*/
void FWD(Program *p, Canvas *c,int flag){
    if(!strsame(p->wds[p->currentword],"FORWARD")){
        fprintf(stderr,"Can't find 'FORWARD'\n");
        exit(EXIT_FAILURE);
    }
    p->currentword=p->currentword+1;

    if(flag==SCREEN){
        FWD_SCREEN(p,c);
    }else if(flag==TXTFILE){
        FWD_TXT(p,c);
    }else{
        FWD_POST(p,c);
    }
    return;
}

void FWD_SCREEN(Program *p,Canvas *c){
    char* cur=VARNUM(p,c);
    //currentword:VAR or NUM?
    if(cur[0]=='$'){
        //is VAR
        int index=checkVAR(c,cur);
        int cur_num=atoi(c->table[index].value);
        for(int i=0; i<cur_num;i++){
            setCOLOUR_NEILL(c);
            printf("\033[%d;%dH", (int)round(c->POSY), (int)round(c->POSX));
            //char col=c->col;
            //setCOLOUR_NEILL(c);
            printf("%c",c->col);
        //get the next posX and posY with dir
            double direction=c->dir;
            c->POSX+=sin(direction);
            c->POSY-=cos(direction);
        }
        neillbusywait(1);
        fflush(stdout);
    }else{
        int cur_num=atoi(cur);
        for(int i=0; i<cur_num;i++){
            setCOLOUR_NEILL(c);
            printf("\033[%d;%dH", (int)round(c->POSY), (int)round(c->POSX));
            printf("%c",c->col);
        //get the next posX and posY with dir
            double direction=c->dir;
            c->POSX+=sin(direction);
            c->POSY-=cos(direction);
        }
        neillbusywait(1);
        fflush(stdout);
        c->POSX = round(c->POSX);
        c->POSY = round(c->POSY);
    }
}

void FWD_TXT(Program *p, Canvas *c){
    char* cur=VARNUM(p,c);
    //currentword:VAR or NUM?
    if(cur[0]=='$'){
        //is VAR
        int index=checkVAR(c,cur);
        int cur_num=atoi(c->table[index].value);
        for(int i=0; i<cur_num;i++){
            int x = (int)round(c->POSX);
            int y = (int)round(c->POSY);
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            c->array[y][x] = c->col;
            }
        //get the next posX and posY with dir
            double direction=c->dir;
            c->POSX+=sin(direction);
            c->POSY-=cos(direction);
        }
    }else{
        int cur_num=atoi(cur);
        for(int i=0; i<cur_num;i++){
            int x = (int)round(c->POSX);
            int y = (int)round(c->POSY);
            if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
            c->array[y][x] = c->col;
            }
        //get the next posX and posY with dir
            double direction=c->dir;
            c->POSX+=sin(direction);
            c->POSY-=cos(direction);
        }
        c->POSX = round(c->POSX);
        c->POSY = round(c->POSY);
    }
}

void FWD_POST(Program *p, Canvas *c){
    char* cur=VARNUM(p,c);
    fprintf(p->ps_out,"newpath\n");
    //currentword:VAR or NUM?
    if(cur[0]=='$'){
        //is VAR
        int index=checkVAR(c,cur);
        int cur_num=atoi(c->table[index].value);
        double x =(c->POSX);
        double y =(c->POSY);
        fprintf(p->ps_out,"%f %f %s",x,y,"moveto\n");
        //MOVETO(c,x,y);
        for(int i=0; i<cur_num;i++){
            x=(c->POSX);
            y=(c->POSY);
        //get the next posX and posY with dir
            double direction=c->dir;
            c->POSX+=sin(direction);
            c->POSY+=cos(direction);
        }
        x=(c->POSX);
        y=(c->POSY);
        fprintf(p->ps_out,"%f %f %s",x,y,"lineto\n");
        //LINETO(c,x,y);
    }else{
        int cur_num=atoi(cur);
        double x=(c->POSX);
        double y=(c->POSY);
        fprintf(p->ps_out,"%f %f %s",x,y,"moveto\n");
        //MOVETO(c,x,y);
        for(int i=0; i<cur_num;i++){
            x=(c->POSX);
            y=(c->POSY);
        //get the next posX and posY with dir
            double direction=c->dir;
            c->POSX+=sin(direction);
            c->POSY+=cos(direction);
        }
        x=(c->POSX);
        y=(c->POSY);
        fprintf(p->ps_out,"%f %f %s",x,y,"lineto\n");
        x=(c->POSX);
        y=(c->POSY);
    }
    SETRGBCOLOUR(p,c);
    //stroke
    fprintf(p->ps_out,"stroke\n");
}


void RGT(Program *p,Canvas *c){
    if(!strsame(p->wds[p->currentword],"RIGHT")){
        fprintf(stderr,"Can't find 'RIGHT'\n");
        exit(EXIT_FAILURE);
    }
    p->currentword=p->currentword+1;
    //VARNUM(p,c);
    char* currentword=VARNUM(p,c);
    //currentword:VAR or NUM?
    if(currentword[0]=='$'){
        //find the arrayROW number in looparray.
        printf("a variable behind RIGHT!");
    }else{
        int cur_num=atoi(currentword);
        double radians=(cur_num)*M_PI/180.0;
        c->dir+=radians;
    }
    return;
}

//find the index of the VARname.
int checkVAR(Canvas* c,char* currentword){
    for(int i=0;i<(c->looparray_num);i++){
        if(strcmp(c->table[i].name,currentword)==0){
            return i;
        }else if(c->table[i].name[0] == currentword[1]){   
            return i;
        }
    }
    return -1;
}

/*
check colour:
"YELLOW-Y", "CYAN-C", "MAGENTA-M", "WHITE"
"BLACK", "RED", "GREEN", "BLUE"
*/
void COL(Program *p, Canvas *c){
    if(!strsame(p->wds[p->currentword],"COLOUR")){
        fprintf(stderr,"Can't find 'COLOUR'\n");
        exit(EXIT_FAILURE);
    }
    p->currentword=p->currentword+1;
    //VAR or WORD??
    char* currentword=p->wds[p->currentword];
    if(currentword[0]=='"'){
        WORD(p,c);
        return;
    }
    if(currentword[0]=='$'){
        int index=checkVAR(c,currentword);
        char* cur_name=c->table[index].value;
        set_WORD(c,cur_name);
        return;
    }
}

//<LOOP>   ::= "LOOP" <LTR> "OVER" <LST> <INSLST>
void LOOP(Program *p, Canvas *c,int flag){
    //Check "loop"
    if(!strsame(p->wds[p->currentword],"LOOP")){
        fprintf(stderr,"Can't find 'LOOP'\n");
        exit(EXIT_FAILURE);
    } 
    p->currentword=p->currentword+1;
    //store LTR
    char* cur=LTR(p);
    strcpy(c->table[c->looparray_num].name,LTR(p));
    c->looparray_num++;

    p->currentword=p->currentword+1;
    if(!strsame(p->wds[p->currentword],"OVER")){
        fprintf(stderr,"Can't find 'OVER'\n");
        exit(EXIT_FAILURE);
    } 
    p->currentword=p->currentword+1;
    int L_bracket_num=p->currentword;
    LST(p,c);
    int R_bracket_num=p->currentword;
    p->currentword=p->currentword+1;

    //Doloop:
    for(int i=L_bracket_num+1;i<R_bracket_num;i++){
        p->currentword=i;
        //set the p->wds[p->currentword] to the table.
        setVALUE(p,c,cur);
        p->currentword=R_bracket_num+1;
        INSLST(p,c,flag);
    }
    return;
}

void setVALUE(Program *p, Canvas *c, char* currentword){
    int index=checkVAR(c,currentword);
    strcpy(c->table[index].value,p->wds[p->currentword]);
}

//<SET> ::= "SET" <LTR> "(" <PFIX>
//cur-> <LTR>
//cur2-> (&<LTR>)
void SET(Program *p, Canvas *c){
    //Check SET
    if(!strsame(p->wds[p->currentword],"SET")){
        fprintf(stderr,"Can't find 'SET'\n");
        exit(EXIT_FAILURE);
    } 
    //update <LTR>
    p->currentword=p->currentword+1;
    char cur[MAXNUMTOKENS];
    strcpy(cur, LTR(p));
    //check duplicate:
    if (!isduplicate(cur, c)) {
        strcpy(c->table[c->looparray_num].name,cur);
        c->looparray_num++;
    }
    
    p->currentword=p->currentword+1;
    //Check "("
    if(!strsame(p->wds[p->currentword],"(")){
        fprintf(stderr,"Can't find '('\n");
        exit(EXIT_FAILURE);
    }
    //<PFIX>
    p->currentword=p->currentword+1;

    //check the first element after (
    char cur2[MAXNUMTOKENS];
    strcpy(cur2, p->wds[p->currentword]);
    if(isNumeric(cur2)){
        //If is a number, set the value of letter and check for ")" then return.
        int index=checkVAR(c,cur);
        strcpy(c->table[index].value, cur2);
        //check for ")"
        p->currentword=p->currentword+1;
        if(strsame(p->wds[p->currentword],")")){
          return;  
        }else{
            fprintf(stderr,"PFIX ERROR!\n");
            exit(EXIT_FAILURE);
        }
    }else{
        //The first element after ( should be $<LTR>
        stack* s = stack_init();
        PFIX(p,c,cur,s);
        stack_free(s);
    }
    return;
}

bool isduplicate(char* cur, Canvas* c){
    for(int i=0;i<(c->looparray_num);i++){
        if(strcmp(c->table[i].name,cur)==0){
            return true;
        }
    }
    return false;
}

int isNumeric(const char* str) {
    char* endptr;
    strtod(str, &endptr);
    return(*endptr=='\0' && endptr!=str);
}

//============================VAR&NUM=============================
char *VARNUM(Program *p, Canvas *c){
    char* currentword=p->wds[p->currentword];
    if(currentword[0]=='-' ||isdigit(currentword[0])){
        char* currentNUM=NUM(p);
        return currentNUM;
    }
    if(currentword[0]=='$'){
        char* currentVAR=VAR(p);
        //find '$', check c->looparray[i][LTRcol]
        return currentVAR;
    }
    (void)c;
    return NULL;
}

char *VAR(Program *p){
    char * currentword=p->wds[p->currentword];
    if (currentword[0] == '$') {
        //check LTR.
        char* currentVAR=LTR(p);
        return currentVAR;
    } else {
        fprintf(stderr,"Invalid VAR format.\n");
        exit(EXIT_FAILURE);
        // Handle the error or return appropriately
    }
}
//rewrite.
char *NUM(Program *p){
    char *currentNUM= p->wds[p->currentword];
    char* endptr;
    strtod(currentNUM, &endptr);
    if(*endptr=='\0' || *endptr ==' '){
        return currentNUM;
    }else{
        fprintf(stderr,"NUM CHECK ERROR!");
        exit(EXIT_FAILURE);
    }
}

char *LTR(Program *p){
    char* currentLTR=p->wds[p->currentword];
    if (strlen(p->wds[p->currentword])==1 && isupper(p->wds[p->currentword][0])) {
        return currentLTR;
    }else if(strlen(p->wds[p->currentword])==2 && isupper(p->wds[p->currentword][1])){
        return currentLTR;
    }else{
        fprintf(stderr,"Invalid LTR format.\n");
        exit(EXIT_FAILURE);
    }
}
//============================WORD=============================
void WORD(Program *p,Canvas *c){
    char* currentword=p->wds[p->currentword];
    int len=strlen(currentword);
    if(len>1 && currentword[0]=='"' && currentword[len - 1] == '"'){
        set_WORD(c,currentword);
        return;
    }else{
        fprintf(stderr,"WORD CHECK INVALID.\n");
        exit(EXIT_FAILURE);
    }
}
void set_WORD(Canvas *c,char *currentword){
    //now currentword's length is 5, " R E D"
    if(strcmp(currentword,"\"BLACK\"")==0) {
        c->col='K';
    }else if(strcmp(currentword,"\"RED\"")==0) {
        c->col='R';
    }else if(strcmp(currentword,"\"GREEN\"")==0) {
        c->col='G';
    }else if(strcmp(currentword,"\"BLUE\"")==0) {
        c->col='B';
    }else if(strcmp(currentword,"\"YELLOW\"")==0) {
        c->col='Y';
    }else if(strcmp(currentword,"\"CYAN\"")==0) {
        c->col='C';
    }else if(strcmp(currentword,"\"MAGENTA\"")==0) {
        c->col='M';
    }else if(strcmp(currentword,"\"WHITE\"")==0) {
        c->col='W';
    }else{
        fprintf(stderr,"INVALID COLOUR WORD!");
        exit(EXIT_FAILURE);
    }
}


//============================ITEMS=============================
void LST(Program *p,Canvas *c){
    if(!strsame(p->wds[p->currentword],"{")){
        fprintf(stderr,"Can't find '{'");
        exit(EXIT_FAILURE);
    }
    p->currentword=p->currentword+1;
    ITEMS(p,c);
    return;
}
void ITEMS(Program *p,Canvas *c){
    if(*p->wds[p->currentword]=='}'){
        return;
    //ITEM -> ITEMS 
    }else{
       ITEM(p,c); 
       p->currentword=p->currentword+1;
       ITEMS(p,c);
    }
    return;
}
void ITEM(Program *p, Canvas *c){
    //ITEMS store what is in the loop index.
    char* currentword=p->wds[p->currentword];
    if(currentword[0]=='"'){
        WORD(p,c);
        
    }else if(currentword[0]=='-' || isdigit(currentword[0]) || currentword[0]=='&'){
        VARNUM(p,c);
    }else{
        fprintf(stderr,"Can't find valid ITEM?\n");
        exit(EXIT_FAILURE);
    }
    return;
}


//============================OPERATIONS=============================
//<OP><PFIX>|<VARNUM><PFIX>|")"
void PFIX(Program *p,Canvas* c, char* cur,stack* s){
    char* current=p->wds[p->currentword];
    char* former;
    char* latter;
    //store &<LTR>
    //stacktype name;
    //<OP><PFIX>
    if(isop(current)){
        char* oper=current;
        //pop the last two elements out of stack and do the calculation.
        stack_pop(s,&latter);
        stack_pop(s,&former);
        double result=Calcul(c,former,latter,oper);
        //store the result in the cur-table.
        int index=checkVAR(c,cur);
        char str2[10];
        snprintf(str2, sizeof(str2), "%.2lf", result);
        strcpy(c->table[index].value,str2);

        p->currentword=p->currentword+1;
        PFIX(p,c,cur,s);
    //<VARNUM><PFIX>
    }else if(current[0]=='-'|| isdigit(current[0]) || current[0]=='$'){
        //push into stack.
        stack_push(s,current);
        p->currentword=p->currentword+1;
        PFIX(p,c,cur,s);
    }else if(strsame(p->wds[p->currentword],")")){
        //destroy_stack(s);
        return;
    }else{
        fprintf(stderr,"PFIX ERROR!\n");
        exit(EXIT_FAILURE);
    }
}


double Calcul(Canvas *c,char* former,char* latter,char* oper){
    double latterINT=strtod(latter,NULL);
    int index=checkVAR(c,former);
    double formerINT=strtod(c->table[index].value,NULL);
    double result;

    if(*oper=='+'){
        result=latterINT+formerINT;
    }else if(*oper=='-'){
        result=formerINT-latterINT;
    }else if(*oper=='/'){
        result=formerINT/latterINT;
    }else if(*oper=='*'){
        result=formerINT*latterINT;
    }
    return result;
}


void OP(Program *p){
    char* currentword=p->wds[p->currentword];
    if (*currentword=='+'||*currentword=='-'||*currentword=='/'|| (*currentword== '*') ){
        return;
    }else{
        fprintf(stderr,"Operations invalid!\n");
        exit(EXIT_FAILURE);  
    }
}

int isop(char *c) {
    int count = 0;
    while (*c!='\0') {
        if (*c =='+' || *c =='-' || *c =='/' || *c=='*') {
            count++;
        }
        c++;
    }
    return count == 1;
}
//==========================Post-related=====================

void SETRGBCOLOUR(Program *p, Canvas *c){
    //0.8 0.8 0.8 setrgbcolor 
    if( c->col=='K') {
        //0 0 0
        c->colour[left]=0;
        c->colour[middle]=0;
        c->colour[right]=0;
        fprintf(p->ps_out,"%d %d %d %s",(int)c->colour[left],
        (int)c->colour[middle],(int)c->colour[right],"setrgbcolor\n");
    }else if(c->col=='R') {
        //1 0 0
        c->colour[left]=1;
        c->colour[middle]=0;
        c->colour[right]=0;   
        fprintf(p->ps_out,"%d %d %d %s",(int)c->colour[left],
        (int)c->colour[middle],(int)c->colour[right],"setrgbcolor\n");
    }else if(c->col=='G') {
        //0 1 0
        c->colour[left]=0;
        c->colour[middle]=1;
        c->colour[right]=0;
        fprintf(p->ps_out,"%d %d %d %s",(int)c->colour[left],
        (int)c->colour[middle],(int)c->colour[right],"setrgbcolor\n");
    }else if(c->col=='B') {
        //0 0 1
        c->colour[left]=0;
        c->colour[middle]=0;
        c->colour[right]=1;
        fprintf(p->ps_out,"%d %d %d %s",(int)c->colour[left],
        (int)c->colour[middle],(int)c->colour[right],"setrgbcolor\n");
    }else if(c->col=='Y') {
        //1 1 0
        c->colour[left]=1;
        c->colour[middle]=1;
        c->colour[right]=0;
        fprintf(p->ps_out,"%d %d %d %s",(int)c->colour[left],
        (int)c->colour[middle],(int)c->colour[right],"setrgbcolor\n");
    }else if(c->col=='C') {
        //0 1 1
        c->colour[left]=0;
        c->colour[middle]=1;
        c->colour[right]=1;
        fprintf(p->ps_out,"%d %d %d %s",(int)c->colour[left],
        (int)c->colour[middle],(int)c->colour[right],"setrgbcolor\n");
    }else if(c->col=='M') {
        //1 0 1
        c->colour[left]=1;
        c->colour[middle]=0;
        c->colour[right]=1;
        fprintf(p->ps_out,"%d %d %d %s",(int)c->colour[left],
        (int)c->colour[middle],(int)c->colour[right],"setrgbcolor\n");
    }else if(c->col=='W') {
        //0.8 0.8 0.8
        c->colour[left]=0.8;
        c->colour[middle]=0.8;
        c->colour[right]=0.8;
        fprintf(p->ps_out,"%.1f %.1f %.1f %s",c->colour[left],
        c->colour[middle],c->colour[right],"setrgbcolor\n");
    }
}

void setCOLOUR_NEILL(Canvas *c){
        if( c->col=='K') {
        neillfgcol(black);
    }else if(c->col=='R') {
        neillfgcol(red);
    }else if(c->col=='G') {
        neillfgcol(green);
    }else if(c->col=='B') {
        neillfgcol(blue);
    }else if(c->col=='Y') {
        neillfgcol(yellow);
    }else if(c->col=='C') {
        neillfgcol(cyan);
    }else if(c->col=='M') {
       neillfgcol(magenta);
    }else if(c->col=='W') {
       neillfgcol(white);
    }
}

//============================MAIN=============================
int main(int argc, char* argv[]){
    test();
    char *filename = argv[1];
    FILE *f = fopen(filename, "r");
    int i=0;
    Program* p = calloc(1,sizeof(Program));
    Canvas* c = calloc(1,sizeof(Canvas));
    while(fscanf(f,"%s",p->wds[i++])==1 && i<MAXNUMTOKENS);
    int flag=0;
    if(argc<sub){
        flag=SCREEN;
        PROG(p,c,flag);
        fclose(f); 
    }else{
        char cmd[MAX_LOOP];
        char *outputFilename = argv[2];
        char *file_extension = strrchr(outputFilename, '.');
         if(strcmp(file_extension,".ps")==0){
            flag=POSTFILE;
            p->ps_out=fopen(argv[2],"w");
            fprintf(p->ps_out,"0.2 setlinewidth\n");
            fprintf(p->ps_out,"10 10 scale\n");
            PROG(p,c,flag);
            fprintf(p->ps_out,"showpage\n");
            fclose(p->ps_out); 
            snprintf(cmd, sizeof(cmd), "gs -sDEVICE=pdfwrite -sOutputFile=%s.pdf -dBATCH -dNOPAUSE %s > /dev/null", argv[1], argv[2]);
            system(cmd);
        }else if (strcmp(file_extension, ".txt") == 0) {
                flag=TXTFILE;
                //do the postscript thing.
                PROG(p,c,flag);
                FILE *file_output=fopen(outputFilename, "w");
                if (file_output == NULL) {
                        fprintf(stderr, "cannot open file!\n");
                        exit(EXIT_FAILURE);
                    }
                for (int i=0; i<HEIGHT;i++) {
                    for (int j=0;j<WIDTH;j++) {
                        fprintf(file_output, "%c", c->array[i][j]);
                    }
                        fprintf(file_output, "\n"); 
                    }
                fclose(file_output);   
        }
    }
    free(p);
    free(c);
    return 0;
}

