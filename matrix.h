#include <stdio.h>
#include "list.h"

typedef struct matrix_ Matrix;
typedef struct cell_ Cell;
//typedef struct Cell** pCell;

struct cell_ {

        SHIP *ship;
        unsigned char shot;
        unsigned char value;
};



//struct to create a matrix with its size and data
struct matrix_
{
    int size;
    Cell*** data;
};


Cell* initCell();
Matrix *initMatrix(int size);
bool insertShipInMatrix(Matrix *a, SHIP *ship, int x, int y);
void printMatrix(Matrix *matrix);
void printEnemyMatrix(Matrix *matrix);
void printBothMatrix(Matrix *start, Matrix *other);
bool canInsert(Matrix *matrix, SHIP *ship, int x, int y);
void letters(int size);