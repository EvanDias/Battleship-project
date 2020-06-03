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

  char *kind = nameShip((SHIP*)(node -> data)); 
  if(kind != "L_GUY" && kind != "S_GUY") {
    x = random()%sizeBitMap;
    y = random()%sizeBitMap;

  }
    bool translate = translation((SHIP*)node -> data, y, x);

    while(translate == false) {
      x = random()%sizeBitMap;
      y = random()%sizeBitMap;
      translate = translation((SHIP*)node -> data, y, x);
    }

    if(translate==true) {
      printf("Os valores são x: %d, y: %d\n",x,y);

    }
}


void randomRotation(ListNode *node) {

  int numberRandom = random()%4;
  rotation((SHIP*)node -> data, rotationNumber(numberRandom));

  printf("O valor da rotação: %d\n",rotationNumber(numberRandom));
}


void randomInsert(User *user, ListNode *node, int boardSize) {

  int x = 0;
  int y = 0;

  char * kind = nameShip((SHIP*)node -> data);

  bool inserted = false;

  x = random()%boardSize; 
  y = random()%boardSize;

  inserted = insertShipInStructure(user, (SHIP*)node -> data,x,y, boardSize);

  while(inserted == false) {
      x = random()%boardSize;
      y = random()%boardSize;
      inserted = insertShipInStructure(user,(SHIP*)node -> data, x, y, boardSize);
  }
  


}
