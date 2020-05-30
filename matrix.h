#ifndef RANDOM_MATRIX_H
#define RANDOM_MATRIX_H
#include "cell.h"

typedef struct matrix_ Matrix;


// Struct to create a matrix with its size and data
struct matrix_
{
    int size;
    void ***data;
};


Matrix *initMatrix(int size);
int getMatrixSize(Matrix *matrix); 
void insertInMatrix(Matrix *a, void *ship, int x, int y);
void *searchInMatrix(Matrix *matrix, int x, int y);
void deleteShipMatrix(Matrix *ma, int x, int y, int numberPoints);
bool sinkBoatMatrix(Matrix *x);
void freeMatrix(Matrix *matrix);

#endif //RANDOM_MATRIX_H