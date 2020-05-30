#include "ship.h"
#pragma once
typedef struct cell_ Cell;


struct cell_ {

        SHIP *ship;
        unsigned char shot;
        unsigned char value;
};


Cell* initCell();
unsigned char CellValue(Cell *cell);
unsigned char CellShot(Cell *cell);
SHIP *getShipCell(Cell *cell);
void modifyCellValue(Cell *cell, unsigned char ch);
void modifyCellShot(Cell *cell, unsigned char ch);
void changeValueShotBp(Cell *cell, int x, int y, unsigned char ternaryValue);
void modifyValues(Cell *cell, int x, int y);
void modifyShot(Cell *cell, bool b);
bool hittedPiece(Cell *cell, int x, int y);
void freeCell(Cell *cell);
void insertedShipCell(Cell *cell, SHIP *sh);


