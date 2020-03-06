#pragma once
#include <stdio.h> 
#include <stdlib.h>
#include "matrix.h"



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


int main() {

    Matrix* x = initMatrix(5);

    for(int i = 0; i < 5; i++) {
       for(int j = 0; j< 5; j++) { 
       printf("%c ", x -> data[i][j]);

    }
        printf("\n");
    }

}