#include "cell.h"

Cell* initCell() {

    Cell* cell = malloc(sizeof(Cell));

    cell -> ship = NULL;
    cell -> shot = '0';
    cell -> value = '.';
    return cell;
}


SHIP *getShipCell(Cell *cell) {

    return cell -> ship;

}

void setSHIPCell(Cell *cell, SHIP  *sh) {
    
    printf("MUDAR BARCO NA CELULA\n");    
    cell -> ship = sh;

}

void insertedShipCell(Cell *cell, SHIP *sh) {

    printf("INSERIU O SHIP NA CELULA\n");
    setSHIPCell(cell,sh);
    modifyCellValue(cell, 'x');

}

unsigned char CellValue(Cell *cell) {

    return cell ->value;
}


unsigned char CellShot(Cell *cell) {

    return cell -> shot;

}

void modifyCellValue(Cell *cell, unsigned char ch) {

    cell -> value = ch;

}

void modifyCellShot(Cell *cell, unsigned char ch) {

    cell -> shot = ch;

}

void changeValueShotBp(Cell *cell, int x, int y, unsigned char ternaryValue) {

    SHIP *sh = getShipCell(cell); 
    BitMap *bp = getBitMapShip(sh); 

    int x_value = getXandY(bp,'x');
    int y_value = getXandY(bp,'y');

     changeCellValue(bp, y-y_value, x-x_value, ternaryValue);

}

// Update values after the shot
void modifyValues(Cell *cell, int x, int y) {

    if(cell != NULL) {

      if(CellValue(cell) == 'x' || CellValue(cell) == '#') {

        //value of matrix become *
        modifyCellValue(cell,'*');
        cell -> ship -> shotCount--;
        //change value bitmap to ship 2
        //changeValueShotBp(cell,x,y,'2');
    
      }
      else if(cell -> value == '.') {
        //o value of matrix become +
        modifyCellValue(cell, '+');
       // if(cell -> ship != NULL) changeValueShotBp(cell,x,y,'3');
     
      }
    }

    

}


void modifyShot(Cell *cell, bool b) {
    if(b == true)
        modifyCellShot(cell,'2');
    else
        modifyCellShot(cell,'1');
}

bool hittedPiece(Cell *cell, int x, int y) {

    bool hitted = false; 

    SHIP *sh = getShipCell(cell);

    printf("ENTROU NO HIT\n");    
    if(sh != NULL)  {
        hitted = true;
        printf("Tem barco \n");
    }
        

    else if(sh == NULL) {
        hitted = false;
        printf("Não tem barco\n");        
    }
    printf("HITTED: %d\n", hitted);
    return hitted; 
}


// Free allocated memory
void freeCell(Cell *cell) {
    free(cell);
}



