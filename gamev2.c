#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include "gamev2.h"
#include <unistd.h>
User *initUser(char *username, int sizeMatrix) {

  User *newUser = malloc(sizeof(User));

  newUser -> username = username;

  Matrix *matrix = initMatrix(sizeMatrix);

  newUser -> matrix = matrix;

  newUser -> shipList = listShips(sizeMatrix);

   return newUser;
}


List *listShips(int sizeMatrix) {

    int number = numberShips(sizeMatrix);

    List *shipList = initList();

    int i = 0;

    while(number != 0) {
      while(i < 5 && number != 0) {
        SHIP *ship = newShip(i);
        headList(shipList,ship);
        number--;
        i++;
      }
      i = 0;
    }

    return shipList;

}

bool sinkBoat(SHIP *ship) {

    bool sinkBoatV = false;

    if(ship -> shotCount == 0) sinkBoatV = true;

    return sinkBoatV;
}

bool sinkBoatMatrix(Matrix *x) {
    for(int i = 0; i < x -> size; i++) {
      for(int j = 0; j < x -> size; j++) {
        if(x -> data[j][i] -> value == '*') {
          if(sinkBoat(x -> data[j][i] -> ship)==true) {
            printf("Sink a boat with coordenates (%d,%d) \n", j,i);
            return true;
        }
      }
    }
  }
  return false;
}


void changeValueShotBp(Matrix *matrix, int x, int y, unsigned char ternaryValue) {

    int x_value = matrix -> data[y][x]-> ship -> bp -> refx;
    int y_value = matrix -> data[y][x]-> ship -> bp -> refy;

    matrix -> data[y][x]-> ship -> bp -> data[y-y_value][x -x_value] = ternaryValue;
}

bool shotInPlayer(Matrix *self, Matrix *other, int x, int y) {

    bool shot = canShot(other,x,y);
    bool shotMatrix = false;


    if(shot) {
      if(other -> data[y][x] -> value == 'x') {
        //o que aparece quando é acertado
        other -> data[y][x] -> value = '*';
        other -> data[y][x] -> ship -> shotCount--;
        changeValueShotBp(other,x,y,'2');
        //alterar o shot da nossa celula para 2
        self -> data[y][x] -> shot = '2';
        printf("Your hit a  cell of a ship\n");
        shotMatrix = true;
      }
      else if(other -> data[y][x] -> value == '.') {
        //o valor do outro passa para +
        other -> data[y][x] -> value = '+';
        self -> data[y][x] -> shot = '1';
        printf("You hit a empty cell\n");
        shotMatrix = true;
      }
  }

  return shotMatrix;
}


bool canShot(Matrix *matrix, int x, int y) {

  bool shot = true;
 

        if(y >= matrix -> size || x >= matrix -> size) {
          shot = false;
        
        }
        else if(matrix -> data[y][x] -> value == 'x' || matrix -> data[y][x] -> value == '.') 
                  shot = true;
                

    return shot;
}

void printList(List *list) {

    ListNode *node = list -> head;

    while( node != NULL) {
        printf("%d ", node -> ship -> kind);
        node = node -> next;
    }
    printf("\n");

  }

int chooseMatrixSize() {
    int size;

    printf("Write the size of the matrix (20 <= x <= 40): ");
    scanf("%d", &size);

    while(size < 20 || size > 40) {
        printf("Write the size of the matrix (20 <= x <= 40): ");
        scanf("%d", &size);
    }

    return size;
}


User *whoStartGame(User *usr1, User *usr2) {

  User *started;

  int numberUsr1, numberUsr2;

  printf("User %s choose a number: \n", usr1 -> username);
  scanf("%d", &numberUsr1);
  printf("User %s choose a number: \n", usr2 -> username);
  scanf("%d", &numberUsr2);

  if(numberUsr1 > numberUsr2) started = usr1;
  else if(numberUsr1 < numberUsr2) started = usr2;
  else {
    printf("The numbers are equal, choose other number\n");
    started = whoStartGame(usr1,usr2);
  }

  return started;

}


void initializedGame(User *usr1, User *usr2) {

  system("clear");

  printf(" -------------START GAME------------- \n");
  User *started = whoStartGame(usr1,usr2);

  printf("User %s - you start a game \n", started -> username);

  if(started == usr1) game(usr1,usr2);
  else if (started == usr2) game(usr2,usr1);


}


void game(User *start, User *other) {
  char ch_x, ch_y;
  int x, y = 0;
  bool shotMatrix = false;

    while(1) {

    printUsers(start, other);
    printBothMatrix(start -> matrix, other -> matrix);

    printf("%s choose point to hit a ship of %s\n", start -> username, other -> username);
    printf("x: ");
    scanf(" %c", &ch_x);
    printf("\ny: ");
    scanf(" %c",&ch_y);

    x = choiceChar(ch_x);

    y = choiceChar(ch_y);


    shotMatrix = shotInPlayer(start -> matrix, other -> matrix,x,y);

    while(shotMatrix == false) {
      printf("Try Again\n");
      printf("%s choose point to hit a ship of %s\n", start -> username, other -> username);
      printf("x: ");
      scanf(" %c", &ch_x);
      printf("\ny: ");
      scanf(" %c",&ch_y);

      x = choiceChar(ch_x);
      y = choiceChar(ch_y);

      shotMatrix = shotInPlayer(start -> matrix, other -> matrix, x,y);
    }


    printUsers(start, other);
    printBothMatrix(start -> matrix, other -> matrix);

    if(sinkBoatMatrix(other -> matrix))
        printSinkShip(other -> matrix, x, y);
    sleep(3);

    if(allShipsSink(start) || allShipsSink(other)) {
        printf("The player %s win the game! \n", start -> username);
        break;
    }

    printUsers(other, start);
    printBothMatrix(other -> matrix, start -> matrix);

    printf("%s choose point to hit a ship of %s \n", other -> username, start -> username);
    printf("x: ");
    scanf(" %c", &ch_x);
    printf("\ny: ");
    scanf(" %c",&ch_y);

    x = choiceChar(ch_x);
    y = choiceChar(ch_y);

    shotMatrix = shotInPlayer(other -> matrix, start -> matrix,x,y);


    while(shotMatrix == false) {
      printf("Try Again\n");
      printf("%s choose point to hit a ship of %s\n", other -> username, start -> username);
      printf("x: ");
      scanf(" %c", &ch_x);
      printf("\ny: ");
      scanf(" %c",&ch_y);

      x = choiceChar(ch_x);
      y = choiceChar(ch_y);

      shotMatrix = shotInPlayer(other -> matrix, start -> matrix,x,y);
    }

    printUsers(other, start);
    printBothMatrix(other -> matrix, start -> matrix);

    if(sinkBoatMatrix(start -> matrix))
        printSinkShip(start -> matrix, x, y);
    sleep(3);

    if(allShipsSink(start) || allShipsSink(other)) {
        printf("||     CONGRULATIONS!     \n");
        printf("The player %s win the game! \n", other -> username);
        break;
    }
  }
}

bool allShipsSink(User *usr) {

  ListNode *node = usr -> shipList -> head;
  int countShips = numberShips(usr -> matrix -> size);

  bool sink = false;

  while(node != NULL) {
    sink = sinkBoat(node -> ship);
    if(sink) countShips--;
    node = node -> next;
  }

  if(countShips==0)
    return true;
  else
    return false;
}


void printSinkShip(Matrix *matrix, int x, int y) {
    SHIP *ship = matrix -> data[y][x] -> ship;

    int xref = ship -> bp -> refx;
    int yref = ship -> bp -> refy;

    printf("KIND: %d\n", ship -> kind);

    for(int i = 0; i < sizeBitMap; i++) {
      for(int j = 0; j < sizeBitMap; j++) {
        if (ship -> bp -> data[j][i] == '2') {
            matrix -> data[j+yref][i+xref]-> value = '#';
        }
      }
    }
}


void printUsers(User *start, User *other) {
    system("clear");
    int matrixSize = (start -> matrix -> size)*2;
    int count = matrixSize / 2 - 7;

   for(int a=0; a < count; a++)
        printf(" ");
    printf("Matrix %s", start -> username);

    for(int a=0; a < 10 + count + (matrixSize/2 - 4); a++)
        printf(" ");
    printf("Matrix %s", other -> username);

}


int choiceChar(char c) {
    int x;

    if(c >= 'A' && c <= 'Z')
        x = charToIntUpper(c);
    else
        x = charToIntLower(c);

    return x;
}

// convert Character to int. Ex: (A B C D E ...) -> (0 1 2 3 4 ...)
int charToIntUpper(char chInput) {

    int inc = 0;

    char ch = 'A';

    while(true) {

        if(ch == chInput)
            return inc;

        ch++;
        inc++;
    }

    return inc;
}


// convert Character to int. Ex: (a b c d e ...) -> (0 1 2 3 4 ...)
int charToIntLower(char chInput) {

    int inc = 26;

    char ch = 'a';

    while(true) {

        if(ch == chInput)
            return inc;

        ch++;
        inc++;
    }

    return inc;
}
