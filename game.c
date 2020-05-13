#include "game.h"

// Each player's turn
bool gameTurn(User *start, User *other) {

  char ch_x, ch_y;
  int x, y = 0;
  bool shotCan = false;

  bool playAgain = false;

    printUsers(start, other);
    printBothMatrix(start -> matrix, other -> matrix);
    /*
    printf("%s choose point to hit a ship of %s\n", start -> username, other -> username);
    printf("x: ");
    scanf(" %c", &ch_x);
    printf("\ny: ");
    scanf(" %c",&ch_y);
    x = choiceChar(ch_x);
    y = choiceChar(ch_y);
    */
    x = randomShoot(start -> matrix -> size);
    y = randomShoot(start -> matrix -> size);

    shotCan = canShot(other -> matrix, x,y);

    if(shotCan) {
        playAgain = shotInPlayer(start, other, x,y);
    }
    else {
        while(shotCan == false) {
        /*
          printf("Try Again\n");
          printf("%s choose point to hit a ship of %s\n", start -> username, other -> username);
          printf("x: ");
          scanf(" %c", &ch_x);
          printf("\ny: ");
          scanf(" %c",&ch_y);
          x = choiceChar(ch_x);
          y = choiceChar(ch_y);
          */
          x = randomShoot(start -> matrix -> size);
          y = randomShoot(start -> matrix -> size);

          if(shotCan) playAgain = shotInPlayer(start, other, x,y);
          else shotCan = canShot(other -> matrix, x,y);
        }
    }

    if(sinkBoatMatrix(other -> matrix)) {
        printSinkShip(other -> matrix, x, y);
        printUsers(start, other);
        printBothMatrix(start -> matrix, other -> matrix);
        printf("You sank the ship!\n");
    } else {
        printUsers(start, other);
        printBothMatrix(start -> matrix, other -> matrix);

        if(other -> matrix -> data[y][x] -> value == '*')
            printf("You hit a ship!\n");
        else if(other -> matrix -> data[y][x] -> value == '+')
            printf("You hit a empty cell!\n");
     }

    //sleep(2);

    return playAgain;
}


// Play again after hit a ship
bool playAgain(User *start, User *other) {

  bool gameTurnVar = gameTurn(start,other);
  bool broke = false;
  while(gameTurnVar) {
    gameTurnVar = gameTurn(start,other);
    if(allShipsSink(start) || allShipsSink(other)) {
      broke = true;
      break;
    }

  }

  return broke;
}

bool shotInPlayer(User* self, User* other, int x, int y) {

    bool shot = modifyValues(other -> matrix, x, y);

    modifyShot(self -> matrix, x, y, shot);

    return shot;
}


//Game development to the condition allShipsSink(user) == true
void game(User *start, User *other) {

    bool playAgainVar = false;

    while(1) {
      playAgainVar = playAgain(start, other);
      if(playAgainVar) {
        printf("||     CONGRULATIONS!     ||\n");
        printf("The player %s win the game! \n", start -> username);
        break;
      }
      playAgainVar= playAgain(other,start);
      if(playAgainVar) {
        printf("||     CONGRULATIONS!     ||\n");
        printf("The player %s win the game! \n", other -> username);
        break;
      }
    }
    // Free all allocated memory used on the game
    freeUser(start);
    freeUser(other);
}

bool allShipsSink(User *usr) {

  ListNode *node = usr -> shipList -> head;
  int countShips = usr -> shipList -> size;

  bool sink = false;

  while(node != NULL) {
    sink = sinkBoat((SHIP*)node -> data);
    if(sink) countShips--;
    node = node -> next;
  }

  if(countShips==0)
    return true;
  else
    return false;
}

// random number between 0 and matrix size to hit a cell
int randomShoot(int matrixSize) {

    int x = rand() % matrixSize;

    return x;
}

