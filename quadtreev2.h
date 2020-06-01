#include "cell.h"


typedef enum {NODELEAF, NODEFATHER} nodeType;
typedef enum {FIRST, SECOND, THIRD, FOURTH} quadChilds;

typedef struct Quad_ QuadTree;
typedef struct QuadPoint_ QuadPoint;
typedef struct QuadChilds_ QuadChilds;

#define BOUNDARY 1;

struct QuadPoint_ {

    Point *position;
    void *data;

};

struct Quad_ {

    Point *middlePoint;
    int dimension;

    nodeType type;

    union {
        QuadTree **children;
        QuadPoint *data;

    } contentNode;
};


QuadPoint *initQuadPoint(Point *point, void *data);
int dimensionQuad(int size);
QuadTree *initQuadInitial(int size);
QuadTree *initQuad(Point *middlePoint, nodeType type, int size);
Point *getPositionQuadPoint(QuadPoint *quadPoint);
void *getDataQuadPoint(QuadPoint *quadPoint);
void insertQuad(QuadTree *quad, void *data, Point *p);
void subdivide(QuadTree *quad);
quadChilds whichQuadrant(QuadTree *quad, Point *p);
Point *newMiddlePoint(QuadTree *quad, int new_dimension, int i);
void goThroughtFather(QuadTree *father, QuadPoint *pqpoint);
int chooseQuad(QuadTree *quad, Point *p);
int whatQuadrants(QuadTree *quad, QuadPoint *pq);
void *searchQuad(QuadTree *quad, Point *p);
void *searchFather(QuadTree *quad, Point *p);
void printQuadTree(QuadTree *quad, int gameBoardSize);
void deletePointQuad(QuadTree *quad, void *data,Point *p);
void deleteFather(QuadTree *quad, void *data,Point *p);
void freeQuadPoint(QuadPoint *pq);
//int numberPointsInserted(QuadTree *quad);
