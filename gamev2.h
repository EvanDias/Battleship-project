#include <stdio.h>
#include "matrix.h"

typedef struct user_ User;


struct user_ {

  char *username;
  List *shipList;
  Matrix *matrix;

};



User *initUser(char *username, int sizeMatrix);
List *listShips(int sizeMatrix);
void shotInPlayer(Matrix *self, Matrix *other, int x, int y);
bool sinkBoatMatrix(Matrix *x);
void printList(List *list);
int chooseMatrixSize();
User *whoStartGame(User *usr1, User *usr2);
void initializedGame(User *usr1, User *usr2);
bool allShipsSink(User *usr);
void game(User *usr1, User *usr2);
void modeGame(User *star, User *other, int x, int y);
void printSinkShip(Matrix *matrix, int x, int y);