#include <stdio.h>
#include <stdlib.h>
#include "ship.h"

typedef struct user_ User; 


struct user_ {

    char *nameUser;
    SHIP **arrayShips;

};

User *initUser(char *nameUser, SHIP **arrayShips);
void choiceMenu(int number);
SHIP **arrayWithShips();  //array com as listas todas
int choiceMatrix();       //escolher o valor da matrix
void choiceOne();          //o que acontece na opção 1     
