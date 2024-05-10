# include "8q.h"
# include <string.h>
//remember to use 3-space before submit it.
//breadth-first search
int main(int argc,char* argv[]){
    test();
    int input;
    int argv_flag=2;
    int i;
    input=atoi(argv[1]);
    for(i=0;i<argc;i++){
        if(i==2){
            if(strcmp(argv[2],"-verbose")==0){
                argv_flag=1;
            }
        }
    }
    solve_Board(input,argv_flag);
}
// void print_board(Board b) {
//     for (int i = 0; i < b.width; i++) {
//         for (int j = 0; j < b.width; j++) {
//             printf("%c ", b.grid[i][j]);
//         }
//         printf("\n");
//     }
//     printf("\n");
// }
Board makeboard(int input){
    Board b;
    int i;
    int j;
    b.width=input;
    b.Q_num=0;
    for(i=0;i<input;i++){
      for(j=0;j<input;j++){
         b.grid[i][j]='0';
        }
    }
    for(i=0;i<MAXWH;i++){
        for(j=0;j<MAXWH;j++){
            b.Q_checked[i][j]=0;
        }
    }
    return b;
  }

void solve_Board(int input,int argv_flag){
    int i;
    int j;
    int index=1;
    //create the list of the Boardlist.
    static struct Board Boardlist[ListMAX];
    int f=0;
    Boardlist[0]=makeboard(input);
    while(Boardlist[f].Q_num<input && f<index){
        for(i=0;i<input;i++){
            for(j=0;j<input;j++){
                //1.Check Q.
                if(Check_Q(Boardlist[f],i,j,input)==1){
                    //Copy the parent board to children board.
                    Board b=create_children(Boardlist[f],i,j,input);
                    //print_board(b);
                    //printf("Now f is:%i,i=%i,j=%i \n",f,i,j);
                    //Start to check duplicate.
                    int temp_index=0;
                    int flag=0;
                    while(flag==0&&temp_index<index){
                        flag=Check_duplicates(b,Boardlist[temp_index],input);
                        temp_index++;
                    }
                    if(flag==0){
                        Boardlist[index]=b;
                        index++;
                        //printf("new valid board!,index:%i\n",index-1);
                        //print_board(Boardlist[index-1]);
                    }
                }
            }
        }
        f++;
    }
    int index_f=index-f;
    if(argv_flag==1){
        while(index>=f){
            for(i=0;i<input;i++){
                for(j=0;j<input;j++){
                    if(Boardlist[index].grid[i][j]=='Q'){
                        printf("%i",j);
                }
            }
        }
        printf("\n");
        index--;
    }
    printf("%i solutions\n",index_f);
    }
    if(argv_flag==2){
        printf("%i solutions\n",index_f);
    }
     //Print out.
}
Board create_children(Board parent,int i,int j,int input){
    Board b;
    b=parent;
    b.grid[i][j]='Q';
    b.Q_num+=1;
    b.Q_checked[0][i]=1;
    b.Q_checked[1][j]=1;
    b.Q_checked[2][i+j]=1;
    b.Q_checked[3][i-j+input]=1;
    return b;
}

bool Check_Q(Board b,int i,int j,int input){
    if(b.Q_checked[0][i]==1||b.Q_checked[1][j]==1||b.Q_checked[2][i+j]==1||b.Q_checked[3][i-j+input]==1){
        return 0;
    }
    return 1;
}

bool Check_duplicates(Board b1, Board b2,int input){
    for(int i=0;i<input;i++){
        for(int j=0;j<input;j++){
            if(b1.grid[i][j]!=b2.grid[i][j]){
                return 0;
            }
        }
    }
    return 1;
}

void test(){
    Board b1,b2;
    int width=5;
    //Check makeboard.
    b1=makeboard(width);
    b2=makeboard(width);
    //Check duplicates.
    assert(Check_duplicates(b1,b2,width)==1);
    b2.grid[3][3]='Q';
    assert(Check_duplicates(b1,b2,width)==0);
    b1.grid[3][3]='Q';
    assert(Check_duplicates(b1,b2,width)==1);
    b1.grid[3][4]='Q';
    assert(Check_duplicates(b1,b2,width)==0);
    //Check Check_Q.
    int i=2;
    int j=3;
    b1.Q_checked[0][i]=1;
    b1.Q_checked[1][j]=1;
    b1.Q_checked[2][i+j]=1;
    b1.Q_checked[3][i-j+width]=1;
    assert(Check_Q(b1,2,3,width)==0);
    assert(Check_Q(b1,2,0,width)==0);
    assert(Check_Q(b1,5,0,width)==0);
    //Check make children.
    b2=create_children(b1,2,3,width);
    assert(b2.Q_checked[0][2]==1);
}  
/*
DEBUG:
1.输入什么input，list就有多少个，不符合题意，尝试打印每一次的board失败。
2.发现check duplicate的时候会有两次出来，确定是check duplicate的问题
（修改为for循环，现在对了）
3.再也没进过while循环，目前的条件为：Boardlist[track].f==f-1，将f++写进了while中
4.每一次duplicate check结果都是1，不太可能,重新做了duplicate check没有问题
5.怀疑是static的问题，我的思路是，先放进去，如果不是的话就不index++，所以下一个index还是指向当前index
6.每次初始化一个新的b，然后b等于Boardlist[track]，如果通过所有测试则再讲Boardlist[track]=b,并且做后续操作

大框架打好了，就那三个功能
1.Check Q
2.Check duplicate
3.都通过的话，将create children放到Boardlist[index]上，并且index++

*重新理顺了一遍Q_checked 的逻辑，实际上储存的1指的是i!=[储存的对应的index]，所以如果任何有一个出现了1，return0，这个地方是不可以放Q的
如果通过该测试，创建b=Boardlist[f];b.grid[i][j]='Q';b.Q_num+=1;
*Duplicate

重新构造了一遍，发现每一次只进了一次while loop
换成while（1）会进入，说明是条件的问题：Boardlist[f].Q_num<input && f<index
flag一直是0，是duplicate的问题？duplicate 在后续的assert里面初步探查没有问题！
duplicate外置的循环有问题，flag==1时跳出所以while的条件应该是flag==0

* 输出了东西了！
但是从4开始会怪怪的
是那个duplicate_check输出0和1的问题
duplicate_check的while(flag==0&&temp_index<index)，这边的意思是“and”一个条件没满足就跳出来（
逻辑没理顺


11/15:
1.修改main为题目要求形式
2.tab的格式问题
3.extension（抄一个.jpg)
*/