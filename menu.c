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

    int sizeBoard = chooseBoardSize();

    //int sizerMatrix = 12;


    printf("Create a user 1 \n");
    printf("Your name: ");
    char *name1 = malloc(1024 * sizeof(char));
    scanf("%s", name1);
    User *user1 = initUser(name1,sizeBoard);
 
    printf("\nCreate a user 2 \n");

    printf("Your name: ");
    char *name2 = malloc(1024 * sizeof(char));
    scanf("%s", name2);
    User *user2= initUser(name2,sizeBoard);

    choiceModeGame(user1, sizeBoard);
    choiceModeGame(user2, sizeBoard);

    initializedGame(user1, user2, sizeBoard);
}



void initializedGame(User *usr1, User *usr2, int boardSize) {
  system("clear");

  int x,y = 0;
  char ch_x, ch_y;

  printBoard(usr1, boardSize);
  printf("User %s do you would like delete some ship?\n",usr1 -> username);
  printf("1)YES\n");
  printf("2)NO \n");
  printf("Option: ");
  int choose;
  scanf("%d", &choose);

  while(choose == 1) {
    printf("Choose the coordenate's ship to delete\n");
    printf("x: ");
    scanf(" %c", &ch_x);
    printf("\ny: ");
    scanf(" %c",&ch_y);
    x = choiceChar(ch_x);
    y = choiceChar(ch_y);
    bool deleted = deleteListShip(usr1, x, y, boardSize);

    while(deleted == false) {
      printf("Don't exist a ship in this point. Choose other\n");
      printf("x: ");
      scanf(" %c", &ch_x);
      printf("\ny: ");
      scanf(" %c",&ch_y);
      x = choiceChar(ch_x);
      y = choiceChar(ch_y);
      deleted = deleteListShip(usr1, x, y, boardSize);
    }

    system("clear");
    printBoard(usr1, boardSize);

    printf("Do you want delete any ship?\n");
    printf("1)YES\n");
    printf("2)NO \n");
    scanf("%d", &choose);
  }
  int chooseother;

  if (choose == 2) {
    system("clear");
    printBoard(usr1, boardSize);
    printf("User %s do you would like delete some ship?\n",usr2 -> username);
    printf("1)YES\n");
    printf("2)NO \n");
    printf("Option: ");
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
    bool deleted = deleteListShip(usr2, x, y , boardSize);

    while(deleted == false) {
      printf("Don't exist a ship in this point. Choose other\n");
      printf("x: ");
      scanf(" %c", &ch_x);
      printf("\ny: ");
      scanf(" %c",&ch_y);
      x = choiceChar(ch_x);
      y = choiceChar(ch_y);
      deleted = deleteListShip(usr2, x, y, boardSize);
    }

    //system("clear");
    printBoard(usr2, boardSize);

    printf("Do you want delete any ship?\n");
    printf("1)YES\n");
    printf("2)NO \n");
    scanf("%d", &chooseother);
  }
}

  if (chooseother == 2) {

    //system("clear");
    printf(" -------------START GAME------------- \n");
    User *started = whoStartGame(usr1,usr2);

    printf("entrei\n");

    printf("User %s - you start a game \n", started -> username);

    if(started == usr1) game(usr1,usr2, boardSize);
    else if (started == usr2) game(usr2,usr1, boardSize);

  }

}


// See the rules of the game
void choiceTwo() {
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



// Scanf of points choosed by user to do translation
void scanPointsTranslation(ListNode *node) {

  int x, y = 0;
  char *kind = nameShip((SHIP*)node -> data);
  if(kind != "L_GUY" && kind != "S_GUY") {
    printf("Choose the points to do translation of %s \n", kind);
    printf("x: ");
    scanf("%d", &x);
    printf("\ny: ");
    scanf("%d",&y);

  }

    bool translate = translation((SHIP*)node -> data, y, x);

    while(translate == false) {
      printf("Try Again: \n");
      printf("x: ");
      scanf("%d", &x);
      printf("\ny: ");
      scanf("%d",&y);
      translate = translation((SHIP*)node -> data, y, x);
    }

}


// Scanf of points choosed by user to do rotation
void scanPointRotation(ListNode *node) {

  int degrees = 0;

  char * kind = nameShip((SHIP*)node -> data);
  printf("Choose the angle to do rotation of %s \n", kind);
  printf("Degrees: ");
  scanf("%d", &degrees);

  while(degrees % 90 != 0) {
    printf("Try again: ");
    scanf("%d", &degrees);
  }

  rotation((SHIP*)node -> data, degrees);


}


// Scanf of points choosed by user to do insert ship in matrix
void scanPointInsert(User *user, ListNode *node, int boardSize) {

  int x,y = 0;

  char * kind = nameShip((SHIP*)node -> data);
  char ch_x, ch_y;

  bool inserted = false;


  printf("Choose a point to insert %s in matrix\n",kind );
      printf("x: ");
      scanf(" %c", &ch_x);
      printf("\ny: ");
      scanf(" %c",&ch_y);
      x = choiceChar(ch_x);
      y = choiceChar(ch_y);

  
    inserted = insertShipInStructure(user, (SHIP*)node -> data,x,y, boardSize);

  while(inserted == false) {
      printf("Try again !\n");
      printf("x: ");
      scanf(" %c", &ch_x);
      printf("\ny: ");
      scanf(" %c",&ch_y);
      x = choiceChar(ch_x);
      y = choiceChar(ch_y);
      inserted = insertShipInStructure(user,(SHIP*)node -> data, x, y, boardSize);
  }

}

void choiceModeGame(User *user, int boardSize) {
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
        case 1: choiceShipsManual(user, boardSize);
              break;
        case 2: choiceShipsAuto(user, boardSize);
              break;
        case 3: choiceShips(user, boardSize);
              break;
        case 4: mainMenu();
              break;
        default: choiceModeGame(user, boardSize);
              break;
      }
}



// If user want to chose manual and random ship
void choiceShips(User *user, int boardSize) {

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
         // printBitMap(node -> ship -> bp);
          printf("\n");
          insertMode(user, node, boardSize);
          break;
        case 2: randomTranslation(node);
          randomRotation(node);
         // printBitMap((SHIP*)(node -> data) -> bp);
          printf("\n");
          insertMode(user, node, boardSize);
          break;

        default: printf("Try again \n");
          scanf("%d", &choice);
          break;
      }

      node = node -> next;
    }
}


// Auxiliar function
void insertMode(User *user, ListNode *node, int boardSize) {

  int insertMode = 0;

  printf("How %s want to insert ship? \n", user -> username);
  printf("1) MANUAL\n");
  printf("2) AUTO\n");
  scanf("%d",&insertMode);

  switch (insertMode) {
    case 1: scanPointInsert(user,node,boardSize);
            printBoard(user, boardSize);
            break;
    case 2: randomInsert(node,user, boardSize);
            printBoard(user, boardSize);
            break;

    default: printf("Try again \n");
      scanf("%d", &insertMode);
      break;
  }
}


// Choose ships random
void choiceShipsAuto(User *user, int boardSize) {

    ListNode *node = user -> shipList -> head;

    int agreed = 0;

    void *structure = initDataStructure(boardSize);

    while(node != NULL) {
      randomTranslation(node);
      randomRotation(node);
      randomInsert(node, user, boardSize);

      node =  node -> next;
    }
    system("clear");
    printBoard(user, boardSize);

    printf("Do you accept this matrix?\n");
    printf("1) YES\n");
    printf("2) NO \n");
    printf("Option: ");
    scanf("%d",&agreed);

    //deleteShip(user);

    switch(agreed) {
      case 1: break;
      case 2: setStructure(user, structure);
              choiceShipsAuto(user,boardSize);
            break;
      default: printf("Try other number\n");
            printf("Option: ");
            scanf("%d",&agreed);

    }
}


// Choose ships manual
void choiceShipsManual(User *user, int boardSize) {

    ListNode *node = user -> shipList -> head;

      while(node != NULL) {
        scanPointsTranslation(node);
        scanPointRotation(node);
        SHIP* ship = (SHIP*)node -> data;
        printBitMap(ship -> bp);
        printf("\n");
        scanPointInsert(user,node,boardSize);

        node =  node -> next;

        printBoard(user, boardSize);

      }
  }



bool deleteListShip(User *usr, int x, int y, int boardSize) {

    bool deleted = false;
   
    ShipKind kind;
    void *structure = getStructure(usr);
    Point *p = newPoint(x,y);

    Cell *aux = searchPoint(structure,p);

    if(aux != NULL) {
      int size = activatePoints(getShipCell(aux)) -> size;

      kind = getShipKind(getShipCell(aux));
      deleteShip(structure,p,size);
      removeNode(usr -> shipList, getShipCell(aux));
      deleted = true;

      BitMap *bp = getBitMapShip(getShipCell(aux));

      for(int i = 0; i < sizeBitMap; i++) {
        for(int j = 0; j < sizeBitMap; j++) {
          unsigned char data = getCellBitMap(bp,i,j); 
          if(data == 1) {
            Point *p1 = newPoint(x+i,y+j);
            void *aux1 = searchPoint(structure, p1);
            if(aux1 != NULL) {
                Cell *cell = (Cell*)aux;
                free(cell); 
            }
          }
        }
      }  

    }

    if(deleted) {

     SHIP *new = newShip(kind); 

     headList(usr -> shipList, new); 

    ListNode *node = usr -> shipList -> head;
    scanPointsTranslation(node);
    scanPointRotation(node);
    scanPointInsert(usr, node,boardSize);

    }

    free(p); 

    printf("%d\n",deleted);

    return deleted;
}
