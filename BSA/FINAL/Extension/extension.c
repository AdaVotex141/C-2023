#include "specific.h"
//Create a new Node.
Node* createNode(int data,int indx) {
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->data=data;
    newNode->indx=indx;
    newNode->next=NULL;
    return newNode;
}

bsa* bsa_init(void){
    bsa* b=(bsa*)malloc(sizeof(bsa));
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
    return false;
}
//while flag=0, do these things.
bool bsa_set_flag(bsa* b, int indx, int data){
    Node* current = b->head;
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
        free(dummy);
        }
        return true;
}

int* bsa_get(bsa* b, int indx){
    Node* current = b->head;
    while(current!=NULL){
        if(current->indx==indx){
            return &current->data;
        }
        current=current->next;
    }
    return NULL;
}

// bool bsa_delete(bsa* b, int indx){
//     Node* dummy=createNode(-1,-1);
//     //There are situations!!!!!!!!
//     dummy->next=b->head;
//     Node* slow=dummy;
//     Node* fast=b->head->next;
//     Node* current=b->head;
//     int current_index=current->indx;
//     while(current!=NULL || current_index!=indx){
//         current_index=current->indx;
//         fast=current->next->next;
//         current=current->next;
//         slow=slow->next;
//     }
//     slow->next=fast;
//     free(current);
//     free(dummy);
//     return true;
// }

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
    //WHY????no &??????
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
    free(b);
    b=NULL;
    return true;
}

// void bsa_foreach(void (*func)(int* p, int* n), bsa* b, int* acc){
//     Node* current=b->head;
//     while(current!=NULL){
//         func(&current->data,acc);
//         current=current->next;
//     }
// }

void test(void){
    assert(bsa_maxindex(NULL)==-1);
    bsa* b = bsa_init();
    assert(b);
   assert(bsa_maxindex(b)==-1);
      assert(bsa_set(b, 0, 4));
   assert(bsa_maxindex(b)==0);
      assert(bsa_set(b, 0, 0));
   assert(bsa_set(b, 15, 15));
   int* p = bsa_get(b, 0);
   assert(p);
   assert(*p == 0);
   p = bsa_get(b, 15);
   assert(p);
   assert(*p == 15);

}
