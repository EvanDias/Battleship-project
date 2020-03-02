#include <stdio.h>
#include <stdlib.h>
#include "list.h"

ListNode* initNode(void* data, ListNode* next) {

    ListNode* newNode = malloc(sizeof(ListNode));

        newNode -> data = data; 
        newNode -> next = next;
    
    return newNode;

}

List* initList() {

    List* newList = malloc(sizeof(List));

    
    return newList;

}

List* headList(List* list, void* elem) {

    ListNode* newNode = malloc(sizeof(ListNode));
    
    newNode -> data = elem; 

    if(list -> head == NULL) {  //list is empty

        list -> head = newNode; 
        newNode -> next = NULL;

    }

    if(list -> head != NULL) {

        newNode -> next = list -> head; 
        list -> head = newNode;        

    }

    return list;        


}

void deleteList(List* list) {

    free(list);

}


