#include <stdio.h>
#include "gamev2.h"

User *initUser(char *username, List *shipList, Matrix *matrix) {

  User *newUser = malloc(sizeof(User));

  newUser -> username = username;

  matrix = initMatrix(matrix->size);

  newUser -> matrix = matrix;

  shipList = listShips(matrix->size);

  newUser -> listShips = shipList;

  return newUser;

}

List *listShips(int sizeMatrix) {

    int number = numberShips(sizeMatrix);

    List *list = initList();

    int i = 0;

    while(number != 0) {
      while(i < 5 && number != 0) {
        SHIP *ship = newShip(i);
        headList(list,ship);
        number--;
        i++;
      }
      i = 0;
    }

    return list;

}


void shotInPlayer(Matrix *self, Matrix *other, int x, int y) {

  if(other -> data[y][x] -> value == 'x') {
    other -> data[y][x] -> value = '#';
    other -> data[y][x] -> ship -> shotCount--;
    self -> data[y][x] -> shot = '2';
    self -> data[y][x] -> value = 'S';
    printf("shotCount: %d\n", other -> data[y][x] -> ship -> shotCount);
  }

  else if(other -> data[y][x] -> value == '.') {
    other -> data[y][x] -> value = '+';
    self -> data[y][x] -> shot = '1';
    self -> data[y][x] -> value = 'W';

  }
  else printf("Não acertou\n");

}

void printList(List *list) {

    ListNode *node = list -> head;

    while( node != NULL) {
        printf("%d ", node -> ship -> kind);
        node = node -> next;
    }
    printf("\n");

  }


int main() {

        /*SHIP *sh = newShip(2);
        printBitMap(sh -> bp);
        printf("\n\n");
        translation(sh,2,2);
        printBitMap(sh -> bp);
        printf("\n\n");
        //printf("\n\n");
        rotation(sh,90);
        printBitMap(sh -> bp);

        printf("\n\n");

      List *ships = listShips(20);
*/

      Matrix *matrix = initMatrix(20);
      Matrix *self = initMatrix(20);

      List *list = initList();
      User *usr1 = initUser("ola",list,matrix);

      SHIP *sh = newShip(4);
      SHIP *sh2 = newShip(2);


      insertShipInMatrix(matrix, sh,2,3);
      insertShipInMatrix(matrix,sh,10,5);
      insertShipInMatrix(matrix,sh2,15,15);


      shotInPlayer(self,matrix,2,3);
      shotInPlayer(self,matrix,2,5);
      shotInPlayer(self,matrix,3,7);
      shotInPlayer(self,matrix,1,1);

      printMatrix(matrix);

      printMatrix(self);

}
