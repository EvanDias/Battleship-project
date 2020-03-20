#include <stdio.h>
#include <stdlib.h>
#include "ship.h"

typedef struct user_ User; 


struct user_ {

    char *nameUser;
    //SHIP **arrayShips;

};


User *initUser(char *nameUsers);
void choiceMenu(int number);
SHIP **arrayWithShips();
int choiceMatrix();
void choiceOne();
void choiceTwo();
void mainMenu();
void initializeGame(User *user1, User *user2, int matrixSize);
int charToInt(char c);
int * getNumShips();
SHIP *initShip(int x, int y);