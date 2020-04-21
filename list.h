#include <stdio.h>
#include <stdlib.h>
#include "ship.h"

typedef struct listNode_ ListNode;
typedef struct list_ List;


//struct to create a list's node. Node save a point and a next node
struct listNode_ {

    SHIP *ship;
    ListNode *next;

};

//struct to create a list. List have a size and reference to head node
struct list_ {

    int size;
    ListNode* head;

};


ListNode *initNode(SHIP* ship, ListNode* next);
List *initList();
void *headList(List *list, SHIP *ship);
List *removeNode(List *list, SHIP *ship);
void printList(List *l);
void deleteList(List* list);
