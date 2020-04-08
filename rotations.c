#include <stdio.h>


void rotation90(SHIP *sh) {

  BitMap *bitaux = initBitMap(5,5);

  for(int i = 0; i < sh -> columns; i++) {
    for(int j = 0; j < sh -> rows; j++) {
      sh -> bp = bitaux;
      sh -> bp = changeCellValue(sh -> bp,i,j, '1');
    }
  }


}
