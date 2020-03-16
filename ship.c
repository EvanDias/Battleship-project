#include <stdio.h>
#include "ship.h"

SHIP *new_ship(ShipKind kind, List *list) {

    SHIP *ship = malloc(sizeof(SHIP));

    ship -> kind = kind;

    ship -> list = list;

    switch(ship -> kind) {

        case SOLO: ship -> size = 1;
        break;       
        case DUAL: ship -> size = 2;
         break;    
        case TRIAL: ship -> size = 3;
         break;    
        case QUAD: ship -> size = 4; 
         break;    
        case T_GUY: ship -> size = 5;
         break;    

    }

    return ship;
}


int sizeShip(SHIP *ship) {
    
    return ship -> size;

}


void delete_ship(SHIP *sh) {

    free(sh -> list);

    free(sh);
}












