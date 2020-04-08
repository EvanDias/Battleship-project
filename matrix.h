#include <stdio.h>
#include "list.h"

typedef struct matrix_ Matrix;
typedef struct cell_ Cell;
typedef struct Cell** pCell;

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
    pCell* data;
};


Cell* initCell();
Matrix *initMatrix(int size);
//Matrix *insertShipInMatrix(Matrix *a, SHIP *ship);
Matrix *changeValueOfMatrix(Matrix *a, int x, int y);