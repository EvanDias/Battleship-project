#include <stdio.h> 
#include <stdlib.h>
#include "game.h"

#define MAX_BUFFER 1024 

User *initUser(char *nameUser) {

    User *newUser = malloc(sizeof(User));

    newUser -> nameUser = nameUser;
    //newUser -> arrayShips = arrayShips;


    return newUser;
}

SHIP **arrayWithShips()  {

    SHIP **new = malloc(sizeof(SHIP*));


}





int choiceMatrix() {

    int numberN;
    
    scanf("%d", &numberN);
    if(numberN < 10) {
        printf("Can't a matrix with that value. The value should be greater or equal than 10. Repeat, please \n");
        choiceMatrix();
    }

    return numberN;

}


void choiceMenu(int numberMenu) {

    int numberMatrix;

    if(numberMenu == 1) {
       system("clear");
       printf("Write a number of matrix (n*n, n >=10): ");
       numberMatrix = choiceMatrix();
       choiceOne();
      }

    else if(numberMenu == 2) {
        system("clear");
        printf("Rules are: \n\n");
        choiceTwo();
    }

    else if(numberMenu == 3) {
        exit(0);
    }

}


void choiceOne() {

    system("clear");

    printf("Create a user 1 \n");
    printf("Your name: ");
    char *name1 = malloc(sizeof(char)*1024);
    scanf("%s", name1);
    User *user1= initUser(name1);

    printf("\nCreate a user 2 \n");
    printf("Your name: ");
    char *name2 = malloc(sizeof(char)*1024);
    scanf("%s", name2);
    User *user2= initUser(name2);
    printf("\nUser 1: %s \n", user1 -> nameUser);
    printf("User 2: %s \n", user2 -> nameUser);
 
}


void choiceTwo() {

    char buffer[MAX_BUFFER];
    int c;
    FILE *file;
    file = fopen("rules.txt", "r");

    if(file) {
        while((c = getc(file)) != EOF) putchar(c);
          fclose(file);
    }


    /*
    printf("\n\n-> Type 1 to return to the main Menu: ");
    int choice;
    scanf("%d",&choice);

     while(choice != 1) {
        printf("Wrong option, choose again: ");
        scanf("%d", &choice);
    }
    */

}






