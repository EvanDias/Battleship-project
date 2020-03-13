#include <stdio.h>
#include <stdlib.h>
#include "list.h"

ListNode *initNode(void* data, ListNode* next) {

    ListNode* newNode = malloc(sizeof(ListNode));

        newNode -> data = data; 
        newNode -> next = next;
    
    return newNode;

}

List *initList() {

    List* newList = malloc(sizeof(List));

    newList -> head = NULL;

    newList -> size = 0;

    return newList;
}


List *headList(List* list, void* elem) {

    ListNode* newNode = malloc(sizeof(ListNode));
    
    newNode -> data = elem;

    if(list -> head == NULL) {  //list is empty
        list -> head = newNode;
        newNode -> next = NULL;
    }

    else if(list -> head != NULL) {

        newNode -> next = list -> head;
        list -> head = newNode;
    }

    list -> size++;

    return list;
}

void deleteList(List* list) {

    free(list);

}


