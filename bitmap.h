#include <stdio.h>
#include <stdlib.h>
#include "point.h"

typedef struct bitmap_ BitMap;


struct bitmap_ {

    int columns;
    int row;

    unsigned char** data;


};

BitMap *initBitMap(int columns, int row);
void printBItMap(BitMap *x);
BitMap *changeCellValue(BitMap *bp, Point *point, unsigned char ternaryValue);






