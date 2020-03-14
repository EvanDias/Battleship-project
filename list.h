#include <stdio.h> 
#include <stdlib.h>
#include "point.h"

typedef struct listNode_ ListNode;
typedef struct list_ List;

struct listNode_ {

    void *data;
    ListNode *next;

};

struct list_ {

    int size; 
    ListNode* head;

};


ListNode *initNode(void* data, ListNode* next);
List *initList();
void *headList(List *list, void *elem);
List *removeNode(List *list, void *node);
void printList(List *l);
void deleteList(List* list);

