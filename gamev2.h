#include <stdio.h>
#include "matrix.h"

typedef struct user_ User;


struct user_ {

  char *username;
  List *listShips;
  Matrix *matrix;

};



User *initUser(char *username, List *shipList, Matrix *matrix);
List *listShips(int sizeMatrix);
void shotInPlayer(Matrix *self, Matrix *other, int x, int y);
void printList(List *list);
