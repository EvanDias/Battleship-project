#include "game.h"

bool gameTurn(User *start, User *other, int boardSize) {

  char ch_x, ch_y;
  int x, y = 0;
  bool shotCan = false;

  void *structureStart = getStructure(start);
  void *structureOther = getStructure(other);
  bool playAgain = false;

  printUsers(start, other, boardSize);
  printBothBoard(start, other, boardSize);
  
   printf("%s choose point to hit a ship of %s\n", start -> username, other -> username);
    printf("x: ");
    scanf(" %c", &ch_x);
    printf("\ny: ");
    scanf(" %c",&ch_y);
    x = choiceChar(ch_x);
    y = choiceChar(ch_y);
  
  //  x = randomShoot(boardSize);
   // y = randomShoot(boardSize);

    shotCan = canShot(other,x,y,boardSize);

    if(shotCan) {
          playAgain = shotPlayer(other, x,y);
          modifyValuesStruct(other,x,y);
          insertLittleCell(start,x,y);

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
          
         //  x = randomShoot(boardSize);
          // y = randomShoot(boardSize);

      

          if(shotCan) {
            playAgain = shotPlayer(other, x,y);
            modifyValuesStruct(other,x,y);
            insertLittleCell(start,x,y);
          }
          else shotCan = canShot(start,x, y, boardSize);
    }
    }

    if(sinkBoatStructure(other -> dataStructs, boardSize)) {
        printUsers(start, other, boardSize);
        printBothBoard(start, other, boardSize);
        //printBoard(start, boardSize);
        //printBoard(other, boardSize);
        printf("You sank the ship!\n");
    } else {
       printUsers(start, other, boardSize);
        printBothBoard(start, other,boardSize);
          //printBoard(start, boardSize);
        //printBoard(other, boardSize);
        Point *p = newPoint(x,y);
        void *aux = searchPoint(structureOther,p);
        if(aux == NULL) printf("pois\n");
        
        else {
        if(CellValue((Cell*)aux) == '*')
            printf("You hit a ship!\n");
        else if(CellValue((Cell*)aux) == '+')
            printf("You hit a empty cell!\n");
     }
    }
  
     //sleep(2);

    printf("playAgain : %d\n", playAgain);
    return playAgain;
}


// Play again after hit a ship
bool playAgain(User *start, User *other, int boardSize) {

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
      playAgainVar = playAgain(start, other, boardSize);
      if(playAgainVar) {
        printf("||     CONGRULATIONS!     ||\n");
        printf("The player %s win the game! \n", start -> username);
        break;
      }
      playAgainVar= playAgain(other,start, boardSize);
      if(playAgainVar) {
        printf("||     CONGRULATIONS!     ||\n");
        printf("The player %s win the game! \n", other -> username);
        break;
      }
    }
    // Free all allocated memory used on the game
    //freeUser(start);
    //freeUser(other);
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

bool canShot(User *usr, int x, int y, int boardSize) {

  bool shot = true; 
  void *structure = getStructure(usr); 

  Point *p = newPoint(x,y);
    if(y >= boardSize || x >= boardSize) {
       shot = false;
      return shot;
    }

  void *aux = searchPoint(structure,p);

     if(aux == NULL) {
      aux = initCell(); 
      insertShip(usr -> dataStructs, aux,p);
      shot = true;
    }

    else {
      Cell *cell = (Cell*)aux;

      if(CellValue(cell) == 'x' || CellValue(cell) == '.') shot = true;

      else if(CellValue(cell) == '*' || CellValue(cell) == '#') shot = false;

    }   

    return shot;
}

bool shotPlayer(User *user, int x, int y) {

    bool shot = false; 


    Point *p = newPoint(y,x);

    void *structure = getStructure(user);
    void *aux = searchPoint(structure,p);
    
    if(aux != NULL) {
      Cell *cell = (Cell*)aux;
      shot = hittedPiece(cell,x,y);
      printf("SHOT: %d\n", shot);

    }
    
    return shot;

}



bool sinkBoatStructure(void *structure, int boardSize) {

    for(int i = 0; i < boardSize; i++) {
      for(int j = 0; j < boardSize; j++) {
        Point *p = newPoint(i,j);
        void *aux = searchPoint(structure,p);
          if(aux != NULL) {
            if(CellValue((Cell*)aux) == '*') {
              SHIP *sh = getShipCell((Cell*)aux);
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
  void *structure = getStructure(user);

  Point *p = newPoint(x,y);
  
  void *aux = searchPoint(structure,p); 

  if(aux != NULL) {

    Cell *cell = (Cell*)aux;
    modifyValues(cell,x,y);

  }
  

}

/*
void modifyShotsStruct(User *user, int x, int y, bool b) {

  void *structure = getStructure(user);

  Point *p = newPoint(x,y);
  
  void *aux = searchPoint(structure,p); 

  if(cell != NULL) {
    
    modifyShot(cell,b);

}

*/

bool canInsert(User *user, SHIP *ship, int x, int y, int boardSize) {

    bool insert = true;
    int broke = 0;

    //printf("user %s", user -> username);

    //printBoard(user, boardSize);

    BitMap *bp = getBitMapShip(ship);

    for(int i = 0; i < sizeBitMap; i++) {
      for(int j = 0; j < sizeBitMap; j++) {
          unsigned char data = getCellBitMap(bp,i,j);
          if(data == '1') {
            if((j+y) >= boardSize|| (i+x) >= boardSize) {
              printf("SAIU FORA DO SITIO\n");
              insert = false;
              broke = 1;
              break;
            }

            Point *p = newPoint(x+i,y+j); 
          //printf("fiz o ponto \n");
            void *aux = searchPoint(user -> dataStructs,p); 
        
              
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
    
     printf("INSERT : %d\n", insert);
     return insert;
}


bool insertShipInStructure(User *user, SHIP *ship, int x, int y, int boardSize) {

      bool insert = canInsert(user,ship,x,y, boardSize);

      printf("size: %d\n", boardSize);
      printf("insert %d \n", insert);

      //void *structure = getStructure(user);

      BitMap *bp = getBitMapShip(ship);


      if(insert) {
        for(int i = 0; i < sizeBitMap; i++) {
            for(int j = 0; j < sizeBitMap; j++) {
              unsigned char data = getCellBitMap(bp,i,j);
                if (data == '1') {
                      Point *p = newPoint(i+x, j+y);
                      printf("ponto: x -> %d e y -> %d\n", p -> x, p -> y);
                      void *aux = searchPoint(user -> dataStructs,p); 
                      printf("%p\n", aux); 
                     if(aux == NULL) {
                        printf("entrei aqui \n");
                        aux = initCell();
                        printf("%p\n", aux); 
                        insertedShipCell(aux, ship);
                        insertShip(user -> dataStructs,aux,p);
                      
                      }

                      else if(aux != NULL) {
                        printf("Não sou nulo\n");
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
