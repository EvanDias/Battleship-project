#include "quadtree.h"



PointQuad *initPointQuad(Point *p, void *value) {

    PointQuad *new = malloc(sizeof(PointQuad));
    
    new -> pos = p; 
    new -> data = value;

    return new;

}

NodeLeaf *initNodeLeaf() {

    NodeLeaf *new = malloc(sizeof(NodeLeaf));

    new -> points = initList();

    return new;

}

NodeFather *initNodeFather() {

    NodeFather *new = malloc(sizeof(NodeFather));

    new -> child = initList();

    return new;

}


QuadTree *initQuad(Point *bottonLeft, Point *topRight, nodetype kind) {

    QuadTree *new = malloc(sizeof(QuadTree));

    new -> bottonLeft = bottonLeft;
    new -> topRight = topRight; 
    
    new -> node = kind;

    if(kind == NODELEAF) new -> type.nodeleaf = initNodeLeaf(); 

    else new -> type.nodefather = initNodeFather();

    return new;
}


void insertQuad(QuadTree *quad, PointQuad *p) {

    int insert = canInsertQuad(quad,p);
    
    if(insert == 0) {
        printf("Can't insert point\n");
    }

    else if(quad -> node == NODELEAF) {

        if(quad -> type.nodeleaf -> points -> size == 0 || quad -> type.nodeleaf -> points -> size <= BOUNDARY) headList(quad -> type.nodeleaf -> points,p);

        else {
            subdive(quad);
            goThroughFatherInsert(quad,p);
            
        }
    }

    else {
        goThroughFatherInsert(quad,p);
    }
    
}


//retornar bool 

int canInsertQuad(QuadTree *quad, PointQuad *p) {

    if(p -> pos -> x <= quad -> bottonLeft -> x && 
    p -> pos -> y >= quad -> bottonLeft -> y &&
    p -> pos -> x >= quad -> topRight -> x &&
    p -> pos -> y <= quad -> topRight -> y) return 0;
    
    else return 1;

}

void subdive(QuadTree *quad){

    QuadTree *new = initQuad(quad -> bottonLeft, quad -> topRight, NODEFATHER);

    Point *bottonLeft = quad -> bottonLeft; 
    Point *topRight = quad -> topRight;

    Point *neL = newPoint(2*(bottonLeft->x),2*(bottonLeft -> y));
    Point *neR = newPoint(topRight -> x, topRight->y);
    QuadTree *firstQuad = initQuad(neL, neR, NODELEAF); 
    Point *nwL = newPoint(bottonLeft->x,2*(bottonLeft -> y));
    Point *nwR = newPoint((topRight -> x)/2, topRight->y);
    NodeLeaf *secondQuad = initQuad(nwL,nwR,NODELEAF);
    Point *swL = newPoint(bottonLeft->x,bottonLeft -> y);
    Point *swR = newPoint((topRight -> x)/2, (topRight->y)/2); 
    NodeLeaf *thirdQuad = initQuad(swL,swR,NODELEAF); 
    Point *seL = newPoint((bottonLeft->x)*2,bottonLeft -> y);
    Point *seR = newPoint(topRight -> x, (topRight->y)/2); 
    NodeLeaf *fourthQuad = initQuad(seL,seR,NODELEAF);

    headList(new -> type.nodefather -> child, firstQuad);
    headList(new -> type.nodefather -> child, secondQuad);
    headList(new -> type.nodefather -> child, thirdQuad);
    headList(new -> type.nodefather -> child, fourthQuad);

}


void goThroughFatherInsert(QuadTree *quad, PointQuad *p) {

      ListNode *nodeAux = quad -> type.nodefather -> child -> head;

        while( nodeAux != NULL) {
            insertQuad(nodeAux -> data, p);
            nodeAux =  nodeAux -> next;
        }
}


/*
void main(){


    Point *bottonLeft = newPoint(0,0);
    Point *topRight = newPoint(10,10);

    QuadTree *center = initQuad(bottonLeft,topRight, NODELEAF);

    Point *p1 = newPoint(1,2);
    Point *p2 = newPoint(4,4);
    Point *p3 = newPoint(7,7);
    Point *p4 = newPoint(9,9);
    Point *p5 = newPoint(6,6);
    PointQuad *pq1 = initPointQuad(p1,0);
    PointQuad *pq2 = initPointQuad(p2,1);
    PointQuad *pq3 = initPointQuad(p3,1);
    PointQuad *pq4 = initPointQuad(p4,5);
    PointQuad *pq5 = initPointQuad(p5,1);

    insertQuad(center,pq1);
    insertQuad(center,pq2);
    insertQuad(center,pq3);
    insertQuad(center,pq4);
    insertQuad(center,pq5);


}


*/