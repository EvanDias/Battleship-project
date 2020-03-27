#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"


//init a matrix with its size and fill with '.'
Matrix* initMatrix(int size) {

    Matrix* matrix = malloc(sizeof(Matrix));
    matrix -> size = size;

    char** data = malloc(sizeof(char*) * size);


   for(int i = 0; i < size; i++)
        data[i] = malloc(size * sizeof(char));

    for(int i = 0; i < size; i++) {
       for(int j = 0; j< size; j++) {
            data[i][j] = '.';

        }
    }

    matrix -> data = data;

    return matrix;
}


//insert a ship in matrix, that's, when put a point of ship, this point in matrix is replace for 'x'
Matrix *insertShipInMatrix(Matrix *a, SHIP *ship) {

    ListNode *current =  ship -> list -> head;

   while(current != NULL) {
        a -> data[current -> data -> y][current -> data -> x] = 'x';

        current = current -> next;
    }

    return a;
}


//loojup a point of matrix, and if this point is a ship's point, it say acertou or errou  - working in progress 
void *lookupInMatrix(Matrix *a, Point *point) {


    if(a -> data[point -> y][point -> x] == 'x') {
        a -> data[point -> y][point -> x] = '-';
        printf("acertou num barco \n");


    }

    else printf("errou \n ");

}


//function to print a matrix
void printMatrix(Matrix *x) {
    printf("   A ");
    char ch = 'B';
    for(char j = 1; j < (x -> size); j++) {
        printf("%c ", ch);
        ch++;
    }
    printf("\n");

    char aux = 'A';

    for(int i = 0; i < x -> size; i++) {
       printf("%c  ", aux);

       for(int j = 0; j< x -> size; j++) {
       printf("%c ", x -> data[i][j]);
    }
        printf("\n");
        aux++;
    }

}






/*

int main() {

    Matrix* x = initMatrix(5);

    Point *a = newPoint(2,3);
    Point *b = newPoint(2,4);
    Point *c = newPoint(2,3);
    Point *d = newPoint(2,1);

    List *l = initList();


    List *boas = headList(l, a);
    List *boas2 = headList(l, b);


    SHIP *sh = new_ship(SOLO,l);

    insertShipInMatrix(x, sh);

    lookupInMatrix(x,c);
    lookupInMatrix(x,d);


    for(int i = 0; i < 5; i++) {
       for(int j = 0; j< 5; j++) {
       printf("%c ", x -> data[i][j]);

    }
        printf("\n");
    }

}

*/
