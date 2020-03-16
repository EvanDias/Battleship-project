#include <stdio.h> 
#include <stdlib.h>
#include "point.h"

typedef struct listNode_ ListNode;
typedef struct list_ List;

typedef enum {true, false} bool;

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
void *headList(List *list, void *elem);
List *removeNode(List *list, void *node);
bool lookUp(List *list, void *point);
//void printList(List *l);
void deleteList(List* list);

