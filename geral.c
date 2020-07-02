#include "geral.h" 

#ifdef MATRIX
#include "matrix.h"

void *initDataStructure(int size) {
    return initMatrix(size);
}

void *searchPoint(void *structure, Point *p) {
    int x = COORDX(p); 
    int y = COORDY(p);
    //printf("fiz o ponto dentro do searchPoint\n");
    Matrix *m = (Matrix*)structure;
   // printf("STRUCTURE SIZE: %d\n", m -> size);
    return searchInMatrix(m, x, y);
}

void insertShip(void *structure, void *information, Point *p) {
    int x = COORDX(p); 
    int y = COORDY(p);
    return insertInMatrix((Matrix*)structure, information, x, y);
}

void deleteShip(void *structure, void *data, Point *p) {
    int x = COORDX(p); 
    int y = COORDY(p);
    return deleteShipMatrix((Matrix*)structure, data, x, y);

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

void deleteShip(void *structure, void *ship, Point *p) {
    return deletePointQuad((QuadTree*)structure,ship,p);

}


void freeDataStructure(void *structure) {
    printf("ola\n");
}


#endif 
