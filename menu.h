#include <ctype.h>
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
