#include <stdio.h>
#include <stdlib.h>
#include "list.h"


//create a node
ListNode *initNode(SHIP *ship, ListNode* next) {

    ListNode* newNode = malloc(sizeof(ListNode));

        newNode -> ship = ship;
        newNode -> next = next;

    return newNode;
}


//init a list
List *initList() {

    List* newList = malloc(sizeof(List));

    newList -> head = NULL;

    newList -> size = 0;

    return newList;
}



//add node a head list
void *headList(List* list, SHIP *elem) {

    //ListNode* newNode = malloc(sizeof(ListNode));
    ListNode* newNode = initNode(elem, NULL);

    newNode -> ship = elem;

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

//remove a specific node of list
List *removeNode(List *list, SHIP *node) {

    ListNode *current = list -> head;
    //printf("current: %d \n", current -> data);

    ListNode *temp = malloc(sizeof(ListNode));

    if(current -> ship == node) {

        current -> ship = current -> next -> ship;
        current -> next = current -> next -> next;
        list -> size--;

    }


    while(current != NULL) {

  

        if(current -> next == NULL && current -> ship == node) {

            temp -> next = NULL;
            current  -> ship = NULL;
            list -> size--;

        }

        else if(current -> next != NULL && current -> ship == node) {

            temp -> next = current -> next;
            list -> size --;

        }

        temp = current;

        current = current -> next;

    }


    return list;
}


void printList(List *list) {

    ListNode *node = list -> head;

    while( node != NULL) {
        printf("%d ", node -> ship -> kind);
        node = node -> next;
    }
    printf("\n");

}

/*
void freeList(List* list) {

    ListNode *node = list -> head;

    while(node != NULL) {
        freeNode(node);
        node = node -> next;
    }


    free(list);
}


void freeNode(ListNode *node) {
    freeShip(node -> ship);
    if(node -> next == NULL) {
        free(node);
    } else {
        free(node -> next);
    }
}*/

void freeList(List* list) {

    ListNode *node = list -> head;
    ListNode *aux;

    while(node != NULL) {
        aux = node -> next;
        freeShip(node -> ship);
        free(node);
        node = aux;
    }

    if(node == NULL) {
        free(node);
        free(aux);
    }

    free(list);
}


/*
void main() {
    List *list = initList();
    SHIP* S_SHIP = newShip(6);

    changeCellValue(S_SHIP -> bp, 0, 2, '4');
    printf("\n");
    printBitMap(S_SHIP -> bp);

    headList(list, S_SHIP);

    printBitMap(S_SHIP -> bp);

}*/