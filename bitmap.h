#ifndef RANDOM_BITMAP_H
#define RANDOM_BITMAP_H
#include <stdio.h>
#include <stdlib.h>
#include "point.h"

#define sizeBitMap 5
#define BP(B) (B)
#define BPX(B) (B -> x)
#define BPY(B) (B -> Y)
#define SETBPX(B,x) (B -> x = x)
#define SETBPY(B,y) (B -> y = y)
#define CELLBP(B,x,y) (B -> data[x][y])
#define SETCELLBP(B,x,y,v) (B -> data[x][y] = v)

typedef struct bitmap_ BitMap;

struct bitmap_ {

    int columns;
    int row;
    unsigned char** data;
    int refx; 
    int refy;
};

BitMap *initBitMap();
void printBitMap(BitMap *x);
void freeBitMap(BitMap *bp);

#endif //RANDOM_BITMAP_H