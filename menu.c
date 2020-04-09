#include <stdio.h>
#include <stdlib.h>
#include "menu.h"


void mainMenu() {

    //system("clear");

    printf("------------------------------------------------ \n");
    printf("            WELCOME TO BATTLESHIP                \n");
    printf("------------------------------------------------ \n");

    printf("\n");

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

    choiceMenu(choice_menu);
}



// Start game
void choiceOne() {

    system("clear");

    int sizerMatrix = chooseMatrixSize();

    printf("Create a user 1 \n");
    printf("Your name: ");
    char *name1 = malloc(sizeof(char)*1024);
    scanf("%s", name1);
    User *user1 = initUser(name1,sizerMatrix);

    printf("\nCreate a user 2 \n");
    printf("Your name: ");
    char *name2 = malloc(sizeof(char)*1024);
    scanf("%s", name2);
    User *user2= initUser(name2,sizerMatrix);



    printf("\nUser 1: %s \n", user1 -> username);
    printf("User 2: %s \n", user2 -> username);

        /*
        ListNode *node = user1 -> shipList -> head;
        while(node != NULL) {
            printBitMap(node -> ship -> bp);
            printf("\n");
            node = node -> next;
        }
        */


    //printMatrix(user1 -> matrix);
    //initializeGame(user1, user2, sizerMatrix);
    choiceShips(user1);
    choiceShips(user2);
}



// See rules of the game
void choiceTwo() {

    char buffer[MAX_BUFFER];
    int c;

    FILE *file;
    file = fopen("rules.txt", "r");

    if(file) {
        while((c = getc(file)) != EOF) putchar(c);
            fclose(file);
    }

    printf("\n\n-> Type 1 to return to the main Menu: ");
    int choice;
    scanf("%d",&choice);

     while(choice != 1) {
        printf("Wrong option, choose again: ");
        scanf("%d", &choice);
    }

    mainMenu();

}



// Chosen option of the mainMenu()
void choiceMenu(int numberMenu) {

    int numberMatrix;

    if(numberMenu == 1) {
       choiceOne();
      }

    else if(numberMenu == 2) {
        system("clear");
        printf("Rules are: \n\n");
        choiceTwo();
    }

    else if(numberMenu == 3) { // Close the program
        exit(0);
    }
}


void choiceShips(User *user) {

    ListNode *node = user -> shipList -> head;
    int x,y, degrees;

    for(int i=0; i<5; i++) {
    //while(user -> shipList -> size != 0) {

        printf("Choose a translation of ship KIND\n");
        printf("x: ");
        scanf("%d", &x);
        printf("\ny: ");
        scanf("%d",&y);

        translation(node -> ship, y, x);




        printf("Choose a rotation to the ship KIND\n");
        printf("Degrees: ");
        scanf("%d", &degrees);

        rotation(node -> ship, degrees);

        printf("Ponto refenrecia: \n");


        printf("x: ");
        scanf("%d", &x);
        printf("\ny: ");
        scanf("%d",&y);



        bool inserted = insertShipInMatrix(user -> matrix, node -> ship, x, y);

        while(inserted == false) {
            printf("x: ");
            scanf("%d", &x);
            printf("\ny: ");
            scanf("%d",&y);

            inserted = insertShipInMatrix(user -> matrix, node -> ship, x, y);
        }

        printf("translationx: %d || translationy: %d || rotation: %d\n", node -> ship -> translationx,node -> ship -> translationy, node -> ship -> rotation );
        node = node -> next;

        printMatrix(user -> matrix);

    }


/*
    ListNode *node = user1 -> shipList -> head;
        while(node != NULL) {
            printBitMap(node -> ship -> bp);
            printf("\n");
            node = node -> next;
        }
        */



}





