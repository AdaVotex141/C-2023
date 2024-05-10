#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#define LISTSTRLEN 1000
#define BSA_ROWS 30

typedef struct Node {
    int data;
    int created;
    int indx;
    struct Node* next;
} Node;

typedef struct bsa{
    struct Node* head;
} bsa;


bool bsa_set_flag(bsa* b, int indx, int data);

void test(void);
