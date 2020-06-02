#include "cell.h"


typedef enum {NODELEAF, NODEFATHER} nodeType;
typedef enum {FIRST, SECOND, THIRD, FOURTH} quadChilds;

typedef struct Quad_ QuadTree;
typedef struct QuadPoint_ QuadPoint;
typedef struct QuadChilds_ QuadChilds;

#define QUADNL(Q) (Q -> contentNode.data)
#define SETQUADPOINTNL(Q, v) (Q -> contentNode.data = v)
#define SETQUADPOINTCHILD(Q,i,v) (Q -> contentNode.children[i] = v)
#define DATAQUADPOINT(QP) (QP -> data)
#define SETDATAQUADPOINT(QP, d) (QP -> data = d)
#define POSQUADPOINT(QP) (QP -> position)
#define SETPOSQUADPOINT(QP,p) (QP -> position = p)
#define MIDDLEPOINT(Q) (Q -> middlePoint)
#define SETMIDDLEPOINT(Q, p) (Q -> middlePoint = p) 
#define DIMENSION(Q) (Q -> dimension)
#define SETDIMENSION(Q,s) (Q -> dimension = s)
#define TYPE(Q) (Q -> type)
#define SETTYPE(Q,t) (Q -> type = t)



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


QuadTree *initQuadInitial(int size);
void insertQuad(QuadTree *quad, void *data, Point *p);
int chooseQuad(QuadTree *quad, Point *p);
void *searchQuad(QuadTree *quad, Point *p);
void deletePointQuad(QuadTree *quad, void *data,Point *p);
void freeQuadPoint(QuadPoint *pq);
//int numberPointsInserted(QuadTree *quad);
