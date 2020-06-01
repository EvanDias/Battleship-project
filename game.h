#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "board.h"

bool allShipsSink(User *usr);
void game(User *usr1, User *usr2, int boardSize);
int randomShoot(int matrixSize);
bool shotPlayer(User *user, int x, int y);
bool sinkBoatStructure(void *structure,int boardSize);
void modifyValuesStruct(User *user, int x, int y);
bool canInsert(User *user, SHIP *sh, int x, int y, int boardSize); 
bool insertShipInStructure(User *user, SHIP *ship, int x, int y, int boardSize);
void scanPointRotation(ListNode *node);
bool canShot(User *usr, int x, int y, int boardSize);
void modifyShotsStruct(User *user, int x, int y, bool b);
void insertLittleCell(User *user, int x, int y);
