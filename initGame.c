#include "initGame.h"

static List *listShips(int sizeBoard);
static int numberShips(int sizeBoard);

//Create user with a name, his matrix of game and list with his ships
User *initUser(char *username, int sizeBoard) {

  User *newUser = malloc(sizeof(User));

  SETUSERNAME(newUser,username); 

  SETUSERLIST(newUser, listShips(sizeBoard));

  SETUSERSTRUCTURE(newUser,initDataStructure(sizeBoard));

   return newUser;
}

/*Create a list with ships
   * Create a ship of different types in each interation(i)
   * If number of ships to insert is zero, then don't add more ships -> list is complete
*/

List *listShips(int sizeBoard) {

    int number = numberShips(sizeBoard);

    List *shipList = initList();

    int numberSmall = number * 0.15;
    int numberBig = number * 0.10;

    while(numberSmall!= 0) {

      SHIP *new = newShip(0);
      headList(shipList,new);
      SHIP *new1 = newShip(1);
      headList(shipList,new1);
      SHIP *new2 = newShip(2);
      headList(shipList, new2);
      SHIP *new3 = newShip(5);
      headList(shipList, new3);
      numberSmall--;

    }

    while(numberBig!= 0) {
      SHIP *new = newShip(6);
      headList(shipList,new);
      SHIP *new1 = newShip(4);
      headList(shipList,new1);
      SHIP *new2 = newShip(3);
      headList(shipList, new2);
      numberBig--;

    }
    
    return shipList;
}


int chooseBoardSize() {
    int size = 0;

    printf("Write the size of the board (20 <= x <= 40): ");
    scanf("%d", &size);

    while(size < 20 || size > 40) {
        printf("Write the size of the board (20 <= x <= 40): ");
        scanf("%d", &size);
    }

    system("clear");
    return size;
}

//numberShips to create
int numberShips(int sizeBoard) {

  int number = 0;

  number = (sizeBoard*sizeBoard)/(5*5);

  return number;
}


//The players choose a number and the greatest number is the start player
User *whoStartGame(User *usr1, User *usr2) {

  User *started;

  int numberUsr1, numberUsr2;

  system("clear");
  printf("User %s choose a number: \n", usr1 -> username);
  scanf("%d", &numberUsr1);
  system("clear");
  printf("User %s choose a number: \n", usr2 -> username);
  scanf("%d", &numberUsr2);

  if(numberUsr1 > numberUsr2) started = usr1;
  else if(numberUsr1 < numberUsr2) started = usr2;
  else {
    printf("The numbers are equal, choose other number\n");
    started = whoStartGame(usr1,usr2);
  }

  return started;
}


// Print name's header's on top of each matrix
void printUsers(User *start, User *other, int boardSize) {
   // system("clear");

    int count = boardSize / 2 - 7;

   for(int a=0; a < count; a++)
        printf(" ");
    printf("Matrix %s", start -> username);

    for(int a=0; a < 10 + count + (boardSize/2 - 4); a++)
        printf(" ");
    printf("Matrix %s", other -> username);

}


/*
// Free allocated memory
void freeUser(User *usr) {
    List *list = getShipList(usr);
    void *structure = getStructure(usr);
    freeList(list);
    freeDataStructure(structure);
    free(usr);
}

*/
