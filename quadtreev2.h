#include "point.h"

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
        QuadTree *children[4];
        struct {
            QuadPoint *data;
            int count;
        };
    } contentNode; 
};

/*
struct QuadChilds_ {

    quadChilds quadChild; 

    union {
        QuadTree *first; 
        QuadTree *second; 
        QuadTree *third; 
        QuadTree *fourth;

    }quadrant;

};

*/




QuadPoint *initQuadPoint(Point *point, void *data);
QuadTree *initQuad(Point *middlePoint, nodeType type, int size);
void insertQuad(QuadTree *quad, QuadPoint *p);
void subdivide(QuadTree *quad);
quadChilds whichQuadrant(QuadTree *quad, Point *p);
Point *newMiddlePoint(QuadTree *quad, int new_dimension, int i);
void goThroughtFather(QuadTree *father, QuadPoint *pqpoint);
int chooseQuad(QuadTree *quad, Point *p);
