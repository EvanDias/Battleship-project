#include "ship.h"

#define PXREF 2
#define PYREF 2
#define sin_int(degrees)({int res=0; \
  if(degrees %360 == 0 ||degrees== 180)res=0;\
  else if(degrees == 270 )res=-1;\
  else if(degrees == 90) res = 1;\
  res; \
})
#define cos_int(degrees)({int res=0; \
  if(degrees == 90 || degrees == 270)res=0;\
  else if(degrees % 360 == 0)res= 1;\
  else if(degrees == 180) res = -1;\
  res; \
})
#define countValuesNotNull(array)({ int count=0; \
    for(int i = 0; i < 25; i++) {\
      if(array[i] != NULL) count++; \
    }\
    count;\
})


/*Create a ship with :
  * kind
  * shotCount
  * bitmap
  * size
*/
SHIP *newShip(ShipKind kind) {

    SHIP *ship = malloc(sizeof(SHIP));

    ship -> kind = kind;

    ship -> shotCount = numCells(ship);

    BitMap *bp = initBitMap();

    ship = getShipSize(ship);

    ship -> bp = bp;

    shipToOne(ship);

    return ship;
}

SHIP *getShip(SHIP *ship) {
  return ship;

}

ShipKind getShipKind(SHIP *sh) {
  return sh -> kind;
}

int getColumnsRows(SHIP *sh, char c) {

  if(c == 'r') return sh -> rows; 

  else return sh -> columns;

}

BitMap *getBitMapShip(SHIP *sh) {

  return getBitMap(sh -> bp);
}


int getShotCount(SHIP *sh) {

  return sh -> shotCount;
}

void setShotCount(SHIP *sh, int value) {

    sh -> shotCount = value;
}

//Change value of bitmap's cell, according ship kind
void *shipToOne(SHIP *sh) {
    unsigned char ternaryValue = '1';

    BitMap *bp = getBitMapShip(sh);
    int columns = getColumnsRows(sh,'c'); 
    int rows = getColumnsRows(sh,'r');

    if(sh -> kind == SOLO) {
        changeCellValue(bp, 0, 0, ternaryValue);

    } else if(sh -> kind == SMALL_QUAD || sh -> kind == BIGGEST_QUAD) {

        for(int i=0; i < columns; i++) {
            for(int j=0; j < rows; j++) {
               changeCellValue(bp, i, j, ternaryValue);
            }
        }

    } else if(sh -> kind == TRIAL)  {
        for(int i=0; i<3; i++)
            changeCellValue(bp, 0, i, ternaryValue);

    } else if(sh -> kind == L_GUY) {
        for(int i=1; i < columns; i++)
            changeCellValue(bp, 4, i, ternaryValue);

        for(int j=0; j < rows; j++)
            changeCellValue(bp, j, 0, ternaryValue);
    }

    else if(sh -> kind == T_GUY) {
        for(int i = 0; i < columns; i++) changeCellValue(bp, i,1,ternaryValue);
        for(int j = 0; j < rows; j++) changeCellValue(bp, 0,j, ternaryValue);
    }

    else if(sh -> kind == S_GUY) {
        for(int i = 0; i < 3; i++) changeCellValue(bp, 4,i,ternaryValue);
        for(int j = 0; j < 5; j++) changeCellValue(bp, j, 2, ternaryValue);
        for(int k = 3; k <= 4; k++) changeCellValue(bp, 0,k,ternaryValue);
    }

    return NULL;

}


//number of columns and rows
SHIP *getShipSize(SHIP *sh) {

    int columns = 0, rows = 0;

    ShipKind kind = getShipKind(sh);

    if(kind == SOLO) {
        columns = 1;
        rows = 1;
    } else if(kind == TRIAL) {
        columns = 3;
        rows = 1;
    } else if(kind == SMALL_QUAD) {
        columns = 2;
        rows = 2;
    } else if(kind == BIGGEST_QUAD) {
        columns = 4;
        rows = 4;
    } else if(kind == L_GUY) {
        columns = 5;
        rows = 5;
    }
      else if(kind == T_GUY) {
          columns = 3;
          rows = 3;
      }

      else if(kind == S_GUY) {
          columns = 5;
          rows = 5;
      }

    sh -> columns = columns;
    sh -> rows = rows;

    return sh;
}


//number of cells that is occuped in bitmap
int numCells(SHIP *sh) {

    ShipKind kind = getShipKind(sh);

    switch(kind) {

        case SOLO:
            return 1;
        case TRIAL:
            return 3;
        case SMALL_QUAD:
           return 4;
        case BIGGEST_QUAD:
            return 16;
        case L_GUY:
            return 9;
        case T_GUY:
            return 5;
        case S_GUY:
            return 9;
         default:
            return 0;
    }
}


// Auxiliar function to print the name of a Ship
char *nameShip(SHIP *sh) {

  char *kind = "";

  ShipKind shipKind = getShipKind(sh);

  switch(shipKind) {

    case 0: kind = "SOLO";
            break;
    case 1: kind = "TRIAL";
            break;
    case 2: kind = "SMALL_QUAD";
            break;
    case 3: kind = "BIGGEST_QUAD";
            break;
    case 4: kind = "L_GUY";
            break;
    case 5: kind = "T_GUY";
            break;
    case 6: kind = "S_GUY";
            break;
    default : kind = "";
            break;

  }

  return kind;

}


// Translation of ship in bitmap
bool translation(SHIP *sh, int sizeVertical, int sizeHorizontal) {

  bool translate = false;
  int broke = 0;

  int columns = getColumnsRows(sh,'c');
  int rows = getColumnsRows(sh, 'r');

  BitMap *bp = getBitMapShip(sh);
  ShipKind kind = getShipKind(sh);

  if(kind != L_GUY && kind != T_GUY && kind != S_GUY) {
    allZero(sh -> bp, '0');
    for(int i=0; i < columns; i++) {
      for(int j=0; j < rows; j++) {
        if((j+sizeVertical) >= 5 || (i+sizeHorizontal) >= 5) {
          broke = 1;
          break;
        }

        changeCellValue(bp, j + sizeVertical, i + sizeHorizontal, '1');
        translate = true;
      }

      if(broke) {
      //  printf("Can't this values to translate! \n");
        translate = false;
        break;
      }
    }
  }
    else if(kind == T_GUY) {
        allZero(sh -> bp, '0');
        for(int i = 0; i < columns;i++)  {
          for(int j = 0; j < rows; j++) {
          if((sizeVertical) >= 3 ||(sizeHorizontal) >= 3) {
          broke = 1;
          break;
        }
          changeCellValue(bp, sizeVertical, i + sizeHorizontal, '1');
          changeCellValue(bp, j + sizeVertical, 1 + sizeHorizontal, '1' );
          translate = true;
      }

        if(broke) {
            //  printf("Can't this values to translate! \n");
            translate = false;
            break;
            }
        }
      }

    else if(kind == L_GUY || kind == S_GUY) {
      char *kind = nameShip(sh);
      printf("Ship of %s' type can't translate! \n", kind);
      translate = true;
    }

    return translate;
}


// Rotation of ship in bitmap
void rotation(SHIP *sh, int degrees) {

  BitMap *bitFinal = initBitMap();

  int x_line, y_line = 0;

  int broke = 0;

  BitMap *bp = getBitMapShip(sh);


  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      unsigned char data = getCellBitMap(bp,i,j);
      if(data =='1') {
        x_line = cos_int(degrees)*(j-PXREF) - sin_int(degrees)*(i-PYREF) + PXREF;
        y_line = sin_int(degrees)*(j-PXREF) + cos_int(degrees)*(i-PYREF) + PYREF;
        if(x_line >= 5 || x_line < 0 || y_line >= 5 || y_line < 0) {
          broke = 1;
          break;
        }
       changeCellValue(bitFinal,y_line,x_line,'1');

      }
      }
      if(broke) {
        printf("This ship can't rotate\n");
        break;
      }
     }

    copyBitMaps(bitFinal, bp);

    freeBitMap(bitFinal);

}

bool sinkBoat(SHIP *ship) {
    bool sinkBoatV = false;

    int shotCount = getShotCount(ship);

    if(ship -> shotCount == 0) sinkBoatV = true;

    return sinkBoatV;
}

List *activatePoints(SHIP *sh) {

  List *list = initList(); 

  BitMap *bp = getBitMapShip(sh);

  for(int i = 0; i < sizeBitMap; i++) {
    for(int j = 0; j < sizeBitMap; j++) {
      unsigned char data = getCellBitMap(bp,i,j);
      if(data == '1') {
        Point *p = newPoint(i,j);
        headList(list,p);
      }
    }
  }

  return list;
}

// Free allocated memory
void freeShip(SHIP *sh) {
    freeBitMap(sh -> bp);
    free(sh);
}
