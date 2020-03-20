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
SHIP *horizontal(int direction, Point *inicial, SHIP *ship, int n) {

    int count = inicial -> x;

    ship -> list = headList(ship-> list,inicial);

    if(direction == 1)  { //1 => esquerda p/direita
    for(int i = 0;  i < ship -> size; i++) {
        Point *p1 = malloc(sizeof(Point));
        p1 = newPoint(count++,inicial -> y);
        ship -> list = headList(ship -> list, p1);
        }
    }

    if(direction == 2) { //2 => direita p/esqueda
    for(int i = 0; i < ship -> size; i++) {
        Point *p1 = malloc(sizeof(Point));
        p1 = newPoint(count--, inicial -> y);
        ship -> list = headList(ship -> list, p1);

        }
    }

    return ship;

}


// Insert a ship in the vertical position
SHIP *vertical(int direction, Point *inicial, SHIP *ship, int n) {

    int count = inicial -> y;

    ship -> list = headList(ship-> list,inicial);

    if(direction == 1)  { //1 => cima p/baixo
    for(int i = 0;  i < ship -> size; i++) {
        Point *p1 = malloc(sizeof(Point));
        p1 = newPoint(inicial -> x,count++);
        ship -> list = headList(ship -> list, p1);
        }
    }

    if(direction == 2) { //2 => baixo p/ cima
    for(int i = 0; i < ship -> size; i++) {
        Point *p1 = malloc(sizeof(Point));
        p1 = newPoint(inicial -> x, count--);
        ship -> list = headList(ship -> list, p1);

        }
    }

    return ship;
}



void initializeGame(User *user1, User *user2, int matrixSize) {


    system("clear");

    printf("GAME BOARD of user %s: \n\n", user1 -> nameUser);

    // Matrix of the player 1
    Matrix *num1 = initMatrix(matrixSize);
    printMatrix(num1);
/*
    Point *point = newPoint(2,3);
    List *list = initList();
    SHIP *shipTest = new_ship(QUAD,list);
    //printf("SIZE: %d", shipTest -> size);
    if(verifyPointVertical(2,point,shipTest,matrixSize)==true) shipTest = vertical(2,point,shipTest,matrixSize);
    else printf("Try other point \n");


    //SHIP **new = arrayWithShips(point);
    num1 = insertShipInMatrix(num1,shipTest);
*/



    shipChoice(num1);

}


// User choosing where to put yours ships
void shipChoice(Matrix *matrix) {

    char ch_x, ch_y;


    // SOLO SHIP
    //for(int i=0; i<2; i++) {
        printf("\nChoose one point to put SOLO ship:\n");
        printf("x: ");
        scanf(" %c", &ch_x);
        printf("y: ");
        scanf(" %c", &ch_y);

        int x = charToInt(ch_x);
        int y = charToInt(ch_y);

        Point *point = newPoint(x,y);

        List *list = initList();

        list = headList(list, point);

        SHIP *shipSolo = new_ship(SOLO,list);


        // FALTA FUNÇÃO PARA VER SE JA NAO EXISTE UM SHIP NO LOCAL

        matrix = insertShipInMatrix(matrix, shipSolo);

        printMatrix(matrix);
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


/*

SHIP *initHeadShip(Point *initial) {

    List *list = initList();

    list = headList(list, initial);

    SHIP *ship = new_ship(QUAD,list);

    return ship;
}



//  Number of ships that will be played
int * getNumShips() {

    static int r[5];

    r[0] = 2; // SOLO
    r[1] = 1; // DUAL
    r[2] = 2;
    r[3] = 1;
    r[4] = 0;

    return r;
}


*/
