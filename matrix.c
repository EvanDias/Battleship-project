#include "matrix.h"



// Init a matrix with its size
Matrix* initMatrix(int size) {

    printf("size: %d\n", size);
    Matrix* matrix = malloc(sizeof(Matrix));
    matrix -> size = size;

    void ***data = malloc(sizeof(void*) * size);

    for(int i = 0; i < size; i++) {
       data[i] = calloc(size,sizeof(void*));
    }
    matrix -> data = data;

    //free(data);

    return matrix;
}



void *searchInMatrix(Matrix *matrix, int x, int y) {

    if(matrix -> data[y][x] == NULL) {
       return NULL;
    }
    else {
    
        return matrix -> data[y][x];

    }
}


void insertInMatrix(Matrix *matrix, void *info, int x, int y) {

    matrix -> data[y][x] = info;

}



void deleteShipMatrix(Matrix *ma, int x, int y, int numberPoints) {
    
    void *cell = searchInMatrix(ma,x,y); 
    SHIP *sh = getShipCell(cell);
    BitMap *bp = getBitMapShip(sh); 
    int xRef = getXandY(bp,'x'); 
    int yRef = getXandY(bp,'y');

        for(int i = 0; i < sizeBitMap; i++) {
          for(int j = 0; j < sizeBitMap; j++) {
              if(bp -> data[j][i] == '1') {
                  void *aux = searchInMatrix(ma,j+yRef,i+xRef);
                  free(aux);
              }
          }

        }
    }



// Free allocated memory
void freeMatrix(Matrix *matrix) {
     for(int i=0; i< matrix -> size; i++) {
        free(matrix -> data[i]);
     }

    free(matrix -> data);
    free(matrix);
}


/*
int main() {

    Matrix *matrix = initMatrix(20);

    void *searchPoint = searchInMatrix(matrix,2,3);

    Cell *cell = initCell(); 

    insertInMatrix(matrix, cell, 2,3);

    void *searchPoint1 = searchInMatrix(matrix,2,3);

}

*/
