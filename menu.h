#ifndef RANDOM_MENU_H
#define RANDOM_MENU_H
#include "randomShips.h"

void mainMenu();
void choiceOne();
void choiceTwo();
void choiceMenu(int numberMenu);
void choiceModeGame(User *user, int boardSize);
void choiceShips(User *user, int boardSize);
void choiceShipsAuto(User *user, int boardSize);
void choiceShipsManual(User *user, int boardSize);
void insertMode(User *user, ListNode *node, int boardSize);
void initializedGame(User *usr1, User *usr2, int boardSize);
bool deleteListShip(User *usr, int x, int y, int boardSize);
void scanPointInsert(User *user, ListNode *node, int boardSize);


#endif //RANDOM_MENU_H
