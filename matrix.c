#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Cell* initCell() {

    Cell* cell = malloc(sizeof(Cell));

    cell -> ship = NULL;
    cell -> shot = ' ';
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
          if(matrix -> data[j+y][i+x] -> value == 'x') {
          insert = false;
        }


      }
    }

     return insert;
}



void changeValueOfMatrix(Matrix *a, int x, int y, unsigned char valueTernary) {

      a -> data[x][y] -> shot  = valueTernary;

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

  printMatrix(x);

  //printMatrix(x);
}


/

Matrix* insertShipInMatrix(Matrix* matrix, SHIP *ship, int x, int y) {

    for(int i = x; i < matrix -> size; i++) {
      for(int j = y; j < matrix -> size;j++) {
        matrix -> data[i][j] = ship -> bp -> data[i][j];
      }
    }

    return matrix;
}

Matrix *auxInserShip(Matrix* matrix, SHIP *ship) {

    for(int i = 0; i < matrix -> size; i++) {
      for(int j = 0; j < matrix -> size; j++) {
        matrix -> data[i][j] = ship -> bp -> data[i][j];
      }
    }

    return matrix;
}




//function to print a matrix
void printMatrix(Matrix *x) {

    for(int i = 0; i < x->size; i++) {
        printf("\n");
            for(int j = 0; j< x -> size; j++) {
              printf("%c ", x -> data[i][j] -> union1.notEmpty.shot);
              }
          }

}

//loojup a point of matrix, and if this point is a ship's point, it say acertou or errou  - working in progress
*/
