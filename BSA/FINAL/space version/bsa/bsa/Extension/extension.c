#include "specific.h"
//Create a new Node.
Node* createNode(int data,int indx) {
   Node* newNode=(Node*)calloc(1,sizeof(Node));
   newNode->data=data;
   newNode->indx=indx;
   newNode->next=NULL;
   return newNode;
}

bsa* bsa_init(void){
   bsa* b=(bsa*)calloc(1,sizeof(bsa));
   b->head=NULL;
   return b;
}

bool bsa_set(bsa* b, int indx, int data){
   if(b==NULL) {
      return false; 
    }
  //Check if there are Node with indx right now.
   int flag=0;
   Node* current = b->head;
   //If the b hasen't been assigned yet.
   if(current==NULL){
      Node* newNode=createNode(data,indx);
      b->head=newNode;
      return true;
   }
   //If there are already one
   while(current!=NULL){
      if(current->indx==indx){
           current->data=data;
           flag=1;
      }
      current = current->next;
   }
   //If there is no the indx given.
   if(flag==0){
      return bsa_set_flag(b,indx,data);
   }
   free(current);
   return true;
}
//while flag=0, do these things.
bool bsa_set_flag(bsa* b, int indx, int data){
   Node* current=b->head;
   current=b->head;
      if(current==NULL){
           Node* newNode=createNode(data, indx);
           current=newNode;
           return true;
      }else{
      int current_index=b->head->indx;
      //create a dummy Node to store the slow Node in a linked list
      Node* dummy=createNode(-1,-1);
      dummy->next=b->head;
      Node* slow=dummy;
      Node* newNode=createNode(data, indx);
      while(current!=NULL && current_index<=indx){            
           current_index=current->indx;
           current=current->next;
           slow=slow->next;
      }
      newNode->next=current;
      slow->next=newNode;
      free(current);
      free(dummy);
      }
      return true;
}

int* bsa_get(bsa* b, int indx){
   Node* current=b->head;
   while(current!=NULL){
      if(current->indx==indx){
          return &current->data;
        }
           current=current->next;
   }
   return NULL;
}

bool bsa_delete(bsa* b, int indx) {
   if (b==NULL || b->head==NULL) {
      return false; 
   }
   Node* current=b->head;
   Node* prev=NULL;
   // If the head node itself holds the data to be deleted
   if (current!= NULL && current->indx==indx) {
      b->head=current->next; 
       free(current); 
       return true;
   }
   // Search for the node to be deleted
   while(current!=NULL&&current->indx!=indx) {
      prev = current;
      current =current->next;
   }
   // If node with indx wasn't found
   if (current==NULL) {
      return false;
   }
   prev->next=current->next;
   free(current);
   return true;
}

int bsa_maxindex(bsa* b){
   if(b==NULL){
      return -1;
   }
   Node* current=b->head;
   if(current==NULL){
      return -1;
   }
   Node* dummy=createNode(-1,-1);
   dummy->next=b->head;
   Node* slow=dummy;
   while(current!=NULL){
      current=current->next;
         slow=slow->next;
   }
   free(dummy);
   return slow->indx;
}

bool bsa_free(bsa* b){
   Node* current=b->head;
   while (current!=NULL) {
      Node* temp=current; // Store the current node
      current=current->next; // Move to the next node
      free(temp); // Free the memory of the stored node
   }
   free(current);
   free(b);
   b=NULL;
   return true;
}

void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc){
   Node* current=b->head;
   while(current!=NULL){
      func(&current->data,acc);
      current=current->next;
   }
}


void test(void){
   assert(bsa_maxindex(NULL)==-1);
   bsa* b = bsa_init();
   assert(b);
   assert(bsa_maxindex(b)==-1);
   assert(bsa_set(b, 0, 4));
   assert(bsa_maxindex(b)==0);
   // Reset existing value
   assert(bsa_set(b, 0, 0));
   assert(bsa_delete(b,0));
   assert(bsa_set(b, 15, 15));
   assert(bsa_delete(b,15));
   free(b);
   b = bsa_init();
   bsa_set(b, 1, 1);
   bsa_set(b, 2, 2);
   bsa_set(b, 3, 3);
   int acc = 1;
   bsa_foreach(times, b, &acc);
   assert(acc==6);
   bsa_free(b);
}
