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


void *headList(List* list, void* elem) {

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

   
}

List *removeNode(List *list, void *node) {

    ListNode *current = list -> head;
    //printf("current: %d \n", current -> data);

    ListNode *temp = malloc(sizeof(ListNode));

    if(current -> data == node) {

        current -> data = current -> next -> data; 
        current -> next = current -> next -> next;
        list -> size--;

    }


    while(current != NULL) {

       // printf("current: %d \n", current -> data);

        if(current -> next == NULL && current -> data == node) {

            temp -> next = NULL;
            current  -> data = NULL;
            list -> size--;

        }
        
        else if(current -> next != NULL && current -> data == node) {

            temp -> next = current -> next;
            list -> size --;

        }

        temp = current;
        //printf("temp antes de avançar: %c \n", temp -> data);
        current = current -> next;
        //if(current != NULL) printf("current-> next: %c \n", current -> data);
    }


    return list;
}



/*

List *removeNode(List *list, void *node) {

    List *newList = initList();

    ListNode* current = list -> head;

    while(current != NULL) {
     if(current -> data != node) headList(newList,current -> data);
        current = current -> next;
    }

    return newList;

}

*/
 
void deleteList(List* list) {

    free(list);

}


/*
void printList(List *list) {

    ListNode *node = list -> head; 

    while( node != NULL) {
        printf("%d ", node -> data);
        node = node -> next;
    }
    printf("\n");
}


int main() {

   
    List *list = initList();
    headList(list,2);
    headList(list,5);
    headList(list,7);
    headList(list,0);
    headList(list,9);
    headList(list,8);

    printf("Lista: ");
    printList(list);

    list = removeNode(list,8);

    printf("Nova Lista: ");
    printf("TAMANHO: %d \n", list -> size);
    printList(list);
    
}

*/


