#include "bitmap.h"
#include "list.h"

typedef enum {SOLO, TRIAL, SMALL_QUAD, BIGGEST_QUAD, L_GUY, T_GUY, S_GUY} ShipKind;
typedef enum {false, true} bool;

typedef struct ship_ SHIP;

#define SHIP(S) (S)
#define SHIPKIND(S) (S -> kind)
#define SHIPCOLUMNS(S) (S -> columns)
#define SETSHIPCOLUMNS(S,c) (S -> columns = c)
#define SHIPROWS(S) (S -> rows)
#define SETSHIPROWS(S,r) (S -> rows = r)
#define SHIPBITMAP(S) (S -> bp)
#define SHIPSHOTCOUNT(S) (S -> shotCount)
#define SETSHIPSHOTCOUNT(S,v) (S -> shotCount, v)


struct ship_ {

    ShipKind kind;

    BitMap *bp;

    int columns, rows;

    int shotCount;
};

SHIP *newShip(ShipKind kind);
bool translation(SHIP *sh, int sizeVertical, int sizeHorizontal);
void rotation(SHIP *sh, int degrees);
char *nameShip(SHIP *sh);
bool sinkBoat(SHIP *sh);
void freeShip(SHIP *sh);
