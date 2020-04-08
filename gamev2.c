#include <stdio.h>
#include "gamev2.h"

User *initUser(char *username, List *shipList, Matrix *matrix) {

  User *newUser = malloc(sizeof(User)); 

  newUser -> username = username; 
  
  matrix = initMatrix(matrix->size);

  newUser -> matrix = matrix;

  shipList = listShips(matrix->size);

  newUser -> shipList = shipList;

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
      List *list = initList();
      User *usr1 = initUser("ola",list,matrix);
      printf("%s \n", usr1 -> username);
      printList(usr1->shipList);
    

}


