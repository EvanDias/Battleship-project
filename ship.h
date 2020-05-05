#ifndef RANDOM_SHIP_H
#define RANDOM_SHIP_H
#include "bitmap.h"

typedef enum {SOLO, TRIAL, SMALL_QUAD, BIGGEST_QUAD, L_GUY, T_GUY, S_GUY} ShipKind;
typedef enum {false, true} bool;

typedef struct ship_ SHIP;

struct ship_ {

    ShipKind kind;

    BitMap *bp;

    int columns, rows;

    int rotation;

    int translationx;

    int translationy;

    int shotCount;
};

SHIP *newShip(ShipKind kind);
void *shipToOne(SHIP *sh);
SHIP *getShipSize(SHIP *sh);
int numCells(SHIP *sh);
bool translation(SHIP *sh, int sizeVertical, int sizeHorizontal);
void rotation(SHIP *sh, int degrees);
void delete_ship(SHIP *sh);
SHIP *createShips(int sizeMatrix);
char *nameShip(SHIP *sh);
void freeShip(SHIP *sh);

#endif //RANDOM_SHIP_H
