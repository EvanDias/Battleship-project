#include "ship.h"
#pragma once
typedef struct cell_ Cell;

#define SHIPCELL(C) (C -> ship)
#define SETSHIPCELL(C, s) (C -> ship = s)
#define CELLVALUE(C) (C -> value)
#define CELLSHOT(C) (C -> shot)
#define SETCELLVALUE(C, v) (C -> value = v)
#define SETCELLSHOT(C, s) (C -> shot = s)

struct cell_ {

        SHIP *ship;
        unsigned char shot;
        unsigned char value;
};


Cell* initCell();
void insertedShipCell(Cell *cell, SHIP *sh);
void changeValueShotBp(Cell *cell, int x, int y, unsigned char ternaryValue);
void modifyValues(Cell *cell, int x, int y);
void modifyShot(Cell *cell, bool b);
bool hittedPiece(Cell *cell, int x, int y);
void freeCell(Cell *cell);


