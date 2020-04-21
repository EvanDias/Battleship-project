#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include "initGame.h"

void initializedGame(User *usr1, User *usr2);
bool shotInPlayer(Matrix *self, Matrix *other, int x, int y);
bool sinkBoatMatrix(Matrix *x);
void printList(List *list);
bool allShipsSink(User *usr);
void gameTurn(User *start, User *other);
void game(User *usr1, User *usr2);
void modeGame(User *star, User *other, int x, int y);
void printSinkShip(Matrix *matrix, int x, int y);
bool canShot(Matrix *self, int x, int y);
