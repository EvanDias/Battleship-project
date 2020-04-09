#include <stdio.h>
#include <math.h>
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


SHIP *newShip(ShipKind kind) {

    SHIP *ship = malloc(sizeof(SHIP));

    ship -> kind = kind;

    ship -> shotCount = numCells(ship); // decrement remaining cells of the ship

    BitMap *bp = initBitMap(5, 5);

    ship = getShipSize(ship);

    ship -> bp = bp;

    shipToOne(ship);

    return ship;

}

void *shipToOne(SHIP *sh) {
    unsigned char ternaryValue = '1';

    if(sh -> kind == SOLO) {
        changeCellValue(sh -> bp, 0, 0, ternaryValue);

    } else if(sh -> kind == SMALL_QUAD || sh -> kind == BIGGEST_QUAD) {

        for(int i=0; i < sh -> columns; i++) {
            for(int j=0; j < sh -> rows; j++) {
                sh -> bp = changeCellValue(sh -> bp, i, j, ternaryValue);
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

//translation - sizeVertical: quanto quer andar para baixo -- sizeHorizontal: quanto quer andar para a direita
void translation(SHIP *sh, int sizeVertical, int sizeHorizontal) {

  BitMap *bitaux = initBitMap(5,5);

  int broke = 0;

  if(sh -> kind != L_GUY) {
    for(int i=0; i < sh -> columns; i++) {
      for(int j=0; j < sh -> rows; j++) {
        if((j+sizeVertical) >= 5 ||(i+sizeHorizontal) >= 5) {
          broke = 1;
          break;
        }
        sh -> bp = bitaux;
        sh -> bp = changeCellValue(sh -> bp, j + sizeVertical, i + sizeHorizontal, '1');

      }

      if(broke) {
        printf("Can't this values to translate ship");
        break;
      }
  }
}
    else printf("This boat can't translate! \n");

    sh -> translationy = sizeVertical;
    sh -> translationx = sizeHorizontal;

}


void rotation(SHIP *sh, int degrees) {

  BitMap *bitFinal = initBitMap(5,5);

  int x_line, y_line = 0;

  int broke = 0;

  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      if(sh->bp -> data[i][j]=='1') {
        x_line = cos_int(degrees)*(j-PXREF) - sin_int(degrees)*(i-PYREF) + PXREF;
        y_line = sin_int(degrees)*(j-PXREF) + cos_int(degrees)*(i-PYREF) + PYREF;
        if(x_line >= 5 || x_line < 0 || y_line >= 5 || y_line < 0) {
          broke = 1;
          break;
        }
        bitFinal = changeCellValue(bitFinal,y_line,x_line,'1');
      }
      }
      if(broke) {
        printf("This ship can't rotate\n");
        break;
      }
     }

    sh -> bp = bitFinal;
    sh -> rotation = degrees;
    int aux = sh -> columns;
    sh -> columns = sh -> rows;
    sh -> rows = aux;
}


int numberShips(int sizeMatrix) {

  int number = 0;

  number = (sizeMatrix*sizeMatrix)/(5*5);

  return number;

}

