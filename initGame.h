#ifndef RANDOM_INITgAME_H
#define RANDOM_INITgAME_H
#include "matrix.h"


typedef struct user_ User;


struct user_ {

  char *username;
  List *shipList;
  Matrix *matrix;

};


User *initUser(char *username, int sizeMatrix);
List *listShips(int sizeMatrix);
int chooseMatrixSize();
int numberShips(int sizeMatrix);
User *whoStartGame(User *usr1, User *usr2);
void printUsers(User *start, User *other);

#endif //RANDOM_INITgAME_H