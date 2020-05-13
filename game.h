#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "initGame.h"

bool shotInPlayer(User* self, User* other, int x, int y);
bool allShipsSink(User *usr);
bool gameTurn(User *start, User *other);
void game(User *usr1, User *usr2);
void modeGame(User *star, User *other, int x, int y);
void printSinkShip(Matrix *matrix, int x, int y);
bool playAgain(User *start, User *other);
int randomShoot(int matrixSize);