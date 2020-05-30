#include "geral.h" 

#ifdef MATRIX
#include "matrix.h"

void *initDataStructure(int size) {
    return initMatrix(size);
}

void *searchPoint(void *structure, Point *p) {
    int x = getX(p); 
    int y = getY(p);
    //printf("fiz o ponto dentro do searchPoint\n");
    Matrix *m = (Matrix*)structure;
   // printf("STRUCTURE SIZE: %d\n", m -> size);
    return searchInMatrix(m, x, y);
}

void insertShip(void *structure, void *information, Point *p) {
    int x = getX(p); 
    int y = getY(p);
    return insertInMatrix((Matrix*)structure, information, x, y);
}

void deleteShip(void *structure, Point *p,int numberPoints) {
    int x = getX(p); 
    int y = getY(p);
    return deleteShipMatrix((Matrix*)structure,x, y, 0);

}


void freeDataStructure(void *structure) {

    return freeMatrix((Matrix*)structure);
}


#endif 


#ifdef QUADTREE 
#include "quadtreev2.h"

void *initDataStructure(int size) {
    return initQuadInitial(size);
}

void *searchPoint(void *structure, Point *p) {

    //printf("Looking in point %d %d\n", p->x, p->y);

    return searchQuad((QuadTree*)structure, p);
    //return NULL;
}

void insertShip(void *structure, void *information, Point *p) {

    printf("Inserting in point %d %d\n", p -> x, p -> y);

    return insertQuad((QuadTree*)structure, information, p);
}

void deleteShip(void *structure, Point *p,int numberPoints) {
    return deletePointQuad((QuadTree*)structure,p, numberPoints);

}


void freeDataStructure(void *structure) {
    printf("ola\n");
}


#endif 
