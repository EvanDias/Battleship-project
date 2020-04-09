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


void insertShipInMatrix(Matrix *matrix, SHIP *ship, int x, int y) {


      bool insert = canInsert(matrix,ship,x,y);

      //printf("%d\n", insert);

      if(insert) {
      ship -> bp -> refx = x; 
      ship -> bp -> refy = y;

      for(int i = 0; i < ship -> columns; i++) {
        for(int j = 0; j < ship -> rows; j++) {
          if (ship -> bp -> data[j][i] == '1') {
            matrix -> data[j+y][i+x]-> ship = ship;
            matrix -> data[j+y][i+x]-> value = 'x';
          }
        }
      }
    }
}


bool canInsert(Matrix *matrix, SHIP *ship, int x, int y) {

    bool insert = true;

    for(int i = 0; i < ship -> columns; i++) {
      for(int j = 0; j < ship -> rows; j++) {
          if((j+y) >= matrix -> size || (i+x) >= matrix -> size) insert = false;
          else if(matrix -> data[j+y][i+x] -> value == 'x') {
          insert = false;
        }


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

  SHIP *sh = newShip(4);

  SHIP *sh1 = newShip(4);

  SHIP *sh2 = newShip(3);


  insertShipInMatrix(x,sh,2,3);

  insertShipInMatrix(x,sh1,3,3);

  insertShipInMatrix(x,sh1,17,2);

  printMatrix(x);

  for(int i = 0; i < x -> size; i++) {
    for(int j = 0; j < x -> size; j++) {
        printf("kind: %d \n", x -> data[i][j] -> ship -> kind);

    }
  }
  //printMatrix(x);
}


*/