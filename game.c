#include "game.h"

bool gameTurn(User *start, User *other, int boardSize) {
  system("clear");
  char ch_x, ch_y;
  int x, y = 0;
  bool shotCan = false;


  void *structureOther = USERSTRUCTURE(other);
  bool gamePlayed = false;

  printUsers(start, other, boardSize);
  printBothBoard(start, other, boardSize);
  
  
   printf("%s choose point to hit a ship of %s\n", USERNAME(start), USERNAME(other));
    printf("x: ");
    scanf(" %c", &ch_x);
    printf("\ny: ");
    scanf(" %c",&ch_y);
    x = choiceChar(ch_x);
    y = choiceChar(ch_y);


    //x = randomShoot(boardSize);
    //y = randomShoot(boardSize);

    shotCan = canShot(other,x,y,boardSize);

    if(shotCan) {
          gamePlayed = shotPlayer(other, x,y);
          modifyValuesStruct(other,x,y);
          insertLittleCell(start,x,y);
          if(gamePlayed) modifyShotsStruct(other,x,y,true); 
          else  modifyShotsStruct(other,x,y,false);

    }
    else {
        while(shotCan == false) {
      
           printf("Try Again\n");
          printf("%s choose point to hit a ship of %s\n", USERNAME(start), USERNAME(other));
          printf("x: ");
          scanf(" %c", &ch_x);
          printf("\ny: ");
          scanf(" %c",&ch_y);
          x = choiceChar(ch_x);
          y = choiceChar(ch_y);
         
        //x = randomShoot(boardSize);
        //y = randomShoot(boardSize);

      

          if(shotCan) {
            gamePlayed = shotPlayer(other, x,y);
            modifyValuesStruct(other,x,y);
            insertLittleCell(start,x,y);
          }
          else shotCan = canShot(start,x, y, boardSize);
    }
    }

    if(sinkBoatStructure(structureOther, boardSize)) {
        system("clear");
        printUsers(start, other, boardSize);
        printBothBoard(start, other, boardSize);
        printf("You sank the ship!\n");
    } else {
        system("clear");
        printUsers(start, other, boardSize);
        printBothBoard(start, other,boardSize);
        //printBoard(start, boardSize);
        //printBoard(other, boardSize);
        Point *p = newPoint(x,y);
        void *aux = searchPoint(structureOther,p);
        if(aux == NULL) printf("pois\n");
        
        else {
          Cell *cell = (Cell*)aux;
        if(CELLVALUE(cell) == '*')
            printf("You hit a ship!\n");
        else if(CELLVALUE(cell) == '+')
            printf("You hit a empty cell!\n");
     }
    }
  
    sleep(2);

    return gamePlayed;
}


// Play again after hit a ship
bool gamePlayed(User *start, User *other, int boardSize) {

  bool gameTurnVar = gameTurn(start,other, boardSize);
  bool broke = false;
  while(gameTurnVar) {
    gameTurnVar = gameTurn(start,other, boardSize);
    if(allShipsSink(start) || allShipsSink(other)) {
      broke = true;
      break;
    }

  }

  return broke;
}

//Game development to the condition allShipsSink(user) == true
void game(User *start, User *other, int boardSize) {

    bool playAgainVar = false;

    while(1) {
      playAgainVar = gamePlayed(start, other, boardSize);
      if(playAgainVar) {
        printf("||     CONGRULATIONS!     ||\n");
        printf("The player %s win the game! \n", USERNAME(start));
        break;
      }
      playAgainVar= gamePlayed(other,start, boardSize);
      if(playAgainVar) {
        printf("||     CONGRULATIONS!     ||\n");
        printf("The player %s win the game! \n", USERNAME(other));
        break;
      }
    }
    // Free all allocated memory used on the game
    //freeUser(start);
    //freeUser(other);
}

   

bool allShipsSink(User *usr) {

  printf("Entrie no alShipsSink\n");

  ListNode *node = usr -> shipList -> head;
  int countShips = USERLIST(usr) -> size;

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

bool canShot(User *usr, int x, int y, int boardSize) {


  printf("x: %d   y: %d\n ",x,y);
  bool shot = true; 
  void *structure = USERSTRUCTURE(usr); 

  Point *p = newPoint(x,y);

    if(y >= boardSize || x >= boardSize) {
       shot = false;
      return shot;
    }

  void *aux = searchPoint(structure,p);

     if(aux == NULL) {
      aux = initCell(); 
      insertShip(structure, aux,p);
      shot = true;
    }

    else {
      Cell *cell = (Cell*)aux;

      if(CELLVALUE(cell) == 'x' || CELLVALUE(cell) == '.') shot = true;

      else if(CELLVALUE(cell) == '*' || CELLVALUE(cell) == '#') shot = false;

    }   

    return shot;
}

bool shotPlayer(User *user, int x, int y) {

  bool shot = false;

    printf("x: %d    y: %d\n",x,y);

    Point *p = newPoint(x,y);

    void *structure = USERSTRUCTURE(user);
    void *aux = searchPoint(structure,p);
    
    if(aux != NULL) {
      Cell *cell = (Cell*)aux;
      shot = hittedPiece(cell);
      printf("SHOT: %d\n", shot);

    }

    else printf("NULA\n");

    return shot;
  
}


bool sinkBoatStructure(void *structure, int boardSize) {

    for(int i = 0; i < boardSize; i++) {
      for(int j = 0; j < boardSize; j++) {
        Point *p = newPoint(i,j);
        void *aux = searchPoint(structure,p);
          if(aux != NULL) {
            Cell *cell = (Cell*)aux;
            if(CELLVALUE(cell) == '*') {
              SHIP *sh = SHIPCELL(cell);
              if(sinkBoat(sh)==true) {
                printf("Sink a boat with coordenates (%d,%d) \n", j,i);
                return true;
              }
          }
        }
        free(p);
      }

    }


  return false;

}



void modifyValuesStruct(User *user, int x, int y) {

  printf("user : %s\n", user -> username);
  void *structure = USERSTRUCTURE(user);

  Point *p = newPoint(x,y);
  
  void *aux = searchPoint(structure,p); 

  if(aux != NULL) {

    Cell *cell = (Cell*)aux;
    modifyValues(cell,x,y);

  }
  

}


void modifyShotsStruct(User *user, int x, int y, bool b) {

  void *structure = USERSTRUCTURE(user);
  Point *p = newPoint(x,y);
  
  void *aux = searchPoint(structure,p); 
  if(aux != NULL) {
    modifyShot((Cell*)aux,b);
}
}


bool canInsert(User *user, SHIP *ship, int x, int y, int boardSize) {

    bool insert = true;
    int broke = 0;

    //printf("user %s", user -> username);

    void *structure = user -> dataStructs;

    //printBoard(user, boardSize);

    BitMap *bp = SHIPBITMAP(ship);

    for(int i = 0; i < sizeBitMap; i++) {
      for(int j = 0; j < sizeBitMap; j++) {
          unsigned char data = CELLBP(bp,i,j);
          if(data == '1') {
            if((j+y) >= boardSize|| (i+x) >= boardSize) {
              insert = false;
              broke = 1;
              break;
            }

            Point *p = newPoint(x+i,y+j); 

            void *aux = searchPoint(structure,p); 
               
            if(aux != NULL) {
                insert = false;
                broke = 1;
                break;
            }
          
          else if(aux == NULL) {

            insert = true; 
         
          }     
        
        free(p);  
      }

      }

      if(broke) {
        break;
      }
    }
    
     return insert;
}


bool insertShipInStructure(User *user, SHIP *ship, int x, int y, int boardSize) {

      bool insert = canInsert(user,ship,x,y, boardSize);

      printf("size: %d\n", boardSize);
      printf("insert %d \n", insert);

      //void *structure = getStructure(user);

      BitMap *bp = SHIPBITMAP(ship);

      printBitMap(bp);

      void *structure = USERSTRUCTURE(user);

      if(insert) {
        for(int i = 0; i < sizeBitMap; i++) {
            for(int j = 0; j < sizeBitMap; j++) {
              unsigned char data = CELLBP(bp,i,j);
                if (data == '1') {
                      SETBPX(bp,x); 
                      SETBPY(bp,y);
                      Point *p = newPoint(BPX(bp) + i, BPY(bp) + j);
                      printf("ponto: x -> %d e y -> %d\n", p -> x, p -> y);
                      void *aux = searchPoint(structure,p); 
                     if(aux == NULL) {
                        aux = initCell();
                        insertedShipCell(aux,ship);  
                        insertShip(user -> dataStructs,aux,p);
                     } 
                      free(p);
                  }
          }
          
      }
      }
    return insert;
}


void insertLittleCell(User *user, int x, int y) {
    
    Point *p = newPoint(x,y);
    void *aux = searchPoint(user -> dataStructs, p);


    if(aux == NULL) {
      aux = initCell(); 
      insertShip(user -> dataStructs, aux, p);
    }

    free(p);

}