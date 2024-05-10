#include "../bsa.h"
//each 
int find_row(int indx);
//doing the pow thing.
int pow_self(int exponent);
//given an index,find the first number in the row of the index?
int find_indx_first(int indx);
int find_row_last(int row);
int max(int a,int b);
// You'll this to test the other functions you write
typedef struct Node{
  //Which row is the array.0~29
  int value;
  //check if the array is created or not
  int created;
}Node;

struct bsa{
  //create an array of the bsarry type of pointers
  Node* arr[BSA_ROWS];
};


