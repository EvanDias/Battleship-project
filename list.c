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



/*

List *removeNode(List *list, void *node) {

    printf("tamanho da fila inicial: %d \n", list -> size);

   // ListNode *newNode = malloc(sizeof(ListNode));

    //newNode -> data = node; 

    if(list == NULL) printf("Não há lista");

    ListNode *current = list -> head;
    ListNode *temp = NULL;

    while (list != NULL) {

        printf("current: %d \n",current -> data);

        if(current -> next == NULL && current -> data == node) 
            {
                current = NULL;
                list -> size--;
            }

        else if(current -> next != NULL && current -> data == node) {

               temp = current -> next; 
               printf("temp: %d \n", temp -> data);
               current  = temp; 
               printf("curr: %d \n", current -> data);
               list -> size--; 
               printf("size1 : %d \n", list -> size);
                 

        }

       /* else if(current -> next != NULL && current -> next -> data == node) {

            temp = current -> next; 
            current = temp -> next; 
            list -> size--;
            printf("size2 : %d \n", list -> size);

            free(temp);


        }
     

        printf("current: antes o while %d \n",current -> data);
 

        current = current -> next;


    }
    
    free(temp);
    printf("tamanho da lista: %d \n", list -> size);
    return list;
      

}*/

List *removeNode(List *list, void *node) {

    List *newList = initList();

    ListNode* current = list -> head;

    while(current != NULL) {
     if(current -> data != node) headList(newList,current -> data);
        current = current -> next;
    }

    return newList;

} 
void deleteList(List* list) {

    free(list);

}

void printList(List *list) {

    ListNode *node = list -> head; 

    while( node != NULL) {
        printf("%d -> ", node -> data);
        node = node -> next;
    }
    printf("\n");
}

int main() {

   
    List *list = initList();
    headList(list,1);
    headList(list,2);
    headList(list,3);
    headList(list,12);

    printf("Lista: ");
    printList(list);



    list = removeNode(list,12);

    printf("Nova Lista: ");
    printf("TAMANHO: %d \n", list -> size);
    printList(list);

    
}





