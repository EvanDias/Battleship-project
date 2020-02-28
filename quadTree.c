#include <stdio.h>
#include <stdlib.h>
#include "quadTree.h"

#define SQUARE 4


Nodes* initNodes(NodeKind kind, Point* p1, Point* p2, void* set) {

    Nodes* newResult = malloc(sizeof(Nodes));
    newResult -> kind = kind;

    //Para não fazer a situação de ter que escrever as duas opções da union, utilizamos um void*
    if(kind == LEAVES) newResult -> possible.leaves = set;
    else if(kind == INTERNODES) newResult -> possible.nodesInter = set;

    newResult -> p1 = p1; 
    newResult -> p2 = p2;

    return newResult;

}

Leaves* initLeaves(Point * * points) {

    Leaves* newResult = malloc(sizeof(Leaves));
    newResult -> points = malloc(MAX_POINT * sizeof(Point*));

    return newResult;


}

InterNodes* initInterNodes(Nodes * * interNodes) {

    InterNodes* newResult = malloc(sizeof(InterNodes));
    newResult -> interNodes = malloc(SQUARE * sizeof(Nodes*));

    return newResult;

}



