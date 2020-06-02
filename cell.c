#include "cell.h"

Cell* initCell() {

    Cell* cell = malloc(sizeof(Cell));

    SETSHIPCELL(cell,NULL);
    SETCELLSHOT(cell,'0');
    SETCELLVALUE(cell,'.');
    
    return cell;
}


void insertedShipCell(Cell *cell, SHIP *sh) {

    SETSHIPCELL(cell,sh);
    SETCELLVALUE(cell, 'x');

}


void changeValueShotBp(Cell *cell, int x, int y, unsigned char ternaryValue) {

    SHIP *sh = SHIPCELL(cell); 
    BitMap *bp = SHIPBITMAP(sh); 

    int x_value = BPX(bp);
    int y_value = BPY(bp);

     SETCELLBP(bp, y-y_value, x-x_value, ternaryValue);

}

// Update values after the shot
void modifyValues(Cell *cell, int x, int y) {

    if(cell != NULL) {

      if(CELLVALUE(cell) == 'x') {

        //value of matrix become *
        SETCELLVALUE(cell,'*');
        SHIP *sh = SHIPCELL(cell);
        SETSHIPSHOTCOUNT(sh, sh -> shotCount--);
        //change value bitmap to ship 2
        //changeValueShotBp(cell,x,y,'2');
    
      }
      else if(CELLVALUE(cell)== '.') {
        //o value of matrix become +
        SETCELLVALUE(cell, '+');
       // if(cell -> ship != NULL) changeValueShotBp(cell,x,y,'3');
     
      }
    }

    

}

void modifyShot(Cell *cell, bool b) {
    if(b == true)
        SETCELLSHOT(cell,'2');
    else
        SETCELLSHOT(cell,'1');
}


bool hittedPiece(Cell *cell, int x, int y) {

    bool hitted = false; 

    SHIP *sh = SHIPCELL(cell);

    if(sh != NULL)  {
        hitted = true;
        //printf("Tem barco \n");
    }
        

    else if(sh == NULL) {
        hitted = false;
        //printf("Não tem barco\n");        
    }

    //printf("HITTED: %d\n", hitted);
    
    return hitted; 
}


// Free allocated memory
void freeCell(Cell *cell) {
    free(cell);
}



