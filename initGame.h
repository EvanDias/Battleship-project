#ifndef RANDOM_INITgAME_H
#define RANDOM_INITgAME_H
#include "geral.h"


typedef struct user_ User;

struct user_ {

  char *username;
  List *shipList;

  void *dataStructs;
};

User *initUser(char *username, int sizeBoard);
char *getUsername(User *user);
List *listShips(int sizeBoard);
List *getShipList(User *user);
int chooseBoardSize();
void setStructure(User *user, void *structure);
void *getStructure(User *user);
int numberShips(int sizeBoard);
User *whoStartGame(User *usr1, User *usr2);
void printUsers(User *start, User *other,int boardSize);
//void freeUser(User *usr);

#endif //RANDOM_INITgAME_H