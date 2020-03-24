#include <stdio.h>
#include <stdlib.h>

#include "bitmapv2.h"

BITMAP *createBitMap(int number) {

  BITMAP *bitmap = malloc(sizeof(BITMAP));

  bitmap -> number = number;

  unsigned char *data = malloc(sizeof(unsigned char)* ((number/8) + 1));

  for(int i = 0; i < (number/8 + 1); i++) {
    data[i] = 0;
  }

  bitmap -> data = data;

/*
  for(int i = 0; i < number; i++) {

    if(i % 4 == 0) printf("\n");
    printf("u: %u ",data[i]);
  }

  */
  return bitmap;

}

void setBit(BITMAP *bitmap, int posBit) {

 // int number = bitmap -> number;
/*
  BYTE newByte = numberBit/(numberBits/8 + 1);
  BYTE posByte = numberBit%(numberBits/8 + 1);

  newByte = newByte || (1 << posByte);

*/
  int findBytePos = (posBit / 8);

  bitmap -> data[findBytePos] = bitmap -> data[findBytePos] | 1 << posBit%8;
  //printf("byte %u\n",newByte);

}

void resetBit(BITMAP *bitmap, int posBit) {


  int findBytePos = (posBit/8);
  bitmap -> data[findBytePos] = bitmap -> data[findBytePos] & ~(1 << posBit%8);


}


bool isSet(BITMAP *bitmap, int posBit) {

  int findBytePos = (posBit/8);

  return (bitmap -> data[findBytePos] & 1 << posBit%8) != false;

}


void printbitmap(BITMAP *bitmap, int number) {


  for(int i = 0; i < number/8 + 1; i++) {
    printf("%u \n", bitmap -> data[i]);
}

}


int main() {

  BITMAP *bitmap = createBitMap(4);
  printbitmap(bitmap,4);

  setBit(bitmap, 2);
  printbitmap(bitmap,4);
  setBit(bitmap, 3);
  printbitmap(bitmap,4);
  resetBit(bitmap,2);
  printbitmap(bitmap, 4);
  bool esta = isSet(bitmap,2);
  printf("%d \n", esta);


}
