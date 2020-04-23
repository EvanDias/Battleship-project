#include "matrix.h"

Cell* initCell() {

    Cell* cell = malloc(sizeof(Cell));

    cell -> ship = NULL;
    cell -> shot = '0';
    cell -> value = '.';
    return cell;
}


//init a matrix with its size
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
        break;
      }
    }

     return insert;
}


// Change value of bp in relation with matrix
void changeValueShotBp(Matrix *matrix, int x, int y, unsigned char ternaryValue) {

    int x_value = matrix -> data[y][x]-> ship -> bp -> refx;
    int y_value = matrix -> data[y][x]-> ship -> bp -> refy;

    changeCellValue(matrix -> data[y][x] -> ship -> bp, y-y_value, x-x_value, ternaryValue);
}


// Print the original matrix without hiding the true values
void printMatrix(Matrix *matrix) {
    printf("\n");
    for(int i = 0; i < matrix -> size; i++) {
      for(int j = 0; j < matrix -> size; j++) {
        printf("%c ", matrix -> data[i][j] -> value);
    }
    printf("\n");
    }
}


// Print the enemy matrix without showing the position's of the ship's
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


// Print letters around the game matrix
void letters(int size) {
    char c;

    printf("  A ");
    while(size != 0) {
        for(c = 'B'; c <= 'Z'; ++c) {
            if(size == 0) break;
            printf("%c ", c);
            size--;
        }

        if(size == 0) break;

        for(c = 'a'; c <= 'z'; ++c) {
            if(size == 0) break;
            printf("%c ", c);
            size--;
        }
    }
}


/*
 * User interface
 * Print current player matrix on left side
 * Print enemy matrix on right side
*/
void printBothMatrix(Matrix *start, Matrix *other) {

    printf("\n");
    int matrixSize = start -> size;
    char c1 = 'A';
    letters(matrixSize-1);
    for(int i=0; i<10; i++) {
        printf(" ");
    }
    letters(matrixSize-1);
    printf("\n");

    for(int i=0; i < matrixSize; i++) {
            printf("%c ", c1);
            if(c1 == '[') c1 = 'a';
            for(int j = 0; j < matrixSize; j++) {
                printf("%c ", start -> data[i][j] -> value);
            }

            for(int z=0; z<10; z++) {
                printf(" ");
            }

            printf("%c ", c1);
            for(int j = 0; j < matrixSize; j++) {
                if(other -> data[i][j] -> value == 'x')
                    printf(". ");
                else
                    printf("%c ", other -> data[i][j] -> value);
            }
            c1 += 1;
    printf("\n");
    }
}


// Change the value of a recently sunk ship to '#'
void printSinkShip(Matrix *matrix, int x, int y) {
    SHIP *ship = matrix -> data[y][x] -> ship;

    int xref = ship -> bp -> refx;
    int yref = ship -> bp -> refy;

    printf("KIND: %d\n", ship -> kind);

    for(int i = 0; i < sizeBitMap; i++) {
      for(int j = 0; j < sizeBitMap; j++) {
        if (ship -> bp -> data[j][i] == '2') {
            matrix -> data[j+yref][i+xref]-> value = '#';
        }
      }
    }
}


// To know if the position chosen by the user is uppercase or lowercase
int choiceChar(char c) {
    int x;
    if(c >= 'A' && c <= 'Z')
        x = charToIntUpper(c);
    else
        x = charToIntLower(c);

    return x;
}


// convert Character to int. Ex: (A B C D E ...) -> (0 1 2 3 4 ...)
int charToIntUpper(char chInput) {

    int inc = 0;

    char ch = 'A';

    while(true) {
        if(ch == chInput)
            return inc;

        ch++;
        inc++;
    }

    return inc;
}


// convert Character to int. Ex: (a b c d e ...) -> (26 27 28 29 30 ...)
int charToIntLower(char chInput) {

    int inc = 26;

    char ch = 'a';

    while(true) {
        if(ch == chInput)
            return inc;

        ch++;
        inc++;
    }

    return inc;
}
