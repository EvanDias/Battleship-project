#include "game.h"


void initializedGame(User *usr1, User *usr2) {

  system("clear");

  printf(" -------------START GAME------------- \n");
  User *started = whoStartGame(usr1,usr2);

  printf("User %s - you start a game \n", started -> username);

  if(started == usr1) game(usr1,usr2);
  else if (started == usr2) game(usr2,usr1);


}

bool canShot(Matrix *matrix, int x, int y) {

  bool shot = true;
 

        if(y >= matrix -> size || x >= matrix -> size) {
          shot = false;
        
        }
        else if(matrix -> data[y][x] -> value == 'x' || matrix -> data[y][x] -> value == '.') 
                  shot = true;
                

    return shot;
}



bool shotInPlayer(Matrix *self, Matrix *other, int x, int y) {

    bool shot = canShot(other,x,y);
    bool shotMatrix = false;


    if(shot) {
      if(other -> data[y][x] -> value == 'x') {
        //value of matrix become *
        other -> data[y][x] -> value = '*';
        other -> data[y][x] -> ship -> shotCount--;
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
        //shot of self matrix become 2
        self -> data[y][x] -> shot = '1';
        printf("You hit a empty cell\n");
        shotMatrix = true;
      }
  }

  return shotMatrix;
}

//user move
void gameTurn(User *start, User *other) {

  char ch_x, ch_y;
  int x, y = 0;
  bool shotMatrix = false;

    printUsers(start, other);
    printBothMatrix(start -> matrix, other -> matrix);

    printf("%s choose point to hit a ship of %s\n", start -> username, other -> username);
    printf("x: ");
    scanf(" %c", &ch_x);
    printf("\ny: ");
    scanf(" %c",&ch_y);

    x = choiceChar(ch_x);

    y = choiceChar(ch_y);


    shotMatrix = shotInPlayer(start -> matrix, other -> matrix,x,y);

    while(shotMatrix == false) {
      printf("Try Again\n");
      printf("%s choose point to hit a ship of %s\n", start -> username, other -> username);
      printf("x: ");
      scanf(" %c", &ch_x);
      printf("\ny: ");
      scanf(" %c",&ch_y);

      x = choiceChar(ch_x);
      y = choiceChar(ch_y);

      shotMatrix = shotInPlayer(start -> matrix, other -> matrix, x,y);
    }


    printUsers(start, other);
    printBothMatrix(start -> matrix, other -> matrix);
    sleep(2);

    if(sinkBoatMatrix(other -> matrix))
        printSinkShip(other -> matrix, x, y);
 

   

}

//Game development to the condition allShipsSink(user) == true

void game(User *start, User *other) {
  

    while(1) {

    gameTurn(start, other); 
     if(allShipsSink(start) || allShipsSink(other)) {
        printf("||     CONGRULATIONS!     ||\n");
        printf("The player %s win the game! \n", start -> username);
        break;
    }
    gameTurn(other,start);

     if(allShipsSink(start) || allShipsSink(other)) {
        printf("||     CONGRULATIONS!     ||\n");
        printf("The player %s win the game! \n", start -> username);
        break;
    }
    }
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
  int countShips = numberShips(usr -> matrix -> size);

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

