#include <stdio.h> 
#include <stdlib.h>
#include "point.h"

typedef struct listNode_ ListNode;
typedef struct list_ List;

struct listNode_ {

    Point *data;
    ListNode *next;

};

struct list_ {

    int size; 
    ListNode* head;

};


ListNode *initNode(void* data, ListNode* next);
List *initList();
List *headList(List *list, void *elem);
void deleteList(List* list);

