#include "bitmap.h"

BitMap * initBitMap() {
    BitMap *bp = malloc(sizeof(BitMap));

    bp -> columns = sizeBitMap;
    bp -> row = sizeBitMap;

    bp -> refx = 0;
    bp -> refy = 0;

    unsigned char** data = malloc(sizeof(unsigned char*) * 1024);

    for(int i = 0; i < sizeBitMap; i++)
        data[i] = malloc(sizeBitMap * sizeof(unsigned char));

    /*for(int i = 0; i < sizeBitMap; i++)
            data[i] = malloc(sizeBitMap * sizeof(unsigned char));
    */
    for(int i = 0; i < sizeBitMap; i++) {
           for(int j = 0; j < sizeBitMap; j++) {
                data[i][j] = '0';
           }
    }

    bp -> data = data;

    return bp;
}


// Modify the ternary value contained in the BitMap
void changeCellValue(BitMap *bp, int x, int y, unsigned char ternaryValue) {

    bp -> data[x][y] = ternaryValue;

}


// Modify the ternary value contained in the BitMap
void allZero(BitMap *bp, unsigned char ternaryValue) {
    for(int i=0; i < 5; i++) {
        for(int j=0; j < 5; j++) {
            bp -> data[i][j] = ternaryValue;
        }
    }
}


// Modify the ternary value contained in the BitMap
void copyBitMaps(BitMap *bp1, BitMap *bp2) {
    for(int i=0; i < 5; i++) {
        for(int j=0; j < 5; j++) {
            bp2 -> data[i][j] = bp1 -> data[i][j];
        }
    }
}


// Print the BitMap
void printBitMap(BitMap *x) {
    for(int i = 0; i < x->row; i++) {
        printf("\n");
           for(int j = 0; j< x -> columns; j++) {
                printf("%c ", x -> data[i][j]);
           }
    }
}


// Free allocated memory
void freeBitMap(BitMap *bp) {

     for(int i=0; i<5;i++) {
         free(bp -> data[i]);
     }

     free(bp -> data);

     free(bp);
}
