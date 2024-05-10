#include "specific.h" 
#define LISTSTRLEN 1000
#define MAXTEMPLEN 50

/*
REMINDER:
* int row:the row of the big vertical array.0~29
* int size:the size of each row contains, for row=2, it should be 2^2=4
size=pow_self(row)
* int indx:the indx of the block,like 15 in row 5.

* int actual:the actual indx in a row, for 15 in row 5, it should be 0.
actual=indx-row_first
      =indx-find_row_with_sum(indx)

* int row_first,the indx of the first element in a row.
row_first=sum=2^0+2^1+...+2^row-1
//whether -1 or not DOUBLE CHECK!!!!
int row_last=row_first+size-1.
            =find_row_last.

* int MaxIndex:the result of bsa_maxindex(bsa* b)

*/
bsa* bsa_init(void){
   bsa* b = (bsa*)calloc(1,sizeof(bsa));
      //create array of pointers in the rows
      for (int i = 0; i < BSA_ROWS; i++) {
         b->arr[i] = NULL;
   }
   return b;
}

bool bsa_set(bsa* b, int indx, int d){
   int row=find_row(indx);
   int size=pow_self(row);
   //check false situations.
   if(!b){
      return false;
}
   //check whether this array has been create or not.
   if(b->arr[row]==NULL){
      //create new Rarr if there aren't any.
      b->arr[row]=(Node*)calloc(size, sizeof(Node));
   }
   int actual=indx-find_indx_first(indx);
   //printf("find_indx_first:%d\n",find_indx_first(indx));
   //printf("actual:%d\n",actual);
   b->arr[row][actual].value=d;
   b->arr[row][actual].created=1;    
   return true;
}

int* bsa_get(bsa* b, int indx){
   int row=find_row(indx);
   int actual=indx-find_indx_first(indx);
   //the row hasn't been allocated.
   if(b->arr[row]==NULL){
      return NULL;
   }
   if(b->arr[row][actual].created==1){
      //return (int*)b->arr[row][actual];
      return &b->arr[row][actual].value;
      //return b->arr[row][actual];
   }else{
      return NULL;
   }
}

bool bsa_delete(bsa* b, int indx){
   int row=find_row(indx);
   int actual=indx-find_indx_first(indx);
   int size=pow_self(row);
   int count=0;
   if(!b || (b->arr[row][actual].created==0)){
      return false;
   }
   //delete.Garbage Collector!
   b->arr[row][actual].created=0;
   //check if it is the last elements in the row.
   for(int i=0;i<size;i++){
      if(b->arr[row][actual].created==0){
         count++;
      }
      if(count==0){
         free(b->arr[row]);
      }
   }
   return true;
}


// -1 if no cells have been written to yet
int bsa_maxindex(bsa* b){
   int row;
   int MaxIndex=-1;
   int indx=0;
   if(b==NULL){
      return -1;
   }
   for(row=0;row<BSA_ROWS;row++){
      //Do things in every row.
      if(b->arr[row]!=NULL){
         int actual=0;
         int size=pow_self(row);
         int row_last=find_row_last(row);
         while(actual<size){
            if(b->arr[row][actual].created==1){
              indx=row_last-size+actual+1;
              MaxIndex=max(MaxIndex,indx);
            }
              actual++;
         }
      }
   }
   return MaxIndex;
}



bool bsa_tostring(bsa* b, char* str){
   int MaxIndex=bsa_maxindex(b);
   str[0] = '\0';
   char* str_void1="{";
   char* str_void2="}";
   int indx=0;  
   int row=0;
   if(b==NULL || str==NULL){
      return false;
   }
   for(row=0;row<BSA_ROWS && indx<=MaxIndex;row++){
      strcat(str, str_void1);
      if(b->arr[row]!=NULL){
         int only_flag=false;
         int size=pow_self(row);
         int row_last=find_row_last(row);
         for(int actual=0;actual<size;actual++){
          if(b->arr[row][actual].created==1){
              indx=row_last-size+actual+1;
              char temp[MAXTEMPLEN];
                if(only_flag==true){
                  strcat(str," ");
                  }
                  snprintf(temp, sizeof(temp), "[%d]=%d", indx, b->arr[row][actual].value);
                  strcat(str,temp);
                  only_flag=true;
              }
         }
      }
      if(indx<MaxIndex){
         strcat(str, str_void2);
      }else{
         strcat(str, str_void2);
         return true;
      }
  }
  return true;
}

//check if there are still things in the arrays.if created==1,set it to zero.

bool bsa_free(bsa *b) {
   if(!b){
      return false;
   }
   for(int row=0;row<BSA_ROWS; row++) {
      if (b->arr[row]) {
         // int size=pow_self(row);
         // for(int actual=0;actual<size;actual++){
         //    if(b->arr[row][actual].created==1){
         //       b->arr[row][actual].value=0;
         //    }
         free(b->arr[row]);
         }
      }
   free(b);
   b = NULL;
   return true;
   }

void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc){
   for(int row=0;row<BSA_ROWS;row++){
      if(b->arr[row] != NULL){
      int size=pow_self(row);
      for(int actual=0;actual<size;actual++){
           if(b->arr[row][actual].created==1){
              func(&b->arr[row][actual].value,acc);
           }
      }
      }
  }
}

int find_row(int indx){
  int sum=0;
  int exponent=0;
  while(sum<=indx){
    sum+=pow_self(exponent);
    exponent++;
  }
    if(sum==indx){
      return exponent;
    }else{
      exponent--;
      return exponent;
  }
}

//given an indx, find the indx_first
int find_indx_first(int indx){
  int sum=0;
  int exponent=0;
  if(indx==0){
      return indx;
  }
  while(sum<=indx){
      sum+=pow_self(exponent);
      exponent++;
  }
  exponent=exponent-2;
  sum=0;
  while(exponent>0){
      sum+=pow_self(exponent);
      exponent--;
  }
  sum++;
  return sum;
}

//doing the pow thing.
int pow_self(int exponent){
  int result=1;
  while(exponent!=0){
      result*=2;
      exponent--;
  }
  return result;
}


int max(int a,int b){
  if (a>b){
      return a;
  }else{
      return b;
  }
}

int log2_int(int n) {
  int result = 0;
  while (n > 1) {
      n /= 2;
      result++;
  }
  return result;
}
//find the biggest index number given a row.
int find_row_last(int row){
  int sum=0;
  for(int i=0;i<=row;i++){
      sum+=pow_self(i);
  }
  sum=sum-1;
  return sum;
}

void test(void){
  int exponent=6;
  assert(pow_self(exponent)==64);
  exponent=10;
  assert(pow_self(exponent)==1024);
  //OK test find_row.
  int indx=15;
  assert(find_row(indx)==4);
  indx=5;
  assert(find_row(indx)==2);
  indx=0;
  assert(find_row(indx)==0);
  //test find_indx_first.
  indx=11;
  assert(find_indx_first(indx)==7);
  indx=5;
  assert(find_indx_first(indx)==3);
  //test find_row_last.
  int row=3;
  assert(find_row_last(row)==14);
  row=0;
  assert(find_row_last(row)==0);

  bsa* b = bsa_init();
  assert(bsa_set(b, 15, 15));
  assert(bsa_set(b, 0, 4));
bsa_free(b);
}
