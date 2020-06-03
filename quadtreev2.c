#include "quadtreev2.h"
#include <math.h>
#include <unistd.h>


static QuadPoint *initQuadPoint(Point *point, void *data);
static int dimensionQuad(int size);
static QuadTree *initQuad(Point *middlePoint, nodeType type, int size);
static bool inBoundar(QuadTree *quad, Point *position);
static void subdivide(QuadTree *quad);
static void goThroughtFather(QuadTree *father, QuadPoint *pqpoint);
static int whatQuadrants(QuadTree *quad, QuadPoint *pq);
static Point *newMiddlePoint(QuadTree *quad, int new_dimension, int i);
static void *searchFather(QuadTree *quad, Point *p);
static void deleteFather(QuadTree *quad, void *data,Point *p);

QuadPoint *initQuadPoint(Point *point, void *data) {

    QuadPoint *new =malloc(sizeof(QuadPoint));
    SETPOSQUADPOINT(new,newPoint(point -> x, point -> y));
    SETDATAQUADPOINT(new,data);

    return new;

}

int dimensionQuad(int size) {

    if(size <= 31) return 32; 
    else return 64;

}


QuadTree *initQuadInitial(int boardSize) {
   
    int dimension = dimensionQuad(boardSize);

    Point *mPoint = newPoint(0, 0);

    QuadTree *new = initQuad(mPoint,NODELEAF,dimension);

}

QuadTree *initQuad(Point *middlePoint, nodeType type, int size) {

    QuadTree *new = malloc(sizeof(QuadTree));

    SETDIMENSION(new,size);

    SETTYPE(new,type);

    SETMIDDLEPOINT(new,middlePoint);

    if(type == NODELEAF) new -> contentNode.data = NULL;

    else {

        for(int i = 0; i < 4; i++) {
            new -> contentNode.children[i] = NULL;
        }
    }
    return new;
}

bool inBoundary(QuadTree *quad, Point *position) {
    
    int dimensions = DIMENSION(quad);

    Point *p = MIDDLEPOINT(quad);

   // printf("DIMENSIONS %d\n", dimensions);

   //printf("POINTTTT x: %d e y: %d\n", position -> x, position -> y);

    //Como guardamos apenas o canto mais pequeno do quadrado, não é necessario dividir o dimensions
    int x_small = COORDX(p), x_large = COORDX(p) + dimensions,
        y_small = COORDY(p), y_large = COORDY(p) + dimensions;
    
    //printf("Checking X: %d small %d large %d Y: %d small %d large %d dimensions %d\n", p->x, x_small, x_large, p->y, y_small, y_large, dimensions);

    if (x_small <= COORDX(position) && COORDX(position) < x_large && y_small <= COORDY(position) && COORDY(position) < y_large) {
        //printf("pertence a este quad \n");
        return true;
    }


    //printf("Não pertence ao quad \n");
    return false;
}

void insertQuad(QuadTree *quad, void *data, Point *p) {

    QuadPoint *qPoint = initQuadPoint(p,data);

    if(inBoundary(quad, POSQUADPOINT(qPoint)) == false) {
        printf("Não pode inserir\n");
        return;

    }

     if(TYPE(quad) == NODELEAF) {
        if(quad -> contentNode.data == NULL) {
       // quadChilds type = whichQuadrant(quad, qPoint -> position);
       printf("inseriu\n");
        quad -> contentNode.data = qPoint;
        } else {
            subdivide(quad);
            insertQuad(quad, data, p);
        }
    }

    else if(TYPE(quad) == NODEFATHER) {

        //printf("FATHER\n");
        goThroughtFather(quad, qPoint);
    } else {
    }
}

void goThroughtFather(QuadTree *father, QuadPoint *pqpoint) {

    int array = whatQuadrants(father,pqpoint);

    void *data = DATAQUADPOINT(pqpoint);
    
    Point *p = POSQUADPOINT(pqpoint);

    if(array != -1) insertQuad(father -> contentNode.children[array], data,p);
         
}

void subdivide(QuadTree *quad) {

    printf("SUBDIVIR\n");
    QuadPoint *pointQuad = quad -> contentNode.data;

    int currentDimension = DIMENSION(quad); 
    int newDimension = 0;
    
    newDimension = currentDimension/2;

    SETTYPE(quad, NODEFATHER);

    quad->contentNode.children = malloc(sizeof(QuadTree*) * 4);

    for(int i = 0; i < 4; i++) {

        Point *newMiddlePoint1 = newMiddlePoint(quad, newDimension, i);

        //printf("i: %d   point x: %d  e  y: %d dimension %d\n",i, newMiddlePoint1 -> x, newMiddlePoint1 -> y, newDimension);

        quad -> contentNode.children[i] = initQuad(newMiddlePoint1,NODELEAF,newDimension);
    }

    insertQuad(quad, pointQuad ->data, pointQuad -> position);

    //TODO:Free point quad

}
int whatQuadrants(QuadTree *quad, QuadPoint *pq) {
    
    if(inBoundary(quad -> contentNode.children[2], POSQUADPOINT(pq))) return 2;

    for(int i = 0; i < 4; i++) {
        if(inBoundary(quad -> contentNode.children[i], POSQUADPOINT(pq))) return i;
    }

    return -1;
}


static int dirs[4][2] = {{1, 1}, {0, 1}, {0, 0}, {1, 0}};

Point *newMiddlePoint(QuadTree *quad, int new_dimension, int i) {
    int x_curMiddle = COORDX(quad->middlePoint);
    int y_curMiddle = COORDY(quad->middlePoint);

    if (i >= 0 && i <= 3) 
        return newPoint(x_curMiddle + dirs[i][0] * new_dimension, 
            y_curMiddle + dirs[i][1] * new_dimension);

    perror("Failed to create middle point, out of bounds\n");
    exit(1);
}


void *searchQuad(QuadTree *quad, Point *p) {

    void *data = NULL;

    if(inBoundary(quad, p) == false) {
        //printf("O ponto não pode estar contido\n");
        return data = NULL;
    }

    else if(TYPE(quad) == NODELEAF) {

        if(quad -> contentNode.data != NULL &&
           COORDX(POSQUADPOINT(quad -> contentNode.data)) == COORDX(p) &&
           COORDY(POSQUADPOINT(quad -> contentNode.data)) == COORDY(p)) {
            data = quad -> contentNode.data -> data;
            return data;
        }

        else {
          return data = NULL;
        }

    }

    else if(TYPE(quad) == NODEFATHER) {
        data = searchFather(quad, p);
    }

   return data;

}


void* searchFather(QuadTree *quad, Point *p) {
    void *searched = NULL;

    for(int i = 0; i < 4; i++) {

        searched = searchQuad(quad -> contentNode.children[i], p);

        if(searched != NULL) break;

    }

    return searched;
}

void deletePointQuad(QuadTree *quad, void *data,Point *p) {

    if(inBoundary(quad, p) == false) {
        return ;
    }

    else if(TYPE(quad) == NODELEAF) {
        if(quad -> contentNode.data != NULL &&
           COORDX(POSQUADPOINT(quad -> contentNode.data)) == COORDX(p) &&
           COORDY(POSQUADPOINT(quad -> contentNode.data)) == COORDY(p)) {
                   printf("delete\n");

           free(quad -> contentNode.data); 
           quad -> contentNode.data = NULL;
           return;
        }
    }

    else if(TYPE(quad) == NODEFATHER) {
        deleteFather(quad, data, p);
    }

}

void deleteFather(QuadTree *quad, void *data, Point *p) {

    for(int i = 0; i < 4; i++) {

        deletePointQuad(quad -> contentNode.children[i], data, p);

    }
}