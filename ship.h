#ifndef RANDOM_SHIP_H
#define RANDOM_SHIP_H
#include "bitmap.h"
#include "list.h"

typedef enum {SOLO, TRIAL, SMALL_QUAD, BIGGEST_QUAD, L_GUY, T_GUY, S_GUY} ShipKind;
typedef enum {false, true} bool;

typedef struct ship_ SHIP;

struct ship_ {

    ShipKind kind;

    BitMap *bp;

    int columns, rows;

    int shotCount;
};

SHIP *newShip(ShipKind kind);
void *shipToOne(SHIP *sh);
SHIP *getShipSize(SHIP *sh);
BitMap *getBitMapShip(SHIP *sh);
ShipKind getShipKind(SHIP *sh);
void setShotCount(SHIP *sh, int value);
int getColumnsRows(SHIP *sh, char c);
int getShotCount(SHIP *sh);
int numCells(SHIP *sh);
bool translation(SHIP *sh, int sizeVertical, int sizeHorizontal);
void rotation(SHIP *sh, int degrees);
void delete_ship(SHIP *sh);
SHIP *createShips(int sizeMatrix);
List *activatePoints(SHIP *sh);
char *nameShip(SHIP *sh);
bool sinkBoat(SHIP *sh);
void freeShip(SHIP *sh);

#endif //RANDOM_SHIP_H
