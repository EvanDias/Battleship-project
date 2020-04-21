#include "bitmap.h"


BitMap * initBitMap(int columns, int row) {

    BitMap *bp = malloc(sizeof(BitMap));

    bp -> columns = columns;
    bp -> row = row;

    bp -> refx = 0;
    bp -> refy = 0;

    unsigned char** data = malloc(sizeof(unsigned char*) * 1024);

    for(int i = 0; i < columns; i++)
        data[i] = malloc(columns * sizeof(unsigned char));

    for(int i = 0; i < row; i++)
            data[i] = malloc(row * sizeof(unsigned char));

    for(int i = 0; i < row; i++) {
           for(int j = 0; j< columns; j++) {
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



// Print the BitMap
void printBitMap(BitMap *x) {
    for(int i = 0; i < x->row; i++) {
        printf("\n");
           for(int j = 0; j< x -> columns; j++) {
                printf("%c ", x -> data[i][j]);
            }
        }
}
