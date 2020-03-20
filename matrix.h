#include <stdio.h>
#include "ship.h"

typedef struct matrix_ Matrix;


//struct to create a matrix with its size and data
struct matrix_
{
    int size;
    char** data;

};


Matrix *initMatrix(int size);
Matrix *insertShipInMatrix(Matrix *a, SHIP *ship);
void printMatrix(Matrix *m);
