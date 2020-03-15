#include <stdio.h> 
#include <stdlib.h>
#include "game.h"


int main() {

    int choice_menu = initialMenu();

    if(choice_menu == 1) startMenu();

    while(choice_menu != 1) {

        if(choice_menu == 2) { // Choose Rules
            rulesMenu();
        } else if(choice_menu == 3) { // Choose Exit
            exit(0);
        }

        choice_menu = initialMenu();

        if(choice_menu == 1){ // Choose START
            startMenu();
             break;
        }
    }




    //choiceMenu(numberMenu);
    //choiceShips(numberChoiceShips);

}




// Main Menu of the game
int initialMenu() {
    system("clear");

    printf("------------------------------------------------ \n");
    printf("            WELCOME TO BATTLESHIP                \n");
    printf("------------------------------------------------ \n\n");

    printf("(1) Start \n");
    printf("(2) Rules \n");
    printf("(3) Exit \n\n");
    printf("Choose one option: ");

    int choice_menu;
    scanf("%d", &choice_menu);

    while(choice_menu != 1 && choice_menu != 2 && choice_menu != 3) {
        printf("Wrong option, choose again: ");
        scanf("%d", &choice_menu);
    }

    return choice_menu;
}




// Start the game
int startMenu() {
    system("clear");

    printf("SIGA\n");
    printf("SIGA\n");
    printf("SIGA\n");
}




// Rules of the game
void rulesMenu() {
    system("clear");

    printf("------------------------------------------------ \n");
    printf("                BATTLE SHIP RULES                 \n");
    printf("------------------------------------------------ \n");

    printf("1) Each player have a number of ships( depending on the size of the board) to place somewhere on their board(random or manual).\n");
    printf("2) The ships can only be placed vertically or horizontally.\n");
    printf("3) Once the guessing begins, the players may not move the ships.\n");
    printf("4) The ships are: Solo (occupies 1 space), Dual (occupies 2 spaces), Trial (occupies 3 spaces), Quad (occupies 4 spaces) and T_Guy (occupies 5 spaces).\n");
    printf("5) Player's take turns guessing by calling out the coordinates (x and y).\n");
    printf("6) If player hits a boat coordinate, he can play again until he fails. If he hists all boat coordinates, the boat is sunk.\n");
    printf("7) If player miss a boat coordinate, is the opposing player's turn.\n");
    printf("8) The game  end when a player's boats are all sunk.\n");

    printf("\n-> Type 1 to return to the main Menu: ");
    int choice;
    scanf("%d",&choice);

     while(choice != 1) {
        printf("Wrong option, choose again: ");
        scanf("%d", &choice);
    }

}