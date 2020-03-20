#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "matrix.h"
#define MAX_BUFFER 1024

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



void mainMenu() {

    system("clear");

    printf("------------------------------------------------ \n");
    printf("            WELCOME TO BATTLESHIP                \n");
    printf("------------------------------------------------ \n");

    printf("\n");

    printf("(1) Start \n");
    printf("(2) Rules \n");
    printf("(3) Exit \n\n");
    printf("Choose one option: ");

    int choice_menu;
    scanf("%d", &choice_menu);

    while(choice_menu != 1 && choice_menu != 2 && choice_menu != 3) {
        printf("Wrong option, choose again: ");
        scanf("%d", &choice_menu);
    }

    choiceMenu(choice_menu);

}



// Chosen option of the mainMenu()
void choiceMenu(int numberMenu) {

    int numberMatrix;

    if(numberMenu == 1) {
       choiceOne();
      }

    else if(numberMenu == 2) {
        system("clear");
        printf("Rules are: \n\n");
        choiceTwo();
    }

    else if(numberMenu == 3) { // Close the program
        exit(0);
    }
}



// Start game
void choiceOne() {

    system("clear");
    printf("Write the size of the matrix (n*n, n >=10): ");
    int sizerMatrix = choiceMatrix();

    printf("Create a user 1 \n");
    printf("Your name: ");
    char *name1 = malloc(sizeof(char)*1024);
    scanf("%s", name1);
    User *user1 = initUser(name1);

    printf("\nCreate a user 2 \n");
    printf("Your name: ");
    char *name2 = malloc(sizeof(char)*1024);
    scanf("%s", name2);
    User *user2= initUser(name2);

    printf("\nUser 1: %s \n", user1 -> nameUser);
    printf("User 2: %s \n", user2 -> nameUser);


    initializeGame(user1, user2, sizerMatrix);

}



// See rules of the game
void choiceTwo() {

    char buffer[MAX_BUFFER];
    int c;

    FILE *file;
    file = fopen("rules.txt", "r");

    if(file) {
        while((c = getc(file)) != EOF) putchar(c);
            fclose(file);
    }

    printf("\n\n-> Type 1 to return to the main Menu: ");
    int choice;
    scanf("%d",&choice);

     while(choice != 1) {
        printf("Wrong option, choose again: ");
        scanf("%d", &choice);
    }

    mainMenu();

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
bool verifyPointVertical(int direction, Point *inicial, SHIP *ship) {

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
void vertical(int direction, SHIP *ship, Matrix *matrix, Point *initial) {

    if(verifyPointVertical(direction, initial, ship) == false) {
        printf("Boas\n");
    }

    int count = inicial -> y;

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

    insertShipInMatrix(matrix, ship);
}



// User choosing where to put yours ships
void shipChoice(Matrix *matrix) {

    int * numShips;
    numShips = getNumShips();

    char ch_x, ch_y;

    /*
    // SOLO SHIP
    for(int i=0; i < numShips[0] ; i++) {
        printf("\nChoose one point to put SOLO ship:\n");
        printf("x: ");
        scanf(" %c", &ch_x);
        printf("y: ");
        scanf(" %c", &ch_y);

        int x = charToInt(ch_x);
        int y = charToInt(ch_y);

        Point *initial = newPoint(x,y);

        // FALTA FUNÇÃO PARA VER SE JA NAO EXISTE UM SHIP NO LOCAL

        matrix = insertShipInMatrix(matrix, initHeadShip(x,y));

        printMatrix(matrix);
    }
    */




    // REMAINING SHIPS
    for(int j=0; j < 1; j++) {
        int choice, direction;

        printf("Chose a positions for dual ship: \n");
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

        Point *initial = newPoint(x,y);

        if(choice == 1) {

            vertical(direction, initHeadShip(x,y), matrix, initial);
        }

        //else if(choice == 2)

        printMatrix(matrix);
    }

}



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



















