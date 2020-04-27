#ifndef RANDOM_BITMAP_H
#define RANDOM_BITMAP_H
#include <stdio.h>
#include <stdlib.h>

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
void printBitMap(BitMap *x);
void changeCellValue(BitMap *bp, int x, int y, unsigned char ternaryValue);

#endif //RANDOM_BITMAP_H