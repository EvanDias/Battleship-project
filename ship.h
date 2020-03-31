#ifndef RANDOM_SHIP_H
#define RANDOM_SHIP_H
#include "bitmap.h"


typedef enum {SOLO, TRIAL, SMALL_QUAD, BIGGEST_QUAD, L_GUY} ShipKind;

typedef struct ship_ SHIP;

struct ship_ {

    ShipKind kind;

    BitMap *bp;

    int columns, rows;

    int direction; // VER DEPOIS

    int shotCount;

};


SHIP *newShip(ShipKind kind);
void *shipToOne(SHIP *sh);
SHIP *getShipSize(SHIP *sh);
int numCells(SHIP *sh);
void delete_ship(SHIP *sh);

#endif //RANDOM_SHIP_H

