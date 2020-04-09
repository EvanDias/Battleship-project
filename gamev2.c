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

bool sinkBoat(SHIP *ship) {

    int sinkBoatV = false; 

    if(ship -> shotCount == 0) sinkBoatV = true;
     
    return sinkBoatV;
}

void sinkBoatMatrix(Matrix *x) {

    bool sinkingBoat = false; 
    int broke = 0;

    for(int i = 0; i < x -> size; i++) {
      for(int j = 0; j < x -> size; j++) {
        if(x -> data[j][i] -> value == '#') {
          if(sinkBoat(x -> data[j][i] -> ship)==true) {
            broke = 1;  
            printf("Sink a boat with coordenates (%d,%d) \n", j,i); 
            break;      
        }
      }
    }
    if(broke) {
      break;
    }
  }
}


void changeValueShotBp(Matrix *matrix, int x, int y) {

    int x_value = matrix -> data[y][x]-> ship -> bp -> refx; 
    int y_value = matrix -> data[y][x]-> ship -> bp -> refy;

    matrix -> data[y][x]-> ship -> bp -> data[y-y_value][x -x_value] = '2';

}

void shotInPlayer(Matrix *self, Matrix *other, int x, int y) {

  if(other -> data[y][x] -> value == 'x') {
    //o que aparece quando é acertado 
    other -> data[y][x] -> value = '#';
    other -> data[y][x] -> ship -> shotCount--;
    changeValueShotBp(other,x,y);
    //alterar o shot da nossa celula para 2
    self -> data[y][x] -> shot = '2';

    //alterar o valor do nosso value para Shot
    self -> data[y][x] -> value = 'S';
    printf("shotCount: %d\n", other -> data[y][x] -> ship -> shotCount);
  }

  else if(other -> data[y][x] -> value == '.') {
    //o valor do outro passa para +
    other -> data[y][x] -> value = '+';
    self -> data[y][x] -> shot = '1';
    //alterar o shot para wrong
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


/*

int main() {

      Matrix *matrix = initMatrix(20);
      Matrix *self = initMatrix(20);

      SHIP *sh = newShip(4);
      SHIP *sh2 = newShip(3);
      SHIP *sh1 = newShip(0);

      insertShipInMatrix(matrix, sh,0,0);
      insertShipInMatrix(matrix,sh2,2,2);
      insertShipInMatrix(matrix,sh1,15,15);
      insertShipInMatrix(matrix,sh2,17,17);
     
      shotInPlayer(self, matrix,0,4);
      shotInPlayer(self,matrix,14,14);
      shotInPlayer(self,matrix,50,15);

      printMatrix(matrix);
      //printMatrix(self);

      sinkBoatMatrix(matrix);

      printBitMap(matrix -> data[0][0]-> ship -> bp);

   



}


*/
