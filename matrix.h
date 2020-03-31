#include <stdio.h>
#include "ship.h"
#include "bitmap.h"

typedef struct matrix_ Matrix;
typedef struct cell_ Cell;


struct cell_ {
    union {
      struct {
        unsigned char shot;
        unsigned char value;

      }empty;

      struct {
        BitMap *bp;
        unsigned char shot;
        unsigned char value;
      }notEmpty;
    }union1;
};



//struct to create a matrix with its size and data
struct matrix_
{
    int size;
    Cell** data;
};


Cell* initCell();
Matrix *initMatrix(int size);
Matrix *insertShipInMatrix(Matrix *a, SHIP *ship);
void printMatrix(Matrix *m);
