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

//Change value of bitmap's cell, according ship kind
void *shipToOne(SHIP *sh) {
    unsigned char ternaryValue = '1';

    if(sh -> kind == SOLO) {
        changeCellValue(sh -> bp, 0, 0, ternaryValue);

    } else if(sh -> kind == SMALL_QUAD || sh -> kind == BIGGEST_QUAD) {

        for(int i=0; i < sh -> columns; i++) {
            for(int j=0; j < sh -> rows; j++) {
               changeCellValue(sh -> bp, i, j, ternaryValue);
            }
        }

    } else if(sh -> kind == TRIAL)  {
        for(int i=0; i<3; i++)
            changeCellValue(sh -> bp, 0, i, ternaryValue);

    } else if(sh -> kind == L_GUY) {
        for(int i=1; i < sh -> columns; i++)
            changeCellValue(sh -> bp, 4, i, ternaryValue);

        for(int j=0; j < sh -> rows; j++)
            changeCellValue(sh -> bp, j, 0, ternaryValue);
    }

}


//number of columns and rows 
SHIP *getShipSize(SHIP *sh) {

    int columns, rows;

    if(sh -> kind == SOLO) {
        columns = 1;
        rows = 1;
    } else if(sh -> kind == TRIAL) {
        columns = 3;
        rows = 1;
    } else if(sh -> kind == SMALL_QUAD) {
        columns = 2;
        rows = 2;
    } else if(sh -> kind == BIGGEST_QUAD) {
        columns = 4;
        rows = 4;
    } else if(sh -> kind == L_GUY) {
        columns = 5;
        rows = 5;
    }

    sh -> columns = columns;
    sh -> rows = rows;

    return sh;
}


//number of cells that is occuped in bitmap
int numCells(SHIP *sh) {

    switch(sh -> kind) {

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
         default:
            return 0;
    }

}


//function auxiliar to print a name of Ship
char *nameShip(SHIP *sh) {

  char *kind = "";
  switch(sh -> kind) {

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
    default : kind = "";
            break;

  }

  return kind;

}

//translation of ship in bitmap 
bool translation(SHIP *sh, int sizeVertical, int sizeHorizontal) {

  BitMap *bitaux = initBitMap();

  bool translate = false;
  int broke = 0;

  if(sh -> kind != L_GUY) {
    for(int i=0; i < sh -> columns; i++) {
      for(int j=0; j < sh -> rows; j++) {
        if((j+sizeVertical) >= 5 ||(i+sizeHorizontal) >= 5) {
          broke = 1;
          break;
        }
        sh -> bp = bitaux;
        changeCellValue(sh -> bp, j + sizeVertical, i + sizeHorizontal, '1');
        translate = true;
      }

      if(broke) {
      //  printf("Can't this values to translate! \n");
        translate = false;
        break;
      }
  }
}
    else {
      char *kind = nameShip(sh);
      printf("Ship of %s' type can't translate! \n", kind);
      translate = true;
    }

    sh -> translationy = sizeVertical;
    sh -> translationx = sizeHorizontal;

    return translate;

}


//rotation of ship in bitmap 

bool rotation(SHIP *sh, int degrees) {

  BitMap *bitFinal = initBitMap();

  int x_line, y_line = 0;

  int broke = 0;
  bool rotate = false;


  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      if(sh->bp -> data[i][j]=='1') {
        x_line = cos_int(degrees)*(j-PXREF) - sin_int(degrees)*(i-PYREF) + PXREF;
        y_line = sin_int(degrees)*(j-PXREF) + cos_int(degrees)*(i-PYREF) + PYREF;
        if(x_line >= 5 || x_line < 0 || y_line >= 5 || y_line < 0) {
          broke = 1;
          break;
        }
       changeCellValue(bitFinal,y_line,x_line,'1');
        rotate = true;
      }
      }
      if(broke) {
        printf("This ship can't rotate\n");
        break;
      }
     }

    sh -> bp = bitFinal;
    sh -> rotation = degrees;

    return rotate;
}

void delete_ship(SHIP *sh) {
  free(sh -> bp);
  free(sh);
}
