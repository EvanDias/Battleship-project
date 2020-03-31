#ifndef RANDOM_SHIP_H
#define RANDOM_SHIP_H
#include "point.h"
#include "bitmap.h"


typedef enum {SOLO, TRIAL, SMALL_QUAD, BIGGEST_QUAD, L_GUY} ShipKind;

typedef struct ship_ SHIP;

struct ship_ {

    ShipKind kind;

    BitMap *bp;

    int columns, rows;

};


SHIP *newShip(ShipKind kind, BitMap *bp);
SHIP *getShipSize(SHIP *sh)
void delete_ship(SHIP *sh);

#endif //RANDOM_SHIP_H

