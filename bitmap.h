#ifndef RANDOM_BITMAP_H
#define RANDOM_BITMAP_H
#include <stdio.h>
#include <stdlib.h>
#include "point.h"

#define sizeBitMap 5
#define BP(B) (B)
#define BPX(B) (B -> refx)
#define BPY(B) (B -> refy)
#define SETBPX(B,x) (B -> refx = x)
#define SETBPY(B,y) (B -> refy = y)
#define CELLBP(B,x,y) (B -> data[x][y])

typedef struct bitmap_ BitMap;

struct bitmap_ {

    int columns;
    int row;
    unsigned char** data;
    int refx; 
    int refy;
};

BitMap *initBitMap();
void setCellBP(BitMap *bp, int x, int y, unsigned char value);
void allZero(BitMap *bp, unsigned char ternaryValue);
void copyBitMaps(BitMap *bp1, BitMap *bp2);
void printBitMap(BitMap *x);
void freeBitMap(BitMap *bp);

#endif //RANDOM_BITMAP_H