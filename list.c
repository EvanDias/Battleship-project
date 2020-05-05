#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Create a node
ListNode *initNode(SHIP *ship, ListNode* next) {

    ListNode* newNode = malloc(sizeof(ListNode));

        newNode -> ship = ship;
        newNode -> next = next;

    return newNode;
}


// Init a list
List *initList() {
    List* newList = malloc(sizeof(List));

    newList -> head = NULL;

    newList -> size = 0;

    return newList;
}


// Add node at the head of the list
void *headList(List* list, SHIP *elem) {

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

    return NULL;
}


// Remove a specific node from the list
List *removeNode(List *list, SHIP *node) {

    ListNode *current = list -> head;

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


// Free allocated memory
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
