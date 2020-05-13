#ifndef RANDOM_MATRIX_H
#define RANDOM_MATRIX_H
#include "ship.h"
#include "list.h"
#include "ship.h"

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
unsigned char CellValue(Matrix *m, int x, int y);
unsigned char CellShot(Matrix *m, int x, int y);
void modifyCellValue(Matrix *m, int x, int y, unsigned char ch);
void modifyCellShot(Matrix *m, int x, int y, unsigned char ch);
bool insertShipInMatrix(Matrix *a, SHIP *ship, int x, int y);
void changeValueShotBp(Matrix *matrix, int x, int y, unsigned char ternaryValue);
void deleteShipMatrix(Matrix *ma, SHIP *sh, int x, int y);
bool sinkBoatMatrix(Matrix *x);
void printMatrix(Matrix *matrix);
void printBothMatrix(Matrix *start, Matrix *other);
bool canInsert(Matrix *matrix, SHIP *ship, int x, int y);
void letters(int size);
int choiceChar(char c);
int charToIntUpper(char chInput);
int charToIntLower(char chInput);
bool canShot(Matrix *matrix, int x, int y);
bool modifyValues(Matrix *other, int x, int y);
void modifyShot(Matrix *m, int x, int y, bool b);
void freeMatrix(Matrix *matrix);
void freeCell(Cell *cell);

#endif //RANDOM_MATRIX_H