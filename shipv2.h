#ifndef RANDOM_SHIP_H
#define RANDOM_SHIP_H
#include "point.h"
#include "bitmap.h"


typedef enum {SOLO, DUAL, TRIAL, QUAD, T_GUY} ShipKind;

typedef struct ship_ SHIP;

struct ship_ {

    ShipKind kind;

    BitMap *bp;

};


SHIP *newShip(ShipKind kind, BitMap *bp);
//void delete_ship(SHIP *sh);

#endif //RANDOM_SHIP_H

