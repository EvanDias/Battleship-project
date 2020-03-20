#include <stdio.h>
#include <stdlib.h>
#include "point.h"

typedef struct listNode_ ListNode;
typedef struct list_ List;

typedef enum {true, false} bool;


//struct to create a list's node. Node save a point and a next node
struct listNode_ {

    Point *data;
    ListNode *next;

};

//struct to create a list. List have a size and reference to head node
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
