#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

Cell* initCell() {

    Cell* cell = malloc(sizeof(Cell));

    cell -> union1.empty.shot = '0';
    cell -> union1.empty.value = '.';
    return cell;
}


//init a matrix with its size and fill with '.'
Matrix* initMatrix(int size) {

    Matrix* matrix = malloc(sizeof(Matrix));
    matrix -> size = size;

    pCell* data = malloc(sizeof(Cell*) * size);

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

Matrix *changeCellValue(Matrix *matrix, int x, int y) {




}

/*
int main() {

  Matrix* x = initMatrix(5);
  printMatrix(x);
}
*/
/*

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