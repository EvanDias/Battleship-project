#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Cell* initCell() {

    Cell* cell = malloc(sizeof(Cell));

    cell -> ship = NULL;
    cell -> shot = '0';
    cell -> value = '.';
    return cell;
}


//init a matrix with its size and fill with '.'
Matrix* initMatrix(int size) {

    Matrix* matrix = malloc(sizeof(Matrix));
    matrix -> size = size;

    Cell*** data = malloc(sizeof(Cell*) * size);

    for(int i = 0; i < size; i++) {
        data[i] = malloc(size * sizeof(Cell));
    }

    for(int i = 0; i < size; i++) {
       for(int j = 0; j < size; j++) {
         data[i][j] = initCell();

        }
    }

    matrix -> data = data;

    return matrix;
}


bool insertShipInMatrix(Matrix *matrix, SHIP *ship, int x, int y) {


      bool insert = canInsert(matrix,ship,x,y);
      bool insertMatrix = false;

      if(insert) {
      ship -> bp -> refx = x; 
      ship -> bp -> refy = y;

      printBitMap(ship -> bp); printf("\n");
      for(int i = 0; i < sizeBitMap; i++) {
        for(int j = 0; j < sizeBitMap; j++) {
          if (ship -> bp -> data[j][i] == '1') {
            matrix -> data[j+y][i+x]-> ship = ship;
            matrix -> data[j+y][i+x]-> value = 'x';
            insertMatrix = true;
          }
        }
      }
    }

    return insertMatrix;
}


bool canInsert(Matrix *matrix, SHIP *ship, int x, int y) {

    bool insert = true;
    int broke = 0;

    for(int i = 0; i < ship -> columns; i++) {
      for(int j = 0; j < ship -> rows; j++) {
          if((j+y) >= matrix -> size || (i+x) >= matrix -> size) {
            insert = false;
            broke = 1;
            break;
          }

          else if(matrix -> data[j+y][i+x] -> value == 'x') {
            insert = false;
            broke = 1;
            break;
          }
      }
      if(broke) {
        fprintf(stderr, "Error, you dont insert this ship\n");
        break;
      }
    }

     return insert;
}




void printMatrix(Matrix *matrix) {

    for(int i = 0; i < matrix -> size; i++) {
      printf("\n");
      for(int j = 0; j < matrix -> size; j++) {
        printf("%c ", matrix -> data[i][j] -> value);
      }
    }
    printf("\n");
}





/*
int main() {

  Matrix* x = initMatrix(20);

  SHIP *sh = newShip(3);

  SHIP *sh1 = newShip(3);

  SHIP *sh2 = newShip(4);

  rotation(sh, 270);

  //printBitMap(sh -> bp);


  insertShipInMatrix(x,sh,2,3);

  insertShipInMatrix(x,sh1,3,3);

  //insertShipInMatrix(x,sh1,17,2);

  printMatrix(x);
}

*/
