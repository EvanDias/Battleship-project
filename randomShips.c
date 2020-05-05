#include "randomShips.h"


#define rotationNumber(number)({int degrees = 0; \
    switch (number) {\
      case 1: degrees = 180; \
          break;\
      case 2: degrees = 270;\
          break;\
      case 3: degrees = 90;\
          break;\
      default: degrees = 0;\
    } \
    degrees; \
})

/* Functions to random mode
  * translation
  * rotation
  * insertion of a ship
*/
void randomTranslation(ListNode *node) {
  int x = 0;
  int y = 0;

  if(node -> ship -> kind != 4 || node -> ship -> kind != 6) {
    x = rand()%sizeBitMap;
    y = rand()%sizeBitMap;

  }
    bool translate = translation(node -> ship, y, x);

    while(translate == false) {
      x = rand()%sizeBitMap;
      y = rand()%sizeBitMap;
      translate = translation(node -> ship, y, x);
    }

    if(translate==true) {
      printf("Os valores são x: %d, y: %d\n",x,y);

    }
}


void randomRotation(ListNode *node) {

  int numberRandom = rand()%4;
  rotation(node -> ship, rotationNumber(numberRandom));

  printf("O valor da rotação: %d\n",rotationNumber(numberRandom));
}


void randomInsertMatrix(ListNode *node, Matrix *matrix) {

  int x = random()%(matrix -> size);
  int y = random()%(matrix -> size);

  bool inserted = insertShipInMatrix(matrix, node -> ship, x, y);

  while(inserted == false) {
      x = random()%(matrix -> size);
      y = random()%(matrix -> size);
      inserted = insertShipInMatrix(matrix, node -> ship, x, y);
  }

  if(inserted==true) {

    printf("Os valores de x: %d e de y: %d\n",x,y);

  }
}
