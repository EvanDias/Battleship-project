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
void sinkBoatMatix(Matrix *x);
void printList(List *list);
int chooseMatrixSize();