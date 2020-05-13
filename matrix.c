#include "matrix.h"

Cell* initCell() {

    Cell* cell = malloc(sizeof(Cell));

    cell -> ship = NULL;
    cell -> shot = '0';
    cell -> value = '.';
    return cell;
}


// Init a matrix with its size
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


// Return's the icone value
unsigned char CellValue(Matrix *m, int x, int y) {
    return m -> data[y][x] -> value;
}


// Return's the shot value
unsigned char CellShot(Matrix *m, int x, int y) {
    return m -> data[y][x] -> shot;
}


void modifyCellValue(Matrix *m, int x, int y, unsigned char ch) {
    m -> data[y][x] -> value = ch;
}


void modifyCellShot(Matrix *m, int x, int y, unsigned char ch) {
    m -> data[y][x] -> shot = ch;
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
                    modifyCellValue(matrix,i+x,j+y,'x');
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
          else if(j+y-1 > 0 && j+y+1 < matrix -> size && i+x-1 > 0 && i+x+1 < matrix -> size) {
                 if((matrix -> data[j+y][i+x-1] -> value == 'x' && ship -> bp -> data[j][i]=='1')|| (matrix -> data[j+y][i+x+1] -> value == 'x' && ship -> bp -> data[j][i] == '1')|| (matrix -> data[j+y-1][i+x] -> value == 'x' && ship -> bp -> data[j][i] == '1')|| (matrix -> data[j+y+1][i+x] -> value == 'x'&& ship -> bp -> data[j][i] == '1')) {
                     insert = false;
                     broke = 1;
                     break;
                 }
                }
      }
      if(broke) {
        break;
      }
    }

     return insert;
}


// Change value of bitmap in relation with matrix
void changeValueShotBp(Matrix *matrix, int x, int y, unsigned char ternaryValue) {

    int x_value = matrix -> data[y][x]-> ship -> bp -> refx;
    int y_value = matrix -> data[y][x]-> ship -> bp -> refy;

    changeCellValue(matrix -> data[y][x] -> ship -> bp, y-y_value, x-x_value, ternaryValue);
}

bool sinkBoatMatrix(Matrix *x) {
    for(int i = 0; i < x -> size; i++) {
      for(int j = 0; j < x -> size; j++) {
        if(CellValue(x,i,j) == '*') {
          if(sinkBoat(x -> data[j][i] -> ship)==true) {
            printf("Sink a boat with coordenates (%d,%d) \n", j,i);
            return true;
        }
      }
    }
  }
  return false;
}


void deleteShipMatrix(Matrix *ma, SHIP *sh, int x, int y) {
     int xx = ma -> data[y][x] -> ship -> bp -> refx;
     int yy = ma -> data[y][x] -> ship -> bp -> refy;
     for(int i = 0; i < sizeBitMap; i++) {
        for(int j = 0; j < sizeBitMap; j++) {
            if (sh -> bp -> data[j][i] == '1') {
                ma -> data[j+yy][i+xx] = initCell();
            }
        }
     }
}


void printMatrix(Matrix *matrix) {
    printf("\n");
    printf("  A ");

    char c1 = 'B';
    for(int i=1; i < matrix -> size; i++) {
        printf("%c ", c1);
        c1++;
        if(c1 == '[') c1 = 'a';
    }
    printf("\n");
    c1 = 'A';
    for(int i = 0; i < matrix -> size; i++) {
        printf("%c ", c1);
        c1++;
        if(c1 == '[') c1 = 'a';
      for(int j = 0; j < matrix -> size; j++) {
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


// Know if the chosen char is a Upper or Lower case
int choiceChar(char c) {
    int x;

    if(c >= 'A' && c <= 'Z')
        x = charToIntUpper(c);
    else
        x = charToIntLower(c);

    return x;
}


// To know if the position chosen by the user is uppercase or lowercase
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


// convert Character to int. Ex: (a b c d e ...) -> (0 1 2 3 4 ...)
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


// Verify if it's possible make the shot
bool canShot(Matrix *matrix, int x, int y) {
    bool shot = true;

    if(y >= matrix -> size || x >= matrix -> size)
        shot = false;

    else if(CellValue(matrix,x,y) == 'x' || CellValue(matrix,x,y) == '.')
        shot = true;

    else if(CellValue(matrix,x,y) == '*' || CellValue(matrix,x,y) == '#')
        shot = false;

    return shot;
}


// Update values after the shot
bool modifyValues(Matrix *other, int x, int y) {

    bool shotMatrix = false;

      if(CellValue(other,x,y) == 'x' || CellValue(other,x,y) == '#') {

        //value of matrix become *
        modifyCellValue(other,x,y,'*');
        other -> data[y][x] -> ship -> shotCount--;
        //change value bitmap to ship 2
        changeValueShotBp(other,x,y,'2');
        shotMatrix = true;
      }
      else if(other -> data[y][x] -> value == '.') {
        //o value of matrix become +
        modifyCellValue(other,x,y,'+');
        if(other -> data[y][x] -> ship != NULL) changeValueShotBp(other,x,y,'3');
        shotMatrix = false;
      }
      return shotMatrix;
}

void modifyShot(Matrix *m, int x, int y, bool b) {
    if(b == true)
        modifyCellShot(m,x,y,'2');
    else
        modifyCellShot(m,x,y,'1');
}


// Free allocated memory
void freeMatrix(Matrix *matrix) {
     for(int i=0; i< matrix -> size; i++) {
        for(int j=0; j < matrix -> size; j++) {
            freeCell(matrix -> data[i][j]);
        }
        free(matrix -> data[i]);
     }

    free(matrix -> data);
    free(matrix);
}


// Free allocated memory
void freeCell(Cell *cell) {
    free(cell);
}

