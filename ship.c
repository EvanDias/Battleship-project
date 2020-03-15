#include <stdio.h>
#include "ship.h"

SHIP *new_ship(ShipKind kind, List *list) {

    SHIP *ship = malloc(sizeof(SHIP));

    ship -> kind = kind;

    ship -> list = list;

    return ship;
}


void delete_ship(SHIP *sh) {

    free(sh -> list);

    free(sh);
}












