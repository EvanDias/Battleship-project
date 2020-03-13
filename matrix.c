#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "point.h"



Matrix* initMatrix(int size) {

    Matrix* matrix = malloc(sizeof(Matrix));
    matrix -> size = size; 

    char** data = malloc(sizeof(char*) * size);

   
   for(int i = 0; i < size; i++) 
        data[i] = malloc(size * sizeof(char));
    
    for(int i = 0; i < size; i++) {
       for(int j = 0; j< size; j++) { 
            data[i][j] = '0';

        }
    }

    matrix -> data = data; 
    
    return matrix;
}


Matrix *insertShipInMatrix(Matrix *a, SHIP *ship) {

    ListNode *current =  ship -> list -> head;

   while(current != NULL) {
        a -> data[current -> data -> y][current -> data -> x] = 'x';

        current = current -> next;
    }

    return a;
}



int main() {

    Matrix* x = initMatrix(5);

    Point *a = newPoint(2,3);
    Point *b = newPoint(2,4);

    List *l = initList();


    List *boas = headList(l, a);
    List *boas2 = headList(l, b);


    SHIP *sh = new_ship(SOLO,l);

    insertionMatrix(x, sh);


    for(int i = 0; i < 5; i++) {
       for(int j = 0; j< 5; j++) { 
       printf("%c ", x -> data[i][j]);

    }
        printf("\n");
    }

}