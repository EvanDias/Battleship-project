#include "menu.h"

void mainMenu() {

    system("clear");

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

    //int sizerMatrix = 12;

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


void initializedGame(User *usr1, User *usr2) {

  system("clear");

  //aqui
  printMatrix(usr1 -> matrix);
  printf("User %s do you would like delete some ship?\n",usr1 -> username);
  printf("1)YES\n");
  printf("2)NO \n");
  int choose;
  scanf("%d", &choose);
  
  int x,y = 0;
  char ch_x, ch_y;
  while(choose == 1) {
    printf("Choose the coordenate's ship to delete\n");
    printf("x: ");
    scanf(" %c", &ch_x);
    printf("\ny: ");
    scanf(" %c",&ch_y);
    x = choiceChar(ch_x);
    y = choiceChar(ch_y);
    bool deleted = deleteListMatrix(usr1, x, y);
    
    while(deleted == false) {
      printf("Don't exist a ship in this point. Choose other\n");
      printf("x: ");
      scanf(" %c", &ch_x);
      printf("\ny: ");
      scanf(" %c",&ch_y);
      x = choiceChar(ch_x);
      y = choiceChar(ch_y);
      deleted = deleteListMatrix(usr1, x, y);
    }

    printf("Do you want delete any ship?\n");
    printf("1)YES\n");
    printf("2)NO \n");
    scanf("%d", &choose);
  }
int chooseother;
if (choose == 2) {
  //aqui
  printMatrix(usr2 -> matrix);
  printf("User %s do you would like delete some ship?\n",usr2 -> username);
  printf("1)YES\n");
  printf("2)NO \n");
  
  scanf("%d", &chooseother);
  
 int x,y = 0;
 char ch_x, ch_y;
  while(chooseother == 1) {
    printf("Choose the coordenate's ship to delete\n");
    printf("x: ");
    scanf(" %c", &ch_x);
    printf("\ny: ");
    scanf(" %c",&ch_y);
    x = choiceChar(ch_x);
    y = choiceChar(ch_y);
    bool deleted = deleteListMatrix(usr2, x, y);
    
    while(deleted == false) {
      printf("Don't exist a ship in this point. Choose other\n");
      printf("x: ");
      scanf(" %c", &ch_x);
      printf("\ny: ");
      scanf(" %c",&ch_y);
      x = choiceChar(ch_x);
      y = choiceChar(ch_y);
      deleted = deleteListMatrix(usr2, x, y);
    }

    printf("Do you want delete any ship?\n");
    printf("1)YES\n");
    printf("2)NO \n");
    scanf("%d", &chooseother);
  } 
}

  if (chooseother == 2) {

    system("clear");
    printf(" -------------START GAME------------- \n");
    User *started = whoStartGame(usr1,usr2);

    printf("User %s - you start a game \n", started -> username);

    if(started == usr1) game(usr1,usr2);
    else if (started == usr2) game(usr2,usr1);

  }

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



/*Scanf of points choosed by user to do translation
  *
  *
*/
void scanPointsTranslation(ListNode *node) {

  int x, y = 0;
  char *kind = "";
  if(node -> ship -> kind != 4 && node -> ship -> kind != 6) {
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


/*Scanf of points choosed by user to do rotation
  *
  *
*/
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


}


/*Scanf of points choosed by user to do insert ship in matrix
  *
  *
*/

void scanPointInsert(ListNode *node, Matrix *matrix) {

  int x,y = 0;

  char * kind = nameShip(node -> ship);
  char ch_x, ch_y;

  printf("Choose a point to insert %s in matrix\n",kind );
      printf("x: ");
      scanf(" %c", &ch_x);
      printf("\ny: ");
      scanf(" %c",&ch_y);
      x = choiceChar(ch_x);
      y = choiceChar(ch_y);

  bool inserted = insertShipInMatrix(matrix, node -> ship, x, y);

  while(inserted == false) {
      printf("Try again !\n");
      printf("x: ");
      scanf(" %c", &ch_x);
      printf("\ny: ");
      scanf(" %c",&ch_y);
      x = choiceChar(ch_x);
      y = choiceChar(ch_y);
      inserted = insertShipInMatrix(matrix, node -> ship, x, y);
  }

}


void choiceModeGame(User *user) {
      system("clear");

      int numberChoice = 0;
      printf("%s choose a mode game\n", user -> username);
      printf("1 - Manual Setup\n");
      printf("2 - Randomize Setup\n");
      printf("3 - Manual/Randomize Setup \n");
      printf("4 - Return principal menu\n");
      printf("Option: ");
      scanf("%d", &numberChoice);
      printf("\n");

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



//if user want to manual and random ship
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


//function auxiliar
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


//choose ships random
void choiceShipsAuto(User *user) {

    ListNode *node = user -> shipList -> head;

    int size = user -> matrix -> size;

    int agreed;

    while(node != NULL) {
      randomTranslation(node);
      randomRotation(node);
      randomInsertMatrix(node, user -> matrix);

      node =  node -> next;

      //aqui
      printMatrix(user -> matrix);

    }

    printf("Do you accept this matrix?\n");
    printf("1) YES\n");
    printf("2) NO \n");
    scanf("%d",&agreed);

    //deleteShip(user);

    switch(agreed) {
      case 1: break;
      case 2: user -> matrix = initMatrix(size);
            choiceShipsAuto(user);
            break;
      default: printf("Try other number\n");
            scanf("%d",&agreed);

    }
}

//choose ships manual

void choiceShipsManual(User *user) {

    ListNode *node = user -> shipList -> head;

      while(node != NULL) {
        scanPointsTranslation(node);
        scanPointRotation(node);
        printBitMap(node -> ship -> bp);
        printf("\n");
        scanPointInsert(node, user -> matrix);

        node =  node -> next;

        //aqui
        printMatrix(user -> matrix);

      }
  }

bool deleteListMatrix(User *usr, int x, int y) {

    bool deleted = false;
    ShipKind kind;
    if(usr -> matrix -> data[y][x] -> ship != NULL) {
        kind = usr -> matrix -> data[y][x] -> ship -> kind;
        removeNode(usr -> shipList, usr -> matrix -> data[y][x] -> ship);
        deleteShipMatrix(usr -> matrix, usr -> matrix -> data[y][x] -> ship , x, y);
        deleted = true;
    }
    else deleted = false; 

    if(deleted) {

      SHIP *new = newShip(kind);
      headList(usr -> shipList, new);
      ListNode *node = usr -> shipList -> head;
      scanPointsTranslation(node);
      scanPointRotation(node);
      scanPointInsert(node, usr -> matrix);
    }

    return deleted;
}
