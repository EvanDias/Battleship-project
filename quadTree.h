#pragma once
#include <stdio.h>
#include "point.h"

#define MAX_POINT 5


typedef enum {LEAVES, INTERNODES} NodeKind;
typedef struct Leaves_ Leaves;
typedef struct InterNodes_ InterNodes;
typedef struct Nodes_ Nodes;

struct Leaves_ {

    Point * * points;

};

struct InterNodes_ {


    Nodes * * interNodes;

};


struct Nodes_ {

    NodeKind kind; 
    Point* p1;
    Point* p2;

    union { 

        Leaves* leaves;
        InterNodes* nodesInter;

    } possible;


};


Nodes* initNodes(NodeKind kind, Point* p1, Point* p2);
Leaves* initLeaves(Point * * points);
InterNodes* initInterNodes(Nodes * * interNodes);
















