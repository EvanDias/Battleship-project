#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "list.h"

#define MAX_BUFFER 1024

typedef struct user_ User;


struct user_ {

    char *nameUser;
    //SHIP **arrayShips;

};


User *initUser(char *nameUsers);
void choiceMenu(int number);
SHIP **arrayWithShips();
int choiceMatrix();
void initializeGame(User *user1, User *user2, int matrixSize);
int charToInt(char c);
void shipChoice(Matrix *matrix);
ShipKind whichKind(int flag);
SHIP *initHeadShip(int x, int y);
int * getNumShips();
int size_Ship(int flag);