#include <stdio.h> 
#include <stdlib.h>



int main() {

    printf("------------------------------------------------ \n");
    printf("            WELCOME TO BATTLESHIP                \n");
    printf("------------------------------------------------ \n");

    printf("\n");

    printf("(1) Start \n");
    printf("(2) Rules \n");

    int numberMenu;

    scanf("%d", &numberMenu);
    choiceMenu(numberMenu);
    //choiceShips(numberChoiceShips);

}