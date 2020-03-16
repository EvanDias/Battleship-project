#include <stdio.h> 
#include <stdlib.h>
#include "game.h"
#include "matrix.h"

#define MAX_BUFFER 1024 

typedef enum {true, false} bool;

User *initUser(char *nameUser) {

    User *newUser = malloc(sizeof(User));

    newUser -> nameUser = nameUser;
    //newUser -> arrayShips = arrayShips;


    return newUser;
}



SHIP **arrayWithShips(Point **arrayPoints)  {

    SHIP **new = malloc(sizeof(SHIP*));
    
    SHIP *newShip = malloc(sizeof(SHIP));

    List * list = initList();

    

    return new;
}

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
   // printMatrix(num1);

    printMenuShips(); 


    Point *point = newPoint(2,3);

    List *list = initList();

    SHIP *shipTest = new_ship(QUAD,list);
    //printf("SIZE: %d", shipTest -> size);

    if(verifyPointVertical(2,point,shipTest,matrixSize)==true) shipTest = vertical(2,point,shipTest,matrixSize);
    else printf("Try other point \n");
    
        
    //SHIP **new = arrayWithShips(point);

    num1 = insertShipInMatrix(num1,shipTest);

    printMatrix(num1);
    


}
