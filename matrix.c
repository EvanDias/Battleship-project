#include "matrix.h"



// Init a matrix with its size
Matrix* initMatrix(int size) {

    printf("size: %d\n", size);
    Matrix* matrix = malloc(sizeof(Matrix));
    matrix -> size = size;

    void ***data = malloc(sizeof(void*) * size);

    for(int i = 0; i < size; i++) {
       data[i] = calloc(size,sizeof(void*));
    }
    matrix -> data = data;

    return matrix;
}



void *searchInMatrix(Matrix *matrix, int x, int y) {

    if(matrix -> data[y][x] == NULL) {
       return NULL;
    }
    else {
    
        return matrix -> data[y][x];

    }
}


void insertInMatrix(Matrix *matrix, void *info, int x, int y) {

    matrix -> data[y][x] = info;

}



void deleteShipMatrix(Matrix *ma, void *data, int x, int y) {
    
       free(ma -> data[y][x]);
       ma -> data[y][x] = NULL;
    }



// Free allocated memory
void freeMatrix(Matrix *matrix) {
     for(int i=0; i< matrix -> size; i++) {
        free(matrix -> data[i]);
     }

    free(matrix -> data);
    free(matrix);
}