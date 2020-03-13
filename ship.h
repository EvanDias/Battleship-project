//
// Created by evan on 06/03/20.
//

#ifndef RANDOM_SHIP_H
#define RANDOM_SHIP_H
#include "point.h"
#include "list.h"


typedef enum {SOLO, DUAL, TRIAL, QUAD, T_GUY} ShipKind;

typedef struct ship_ SHIP;

struct ship_ {

    ShipKind kind;

    List *list;

};


SHIP *new_ship(ShipKind kind, List *list);
void delete_ship(SHIP *sh);

#endif //RANDOM_SHIP_H

