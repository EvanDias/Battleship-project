#ifndef RANDOM_MATRIX_H
#define RANDOM_MATRIX_H
#include "list.h"

typedef struct matrix_ Matrix;
typedef struct cell_ Cell;

struct cell_ {

        SHIP *ship;
        unsigned char shot;
        unsigned char value;
};


// Struct to create a matrix with its size and data
struct matrix_
{
    int size;
    Cell*** data;
};


Cell* initCell();
Matrix *initMatrix(int size);
bool insertShipInMatrix(Matrix *a, SHIP *ship, int x, int y);
void changeValueShotBp(Matrix *matrix, int x, int y, unsigned char ternaryValue);
void deleteShipMatrix(Matrix *ma, SHIP *sh, int x, int y);
void printMatrix(Matrix *matrix);
void printBothMatrix(Matrix *start, Matrix *other);
bool canInsert(Matrix *matrix, SHIP *ship, int x, int y);
void letters(int size);
int choiceChar(char c);
int charToIntUpper(char chInput);
int charToIntLower(char chInput);
void freeMatrix(Matrix *matrix);
void freeCell(Cell *cell);

#endif //RANDOM_MATRIX_H