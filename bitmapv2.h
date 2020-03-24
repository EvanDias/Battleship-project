#include <stdio.h>
#include <stdlib.h>

#define BIT (8*(sizeof(BYTE)))


typedef enum {false = 0, true = 1} bool;
//typedef unsigned char BYTE;


typedef struct bitmap_ BITMAP;

struct bitmap_ {

  unsigned char *data;
  int number;

};


BITMAP *createBitMap(int number);
void setBit(BITMAP *bitmap, int numberBit);
void resetBit(BITMAP *bitmap, int numberBit);
bool isSet(BITMAP *bitmap, int numberBit);