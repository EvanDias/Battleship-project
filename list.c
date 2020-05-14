#include <stdio.h>
#include <stdlib.h>
#include "list.h"


//create a node
ListNode *initNode(void *data, ListNode* next) {

    ListNode* newNode = malloc(sizeof(ListNode));

        newNode -> data = data;
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
void headList(List* list, void *elem) {

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

/*
//remove a specific node of list
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

        current = current -> next;

    }


    return list;
}
*/

void removeNode(List *list, void *node)
{
    ListNode *current = list -> head;
    ListNode *temp = current;
    ListNode *prev = NULL;

    // If head node itself holds the key to be deleted
    if (temp != NULL && temp->data == node)
    {
        current = temp->next;   // Changed head
        free(temp);               // free old head
        return;
    }

    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (temp != NULL && temp->data != node)
    {
        prev = temp;
        temp = temp->next;
    }

    // If key was not present in linked list
    if (temp == NULL) return;

    // Unlink the node from linked list
    prev->next = temp->next;

    free(temp);  // Free memory
}



//delete a list
// Free allocated memory
void freeList(List* list) {

    ListNode *node = list -> head;
    ListNode *aux = NULL;

    while(node != NULL) {
        aux = node -> next;
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
void printList(List *list) {

    if(list -> size = 0) printf("List is empty \n");

    else {
    ListNode *node = list -> head;

    while( node != NULL) {
        printf("Olá\n");
        node = node -> next;
    }
    printf("\n");
    }
  }

  */
