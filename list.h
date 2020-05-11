#ifndef RANDOM_LIST_H
#define RANDOM_LIST_H
#include <stdio.h>
#include <stdlib.h>
//#include "ship.h"

typedef struct listNode_ ListNode;
typedef struct list_ List;


//struct to create a list's node. Node save a point and a next node
struct listNode_ {

    void *data;
    ListNode *next;

};

//struct to create a list. List have a size and reference to head node
struct list_ {

    int size;
    ListNode* head;

};


ListNode *initNode(void* data, ListNode* next);
List *initList();
void headList(List *list, void *data);
List *removeNode(List *list, void *data);
//void printList(List *l);
void deleteList(List* list);

#endif //RANDOM_LIST_H
