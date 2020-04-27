#ifndef RANDOM_MENU_H
#define RANDOM_MENU_H
#include "randomShips.h"

#define MAX_BUFFER 1024

void mainMenu();
void choiceOne();
void choiceTwo();
void choiceMenu(int numberMenu);
void choiceModeGame(User *user);
void choiceShips();
void choiceShipsAuto(User *user);
void choiceShipsManual(User *user);
void insertMode(User *user);

#endif //RANDOM_MENU_H