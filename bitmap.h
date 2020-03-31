#include <stdio.h>
#include <stdlib.h>

typedef struct bitmap_ BitMap;

struct bitmap_ {

    int columns;
    int row;

    unsigned char** data;


};

BitMap *initBitMap(int columns, int row);
void printBitMap(BitMap *x);
BitMap *changeCellValue(BitMap *bp, int x, int y, unsigned char ternaryValue);






