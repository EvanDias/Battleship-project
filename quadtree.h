#include "point.h"
#include "list.h"

typedef struct PointQuad_ PointQuad;
typedef struct Quad_ QuadTree;
typedef struct NodeLeaf_ NodeLeaf;
typedef struct NodeFather_ NodeFather;

typedef enum {NODELEAF, NODEFATHER} nodetype;


#define BOUNDARY 4


struct PointQuad_ {

    Point *position; 
    void *data;
};

struct Quad_ {

    Point *bottonLeft;
    Point *topRight;

    nodetype node;

    union {

        NodeLeaf *nodeleaf;
        NodeFather *nodefather;

    }type;

};

struct NodeLeaf_ {

    List *points;

};


struct NodeFather_ {

    List *child;

};


PointQuad *initPointQuad(Point *p, void *value);
NodeLeaf *initNodeLeaf();
NodeFather *initNodeFather();
QuadTree *initQuad(Point *buttonLeft, Point *topRight, nodetype kind);
void insertQuad(QuadTree *quad, PointQuad *p);
int canInsertQuad(QuadTree *quad, PointQuad *p);
void subdive(QuadTree *quad);
void goThroughFatherInsert(QuadTree *quad, PointQuad *p);
void deleteQuadNodeLeaf(QuadTree *quad);
