#ifndef RANDOM_BITMAP_H
#define RANDOM_BITMAP_H
#include <stdio.h>
#include <stdlib.h>
#include "point.h"

#define sizeBitMap 5

typedef struct bitmap_ BitMap;

struct bitmap_ {

    int columns;
    int row;
    unsigned char** data;
    int refx; 
    int refy;
};

BitMap *initBitMap();
BitMap *getBitMap(BitMap *bp);
unsigned char getCellBitMap(BitMap *bp, int x, int y);
int getXandY(BitMap *bp, char ch);
void setXAndY(BitMap *bp, int ref, char c);
void printBitMap(BitMap *x);
void allZero(BitMap *bp, unsigned char ternaryValue);
void copyBitMaps(BitMap *bp1, BitMap *bp2);
void changeCellValue(BitMap *bp, int x, int y, unsigned char ternaryValue);
void freeBitMap(BitMap *bp);

#endif //RANDOM_BITMAP_H