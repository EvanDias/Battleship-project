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

int getSizeList(List *list) {

    return list -> size;
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

//remove a specific node of list
void removeNode(List *list, void *node) {
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
            list -> size--;
        }
        temp = current;
        current = current -> next;
    }
}

/*

List *concatenateList(List *l1, List *l2) {

    ListNode *node = NULL; 

    if(l1 -> size == 0) {
        return l2;
    }

    if(l2 -> size == 0) {
    
        return l1; 
    }

    node = l1 -> head; 

    while(node -> next != NULL) {
        node = node -> next;
        node -> next = l2 -> head;
    }

    l1 -> size = l1 -> size + l2 -> size; 

    return l1;
}

*/

List *concatenateList(List *l1, List *l2) {

    ListNode *node = l2 -> head; 

    while(node != NULL) {

        headList(l1,node -> data);
        node = node -> next;

    }

    return l1;
    
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
 void main() {


     List *list = initList(); 

     headList(list,"ola"); 
     headList(list,"adeus"); 
     headList(list,"sou");
     headList(list,"ui");

    //printList(list);

     removeNode(list, "adeus");

    //printList(list);

    List *list1 = initList(); 
    headList(list1,"pois"); 
    headList(list1, "kkk");
    headList(list1, "era");

    printf("%d\n", list -> size);


    List *concatenate = concatenateList(list, list1);

    
}

*/


 
