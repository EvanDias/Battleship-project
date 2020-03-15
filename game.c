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
       printf("Write a number of matrix (n*n, n >=10): ");
       numberMatrix = choiceMatrix();
       choiceOne();
      }

    else if(numberMenu == 2) {
        printf("Rules are: \n");
        choiceTwo();
    }
    else printf("Don't exist that option");


}

void choiceOne() {

    
        printf("Create a user 1 \n");
        printf("Your name \n");
        char *name1 = malloc(sizeof(char)*1024); 
        scanf("%s", name1);
        User *user1= initUser(name1);
        printf("User 1: %s \n", user1 -> nameUser);
        printf("Create a user 2 \n");
        printf("Your name \n");
        char *name2 = malloc(sizeof(char)*1024); 
        scanf("%s", name2);
        User *user2= initUser(name2);
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
    printf("\n");

}






