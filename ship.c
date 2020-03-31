#include <stdio.h>
#include "ship.h"


SHIP *newShip(ShipKind kind) {

    SHIP *ship = malloc(sizeof(SHIP));

    ship -> kind = kind;
    ship = getShipSize(ship); // get csolumns and rows
    ship -> shotCount = numCells(ship); // decrement remaining cells of the ship

    BitMap *bp = initBitMap(ship -> columns, ship -> rows);

    ship -> bp = bp;

    shipToOne(ship);

    return ship;

}




void *shipToOne(SHIP *sh) {
    unsigned char ternaryValue = '1';

    if(sh -> kind == SOLO) {
        changeCellValue(sh -> bp, 0, 0, ternaryValue);

    } else if(sh -> kind == SMALL_QUAD || sh -> kind == BIGGEST_QUAD) {

        for(int i=0; i < sh -> columns; i++) {
            for(int j=0; j < sh -> rows; j++) {
                sh -> bp = changeCellValue(sh -> bp, i, j, ternaryValue);
            }
        }

    } else if(sh -> kind == TRIAL)  {
        for(int i=0; i<3; i++)
            changeCellValue(sh -> bp, 0, i, ternaryValue);

    } else if(sh -> kind == L_GUY) {
        for(int i=1; i < sh -> columns; i++)
            changeCellValue(sh -> bp, 4, i, ternaryValue);

        for(int j=0; j < sh -> rows; j++)
            changeCellValue(sh -> bp, j, 0, ternaryValue);
    }

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


int numCells(SHIP *sh) {

    switch(sh -> kind) {

        case SOLO:
            return 1;
        case TRIAL:
            return 3;
        case SMALL_QUAD:
           return 4;
        case BIGGEST_QUAD:
            return 16;
        case L_GUY:
            return 9;
         default:
            return 0;
    }

}




void delete_ship(SHIP *sh) {

    free(sh -> bp);

    free(sh);
}



int main() {
    for(int i=0; i<5; i++) {
        SHIP *sh = newShip(i);
        printBitMap(sh -> bp);
        printf("\n\n");
    }


}