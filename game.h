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
SHIP **arrayWithShips();  //array com as listas todas
int choiceMatrix();       //escolher o valor da matrix
void choiceOne();          //o que acontece na opção 1     
void choiceTwo();         //o q acontece na opção 2
