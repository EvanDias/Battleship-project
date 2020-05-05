#ifndef RANDOM_MENU_H
#define RANDOM_MENU_H
#include "randomShips.h"

void mainMenu();
void choiceOne();
void choiceTwo();
void choiceMenu(int numberMenu);
void choiceModeGame(User *user);
void choiceShips();
void choiceShipsAuto(User *user);
void choiceShipsManual(User *user);
void insertMode(User *user, ListNode *node);
void initializedGame(User *usr1, User *usr2);
bool deleteListMatrix(User *usr, int x, int y);

#endif //RANDOM_MENU_H
