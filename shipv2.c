#include <stdio.h>
#include "shipv2.h"


SHIP *newShip(ShipKind kind, BitMap *bp) {

    SHIP *ship = malloc(sizeof(SHIP));

    ship -> kind = kind;

    ship = getShipSize(sh);

    BitMap *bp = initBitMap(ship -> columns, ship -> rows);

    ship -> bp = bp;

    return ship;

}



// Get the size required to init the BitMap
SHIP *getShipSize(SHIP *sh) {

    int columns, rows;

    if(sh -> kind == SOLO) {
        columns = 1;
        rows = 1;
    } else if(sh -> kind == TRIAL) {
        columns = 3;
        rows = 1;
    } else if(sh -> kind == SMALL_QUAD) {
        columns = 2;
        rows = 2;
    } else if(sh -> kind == BIGGEST_QUAD) {
        columns = 4;
        rows = 4;
    } else if(sh -> kind == L_GUY) {
        columns = 5;
        rows = 5;
    }

    sh -> columns = columns;
    sh -> rows = rows;

    return sh;
}



void delete_ship(SHIP *sh) {

    free(sh -> bp);

    free(sh);
}



