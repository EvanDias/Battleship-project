#include "quadtreev2.h"



QuadPoint *initQuadPoint(Point *point, void *data) {

    QuadPoint *new =malloc(sizeof(QuadPoint)); 

    new -> position = point; 
    new -> data = data; 

    return new;

}

int dimension(int size) {

    if(size <= 31) return 32;

    else return 64;


}


/*

QuadChilds *initQuadChilds(quadChilds typeChild, Point *middlePoint, int size) {

    QuadChilds *new = malloc(sizeof(QuadChilds));

    if(typeChild == FIRST) new -> quadrant.first = initQuad(middlePoint, NODELEAF,size); 
    else if(typeChild == SECOND) new -> quadrant.second = initQuad(middlePoint, NODELEAF,size);
    else if(typeChild == THIRD) new -> quadrant.third = initQuad(middlePoint, NODELEAF,size);
    else if(typeChild == FOURTH) new -> quadrant.fourth = initQuad(middlePoint, NODELEAF,size);

    return new;
}

*/

QuadTree *initQuad(Point *middlePoint, nodeType type, int size) {

    QuadTree *new = malloc(sizeof(QuadTree));

    new -> dimension = size; 

    printf("dimension: %d\n", new -> dimension);

    new -> middlePoint = middlePoint;

    if(type == NODELEAF)  {
        new -> contentNode.data = NULL;
        new -> contentNode.count = 0;
    }
    else {
        
        for(int i = 0; i < 4; i++) {
            new -> contentNode.children[i] = NULL;
        }
    }
    return new; 
}


bool inBoundary(QuadTree *quad, QuadPoint *p) {

    if(p -> position -> x >= (quad -> middlePoint -> x) - ((quad -> dimension)/2)&&
       p -> position -> x <= (quad -> middlePoint -> x) + ((quad -> dimension)/2) &&
       p -> position -> y >= (quad -> middlePoint -> y) - ((quad -> dimension)/2)  &&
       p -> position -> y <= (quad -> middlePoint -> y) + ((quad -> dimension)/2)) return true;

    else return false;

}

void insertQuad(QuadTree *quad, QuadPoint *qPoint) {


    
    if(inBoundary(quad, qPoint) == false) {
        printf("Não pode inserir\n");
        return;

    }

        printf("PONTO A INSERIR: x -> %d  y -> %d\n", qPoint -> position -> x, qPoint -> position -> y);


    if(quad -> type == NODELEAF) {
        if(quad -> contentNode.data == NULL) {
       // quadChilds type = whichQuadrant(quad, qPoint -> position);
        printf("inseriu  no quadrante com o ponto médio x: %d   y_: %d\n", quad -> middlePoint -> x, quad -> middlePoint -> y);
        quad -> contentNode.data = qPoint;
        return;
        }

        else {
            subdivide(quad);
            insertQuad(quad, qPoint);
        }
    }

    else if(quad -> type == NODEFATHER) {
        goThroughtFather(quad, qPoint);
    }
}

void goThroughtFather(QuadTree *father, QuadPoint *pqpoint) {
    
    int choose = chooseQuad(father, pqpoint -> position);

    printf("choose: %d\n", choose);

    if(choose <= 3) {

        insertQuad(father -> contentNode.children[choose], pqpoint);

    }

    else if(choose == 5) {

    for(int i = 0; i < 4; i++) {
       insertQuad(father -> contentNode.children[i], pqpoint);
     }

    }
}


void subdivide(QuadTree *quad) {

    printf("SUBDIVIR\n");
    QuadPoint *pointQuad = quad -> contentNode.data;

    int currentDimension = (quad -> dimension)/2;

    quad -> type = NODEFATHER; 

    for(int i = 0; i < 4; i++) {

        Point *newMiddlePoint1 = newMiddlePoint(quad, currentDimension, i); 
        printf("i: %d   point x: %d  e  y: %d\n",i, newMiddlePoint1 -> x, newMiddlePoint1 -> y);
        quad -> contentNode.children[i] = initQuad(newMiddlePoint1,NODELEAF,currentDimension);               
    }

    insertQuad(quad, pointQuad);
}


quadChilds whichQuadrant(QuadTree *quad, Point *p) {

    int x_bottomLeft = (quad -> middlePoint -> x) - ((quad -> dimension)/4);
    int y_bottomLeft = (quad -> middlePoint -> y) - ((quad -> dimension)/4);
    int x_topRight = (quad -> middlePoint -> x) + ((quad -> dimension)/4);
    int y_topRight = (quad -> middlePoint -> y) + ((quad -> dimension)/4);
    int x = p -> x, y = p -> y;

    if(x >= (x_topRight/2) && y >= (y_topRight / 2)) {
        printf("1º Quadrant\n");
        return FIRST;
        } 
        
    else if(x <= (x_topRight/2) && y >= (y_topRight / 2)) {
        printf("2º Quadrant\n");
        return SECOND;
        } 

    else if(x <= (x_topRight/2) && y <= (y_topRight / 2)) {
        printf("3º Quadrant\n");
        return THIRD;
        } 
    
    else {
        printf("4º Quadrant\n");
        return FOURTH;
        }
} 


Point *newMiddlePoint(QuadTree *quad, int new_dimension, int i) {
    int x_curMiddle = quad -> middlePoint -> x;
    int y_curMiddle = quad -> middlePoint -> y;

    new_dimension = new_dimension / 2; 

    Point *newMiddlePoints = NULL;
    switch (i)
    {
        case 0:
            newMiddlePoints = newPoint(x_curMiddle + new_dimension, x_curMiddle + new_dimension); 
            break;
        case 1:
            newMiddlePoints = newPoint(new_dimension, x_curMiddle + new_dimension); 
            break;
        case 2:
            newMiddlePoints = newPoint(new_dimension, new_dimension); 
            break;
        case 3:
            newMiddlePoints = newPoint(x_curMiddle + new_dimension, new_dimension); 
            break;
        default:
            printf("ERROR");
            break;
        }

    return newMiddlePoints;
} 

int chooseQuad(QuadTree *quad, Point *p) {
    int x_middle = quad -> middlePoint -> x;
    int y_middle = quad -> middlePoint -> y;
    int x = p -> x, y = p -> y;
// up
    if(x == x_middle && y > y_middle) return 1;
// dow
    else if(x == x_middle && y < y_middle) return 2;
// left
    else if(y == y_middle && x < x_middle) return 2;
// right
    else if(y == y_middle && x > x_middle) return 3;
// center
    else if(x == x_middle && y == y_middle) return 2;

    else if(y == y_middle && x >= x_middle) return 0;

    else return 5;

} 


int main() {

    Point *p1 = newPoint(9,1); 
    Point *p2 = newPoint(3,4); 
    Point *p3 = newPoint(1,2);
    Point *p4 = newPoint(8,8);
    Point *p5 = newPoint(2,8);
    Point *p6 = newPoint(3,8);


    QuadPoint *pq1 = initQuadPoint(p1, "ola");
    QuadPoint *pq2 = initQuadPoint(p2, "ola");
    QuadPoint *pq3 = initQuadPoint(p3,"ola");
    QuadPoint *pq4 = initQuadPoint(p4,"ola");
    QuadPoint *pq5 = initQuadPoint(p5,"ola");
    QuadPoint *pq6 = initQuadPoint(p6,"ola");

    Point *middlePoint = newPoint(16,16);
    QuadTree *center = initQuad(middlePoint, NODELEAF, 32);
    
   // int i = chooseQuad(center,p3);
    //printf("%d\n", i);
    insertQuad(center, pq2);   
    insertQuad(center, pq3);
    insertQuad(center, pq1); 
    insertQuad(center, pq4);
    insertQuad(center, pq5);
    insertQuad(center, pq6);


    return 0;
}