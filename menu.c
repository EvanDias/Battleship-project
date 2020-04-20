#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

    //int sizerMatrix = chooseMatrixSize();

    int sizerMatrix = 8;

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

    choiceModeGame(user1);
    choiceModeGame(user2);

    initializedGame(user1, user2);
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

void scanPointsTranslation(ListNode *node) {

  int x, y = 0;
  char *kind = "";
  if(node -> ship -> kind != 4) {
    kind = nameShip(node -> ship);
    printf("Choose the points to do translation of %s \n", kind);
    printf("x: ");
    scanf("%d", &x);
    printf("\ny: ");
    scanf("%d",&y);

  }

    bool translate = translation(node -> ship, y, x);

    while(translate == false) {
      printf("Try Again: \n");
      printf("x: ");
      scanf("%d", &x);
      printf("\ny: ");
      scanf("%d",&y);
      translate = translation(node -> ship, y, x);
    }

}

void scanPointRotation(ListNode *node) {

  int degrees = 0;

  char * kind = nameShip(node -> ship);
  printf("Choose the angle to do rotation of %s \n", kind);
  printf("Degrees: ");
  scanf("%d", &degrees);

  while(degrees % 90 != 0) {
    printf("Try again: ");
    scanf("%d", &degrees);
  }

  bool rotate = rotation(node -> ship, degrees);

   /*
  while(rotate == false) {
    printf("Try Again: \n");
    printf("Degrees: ");
    scanf("%d", &degrees);
    rotate = rotation(node -> ship, degrees);
  }*/

}

void scanPointInsert(ListNode *node, Matrix *matrix) {

  int x,y = 0;

  char * kind = nameShip(node -> ship);

  printf("Choose a point to insert %s in matrix\n",kind );
  printf("x: ");
  scanf("%d", &x);
  printf("\ny: ");
  scanf("%d",&y);

  bool inserted = insertShipInMatrix(matrix, node -> ship, x, y);

  while(inserted == false) {
      printf("Try again !\n");
      printf("x: ");
      scanf("%d", &x);
      printf("\ny: ");
      scanf("%d",&y);
      inserted = insertShipInMatrix(matrix, node -> ship, x, y);
  }

}


void choiceModeGame(User *user) {

      int numberChoice = 0;
      printf("%s choose a mode game\n", user -> username);
      printf("1 - Manual Setup\n");
      printf("2 - Randomize Setup\n");
      printf("3 - Manual/Randomize Setup \n");
      printf("4 - Return principal menu\n");
      scanf("%d", &numberChoice);

      switch (numberChoice) {
        case 1: choiceShipsManual(user);
              break;
        case 2: choiceShipsAuto(user);
              break;
        case 3: choiceShips(user);
              break;
        case 4: mainMenu();
              break;
        default: choiceModeGame(user);
              break;
      }

}


void choiceShips(User *user) {

    ListNode *node = user -> shipList -> head;
    int choice;

    while(node != NULL) {
      printf("How %s want to do a ship?\n", user -> username);
      printf("1) MANUAL\n");
      printf("2) AUTO \n");
      scanf("%d", &choice);
      switch(choice) {
        case 1: scanPointsTranslation(node);
          scanPointRotation(node);
          printBitMap(node -> ship -> bp);
          printf("\n");
          insertMode(user);
          break;
        case 2: randomTranslation(node);
          randomRotation(node);
          printBitMap(node -> ship -> bp);
          printf("\n");
          insertMode(user);
          break;

        default: printf("Try again \n");
          scanf("%d", &choice);
          break;
      }

      node = node -> next;
    }
}

void insertMode(User *user) {


  ListNode *node = user -> shipList -> head;
  int insertMode;

  printf("How %s want to insert ship? \n", user -> username);
  printf("1) MANUAL\n");
  printf("2) AUTO\n");
  scanf("%d",&insertMode);

  switch (insertMode) {
    case 1: scanPointInsert(node, user -> matrix);
            printMatrix(user -> matrix);
            break;
    case 2: randomInsertMatrix(node, user -> matrix);
            printMatrix(user -> matrix);
            break;

    default: printf("Try again \n");
      scanf("%d", &insertMode);
      break;
  }

  }

void choiceShipsAuto(User *user) {

    ListNode *node = user -> shipList -> head;

    int size = user -> matrix -> size;

    int agreed;

    while(node != NULL) {
      randomTranslation(node);
      randomRotation(node);
      randomInsertMatrix(node, user -> matrix);

      node =  node -> next;

      printMatrix(user -> matrix);

    }

    printf("Do you accept this matrix?\n");
    printf("1) YES\n");
    printf("2) NO \n");
    scanf("%d",&agreed);

    switch(agreed) {
      case 1: break;
      case 2: user -> matrix = initMatrix(size);
            choiceShipsAuto(user);
            break;
      default: printf("Try other number\n");
            scanf("%d",&agreed);

    }
}

void choiceShipsManual(User *user) {

    ListNode *node = user -> shipList -> head;

      while(node != NULL) {
        scanPointsTranslation(node);
        scanPointRotation(node);
        printBitMap(node -> ship -> bp);
        printf("\n");
        scanPointInsert(node, user -> matrix);

        node =  node -> next;

        printMatrix(user -> matrix);

      }
  }

