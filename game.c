#include "game.h"

bool canShot(Matrix *matrix, int x, int y) {

  bool shot = true;

        if(y >= matrix -> size || x >= matrix -> size) {
          shot = false;
        }

        else if(matrix -> data[y][x] -> value == 'x' || matrix -> data[y][x] -> value == '.')
                  shot = true;
                  
        else if(matrix -> data[y][x] -> value == '*' || matrix -> data[y][x] -> value == '#')
                  shot = false;
    return shot;
}


bool shotInPlayer(Matrix *self, Matrix *other, int x, int y) {

    bool shotMatrix = false;
      
      if(other -> data[y][x] -> value == 'x') {
        
        //value of matrix become *
        other -> data[y][x] -> value = '*';
        other -> data[y][x] -> ship -> shotCount--;
        printf("ShotCount = %d of %d", other -> data[y][x] -> ship -> shotCount, other -> data[y][x] -> ship -> kind);
        //change value bitmap to ship 2
        changeValueShotBp(other,x,y,'2');
        //shot of self matrix become 2
        self -> data[y][x] -> shot = '2';
        printf("Your hit a  cell of a ship\n");
        shotMatrix = true;
      }
      else if(other -> data[y][x] -> value == '.') {
        //o value of matrix become +
        other -> data[y][x] -> value = '+';
        //shot of self matrix become 1
        self -> data[y][x] -> shot = '1';
        printf("You hit a empty cell\n");
        shotMatrix = false;
      }

      return shotMatrix;

}
bool gameTurn(User *start, User *other) {

  char ch_x, ch_y;
  int x, y = 0;
  bool shotCan = false;

  bool playAgain = false;

    printUsers(start, other);
    printBothMatrix(start -> matrix, other -> matrix);

    
    printf("%s choose point to hit a ship of %s\n", start -> username, other -> username);
    printf("x: ");
    scanf(" %c", &ch_x);
    printf("\ny: ");
    scanf(" %c",&ch_y);
    x = choiceChar(ch_x);
    y = choiceChar(ch_y);
    

    //x = randomShoot(start -> matrix -> size);
    //y = randomShoot(start -> matrix -> size);

    shotCan = canShot(other -> matrix, x,y);

    if(shotCan) {
      playAgain = shotInPlayer(start -> matrix, other -> matrix, x,y);
    }

    else {
    while(shotCan == false) {
      
      printf("Try Again\n");
      printf("%s choose point to hit a ship of %s\n", start -> username, other -> username);
      printf("x: ");
      scanf(" %c", &ch_x);
      printf("\ny: ");
      scanf(" %c",&ch_y);
      x = choiceChar(ch_x);
      y = choiceChar(ch_y);
        
     //   x = randomShoot(start -> matrix -> size);
       // y = randomShoot(start -> matrix -> size);

        if(shotCan) playAgain = shotInPlayer(start -> matrix, other -> matrix, x,y);
        else shotCan = canShot(other -> matrix, x,y);
    }
  }

    if(sinkBoatMatrix(other -> matrix)) {
        printSinkShip(other -> matrix, x, y);
        printUsers(start, other);
        printBothMatrix(start -> matrix, other -> matrix);
        sleep(2);
    } else {
        printUsers(start, other);
        printBothMatrix(start -> matrix, other -> matrix);
        sleep(2);
     }

    return playAgain;
}


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

    freeUser(start);
    freeUser(other);
}


bool sinkBoat(SHIP *ship) {

    bool sinkBoatV = false;

    if(ship -> shotCount == 0) sinkBoatV = true;

    return sinkBoatV;
}

bool sinkBoatMatrix(Matrix *x) {
    for(int i = 0; i < x -> size; i++) {
      for(int j = 0; j < x -> size; j++) {
        if(x -> data[j][i] -> value == '*') {
          if(sinkBoat(x -> data[j][i] -> ship)==true) {
            printf("Sink a boat with coordenates (%d,%d) \n", j,i);
            return true;
        }
      }
    }
  }
  return false;
}


bool allShipsSink(User *usr) {

  ListNode *node = usr -> shipList -> head;
  int countShips = usr -> shipList -> size;

  bool sink = false;

  while(node != NULL) {
    sink = sinkBoat(node -> ship);
    if(sink) countShips--;
    node = node -> next;
  }

  if(countShips==0)
    return true;
  else
    return false;
}


int randomShoot(int matrixSize) {

    int x = rand() % matrixSize;

    return x;
}

