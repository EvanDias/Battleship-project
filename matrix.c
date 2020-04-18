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

      ship -> bp -> refx = x;
      ship -> bp -> refy = y;

      if(insert) {
      for(int i = 0; i < sizeBitMap; i++) {
        for(int j = 0; j < sizeBitMap; j++) {
          if (ship -> bp -> data[j][i] == '1') {
            ship -> bp -> refx = x;
            ship -> bp -> refy = y;
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

    for(int i = 0; i < sizeBitMap; i++) {
      for(int j = 0; j < sizeBitMap; j++) {

          if((j+y) >= matrix -> size || (i+x) >= matrix -> size) {
            insert = false;
            broke = 1;
            break;
          }

          else if(matrix -> data[j+y][i+x] -> value == 'x' && ship -> bp -> data[j][i] == '1') {
            insert = false;
            broke = 1;
            break;
          }
      }
      if(broke) {
      //  fprintf(stderr, "ERROR: you can't insert this ship\n");
        break;
      }
    }

     return insert;
}



void printMatrix(Matrix *matrix) {
    printf("\n");
    for(int i = 0; i < matrix -> size; i++) {
      for(int j = 0; j < matrix -> size; j++) {
        printf("%c ", matrix -> data[i][j] -> value);
    }
    printf("\n");
    }
}


void printEnemyMatrix(Matrix *matrix) {
    printf("\n");
    for(int i = 0; i < matrix -> size; i++) {
        for(int j = 0; j < matrix -> size; j++) {
            if(matrix -> data[i][j] -> value == 'x')
                printf(". ");
            else
                printf("%c ", matrix -> data[i][j] -> value);
        }
    printf("\n");
}

}


void printBothMatrix(Matrix *start, Matrix *other) {
    printf("\n");
    int matrixSize = start -> size;

    for(int i=0; i < matrixSize; i++) {

        for(int j = 0; j < matrixSize; j++) {
            printf("%c ", start -> data[i][j] -> value);
        }

        for(int z=0; z<10; z++) {
            printf(" ");
        }

        for(int j = 0; j < matrixSize; j++) {
            if(other -> data[i][j] -> value == 'x')
                printf(". ");
            else
                printf("%c ", other -> data[i][j] -> value);
        }

    printf("\n");

    }
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
