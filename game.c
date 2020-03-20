#include <stdio.h>
#include <stdlib.h>
#include "game.h"

// Create a user
User *initUser(char *nameUser) {

    User *newUser = malloc(sizeof(User));

    newUser -> nameUser = nameUser;
    //newUser -> arrayShips = arrayShips;


    return newUser;
}



// Array containing all ships of a User
SHIP **arrayWithShips(Point **arrayPoints)  {

    SHIP **new = malloc(sizeof(SHIP*));

    SHIP *newShip = malloc(sizeof(SHIP));

    List * list = initList();

    return new;
}



// Choosing the size of the matrix
int choiceMatrix() {

    int numberN;

    scanf("%d", &numberN);
    if(numberN < 10) {
        printf("Can't a matrix be with that value. The value should be greater or equal than 10. Repeat, please \n");
        choiceMatrix();
    }

    return numberN;
}



// Verify if a horizontal ship doesn't leave the game area
bool verifyPointHorizontal(int direction, Point *inicial, SHIP *ship, int n) {

    if(direction == 1) {
        if(inicial -> x + ship -> size - 1 > n) return false;
        else return true;
    }

    if(direction == 2) {
        if(inicial -> x - ship -> size - 1 < 0) return false;
        else return true;
    }

}



// Verify if a vertical ship doesn't leave the game area
bool verifyPointVertical(int direction, Point *inicial, SHIP *ship, int n) {

    if(direction == 1) { //cima para baixo
        if(inicial -> y + ship -> size - 1 > n) return false;
        else return true;
    }

    if(direction == 2) {  //baixo para cima
        if(inicial -> y - ship -> size - 1 < 0) return false;
        else return true;
    }

}



// Insert a ship in the horizontal position
void *horizontal(int direction, SHIP *ship, Matrix *matrix, int flag) {
    int sizeShip = size_Ship(flag);

    Point *inicial = ship -> list -> head -> data;

    int count = inicial -> x;

    if(direction == 1)  { //1 => esquerda p/direita
    for(int i = 0;  i < sizeShip; i++) {
        Point *p1 = malloc(sizeof(Point));
        p1 = newPoint(count++,inicial -> y);
        ship -> list = headList(ship -> list, p1);
        }
    }

    if(direction == 2) { //2 => direita p/esqueda
    for(int i = 0; i < sizeShip; i++) {
        Point *p1 = malloc(sizeof(Point));
        p1 = newPoint(count--, inicial -> y);
        ship -> list = headList(ship -> list, p1);

        }
    }

     insertShipInMatrix(matrix, ship);
     printMatrix(matrix);
}



// Insert a ship in the vertical position
void *vertical(int direction, SHIP *ship, Matrix *matrix, int flag) {
    int sizeShip = size_Ship(flag);

    Point *inicial = ship -> list -> head -> data;

    int count = inicial -> y;

    if(direction == 1)  { //1 => cima p/baixo
    for(int i = 0;  i < sizeShip; i++) {
        Point *p1 = malloc(sizeof(Point));
        p1 = newPoint(inicial -> x,count++);
        ship -> list = headList(ship -> list, p1);
        }
    }

    if(direction == 2) { //2 => baixo p/ cima
    for(int i = 0; i < sizeShip; i++) {
        Point *p1 = malloc(sizeof(Point));
        p1 = newPoint(inicial -> x, count--);
        ship -> list = headList(ship -> list, p1);

        }
    }

    insertShipInMatrix(matrix, ship);
    printMatrix(matrix);
}



void initializeGame(User *user1, User *user2, int matrixSize) {


    system("clear");

    printf("GAME BOARD of user %s: \n\n", user1 -> nameUser);

    // Matrix of the player 1
    Matrix *num1 = initMatrix(matrixSize);
    printMatrix(num1);

    shipChoice(num1);

}



// User choosing where to put yours ships
void shipChoice(Matrix *matrix) {
    int flag=0;
    char ch_x, ch_y;
    int * numShips;
    numShips = getNumShips(matrix -> size);

    // SOLO SHIP
    for(int i=0; i<numShips[flag]; i++) {
        printf("\nChoose one point to put SOLO ship:\n");
        printf("x: ");
        scanf(" %c", &ch_x);
        printf("y: ");
        scanf(" %c", &ch_y);

        int x = charToInt(ch_x);
        int y = charToInt(ch_y);

        SHIP *shipSolo = initHeadShip(x,y);

        // FALTA FUNÇÃO PARA VER SE JA NAO EXISTE UM SHIP NO LOCAL

        matrix = insertShipInMatrix(matrix, shipSolo);

        printMatrix(matrix);

    }

    flag++;

    // OTHER SHIPS
    for(int j=0; j < 4; j++) {
        for(int i = 0; i < numShips[flag]; i++) {
            int choice, direction;

            printf("Chose a positions for %d ship: \n", flag);
            printf("1) Vertical\n");
            printf("2) Horizontal\n");
            printf("Choice: ");
            scanf("%d", &choice);

            if(choice == 1) {
                printf("1) Top -> down\n");
                printf("2) Bottom -> up\n");
                printf("Choice: ");
                scanf("%d", &direction);


            } else if(choice == 2) {
                printf("1) Left to right\n ");
                printf("2) Right to lef\n");
                printf("Choice: ");
                scanf("%d", &direction);
            } else {
                printf("Erro");
            }

            printf("\nChoose the first point: \n");
            printf("x: ");
            scanf(" %c", &ch_x);
            printf("y: ");
            scanf(" %c", &ch_y);

            int x = charToInt(ch_x);
            int y = charToInt(ch_y);

            SHIP *shipSolo2 = initHeadShip(x,y);

            if(choice == 1) {
                vertical(direction, shipSolo2, matrix, flag);
            }
            else if(choice == 2) {
                horizontal(direction, shipSolo2, matrix, flag);
            }
        }
            flag++;
    }
}



SHIP *initHeadShip(int x, int y) {
    Point *point = newPoint(x,y);

    List *list = initList();

    list = headList(list, point);

    SHIP *ship = new_ship(QUAD,list);

    return ship;
}



ShipKind whichKind(int flag) {
    if(flag == 0) return SOLO;
    else if(flag == 1) return DUAL;
    else if(flag == 2) return TRIAL;
    else if(flag == 3) return QUAD;
    else if(flag == 4) return T_GUY;
    else printf("Erro whichKind\n");
}



// convert Character to int. Ex: (A B C D E ...) -> (0 1 2 3 4 ...)
int charToInt(char chInput) {

    int inc = 0;

    char ch = 'A';

    while(1) {

        if(ch == chInput)
            return inc;

        ch++;
        inc++;
    }
}



int * getNumShips(int matrixSize) {

  static int array[5];
  array[0] = 2;
  array[1] = 2;
  array[2] = 1;
  array[3] = 1;
  array[4] = 1;

  int count = 0;
  count = (int)matrixSize/10;

  /*for(int j = 0; j < 5; j++) {
    printf("pre => i = %d e valor = %d: \n",j, array[j]);
  }

  printf("count %d\n", count);
*/
    for(int i = 0; i < count; i++) {

        if(matrixSize%10 == 1) {
          array[0] += 1;
          array[1] += 1;
        }
        else if(matrixSize%10 > 1 && matrixSize%10 <= 3) {
          array[0]+= 1;
          array[1] += 1;
          array[2] += 1;

        }

        else if(matrixSize%10 > 3 && matrixSize%10 <= 5) {
          array[0] += 2;
          array[1] += 2;
          array[2] += 1;
          array[3] += 1;
        }

        else if(matrixSize%10 > 5) {
          array[0] += 3;
          array[1] += 3;
          array[2] += 2;
          array[3] += 1;
          array[4] += 1;
        }
    }

    for(int j = 0; j < 5; j++) {
        printf("i = %d e valor = %d; \n",j, array[j]);
      }

    return array;
}



int size_Ship(int flag) {

    if(flag == 0) return 1;
    else if(flag == 1) return 2;
    else if(flag == 2) return 3;
    else if(flag == 3) return 4;
    else if(flag == 4) return 5;

}











/*

SHIP *initHeadShip(Point *initial) {

    List *list = initList();

    list = headList(list, initial);

    SHIP *ship = new_ship(QUAD,list);

    return ship;
}






*/
