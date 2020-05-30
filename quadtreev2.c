#include "quadtreev2.h"
#include <math.h>
#include <unistd.h>

#define maxArray(array) ({int max = -1; \
    for(int i = 0; i < 4; i++) {   \
        if(max < array[i]) max = array[i];}\
     max;\
})

static int count = 0;


QuadPoint *initQuadPoint(Point *point, void *data) {

    QuadPoint *new =malloc(sizeof(QuadPoint));
    new -> position = newPoint(point -> x, point -> y);
    new -> data = data;

    return new;

}


void *getDataQuadPoint(QuadPoint *quadPoint) {



    return quadPoint -> data;
}

Point *getPositionQuadPoint(QuadPoint *quadPoint) {

    return quadPoint -> position;
}

int dimensionQuad(int size) {
    return 32;
}


QuadTree *initQuadInitial(int boardSize) {

    int dimension = dimensionQuad(boardSize);

    Point *mPoint = newPoint(0, 0);

    QuadTree *new = initQuad(mPoint,NODELEAF,dimension);

}

QuadTree *initQuad(Point *middlePoint, nodeType type, int size) {

    QuadTree *new = malloc(sizeof(QuadTree));

    new -> dimension = size;

    new->type = type;

    new -> middlePoint = middlePoint;

    if(type == NODELEAF) new -> contentNode.data = NULL;

    else {

        for(int i = 0; i < 4; i++) {
            new -> contentNode.children[i] = NULL;
        }
    }
    return new;
}


bool inBoundary(QuadTree *quad, Point *position) {
    
    int dimensions = quad->dimension;

    Point *p = quad->middlePoint;

   // printf("DIMENSIONS %d\n", dimensions);

   //printf("POINTTTT x: %d e y: %d\n", position -> x, position -> y);

    //Como guardamos apenas o canto mais pequeno do quadrado, não é necessario dividir o dimensions
    int x_small = p->x, x_large = p-> x + dimensions,
        y_small = p->y, y_large = p->y + dimensions;
    
    //printf("Checking X: %d small %d large %d Y: %d small %d large %d dimensions %d\n", p->x, x_small, x_large, p->y, y_small, y_large, dimensions);

    if (x_small <= position->x && position->x < x_large && y_small <= position->y && position->y < y_large) {
        //printf("pertence a este quad \n");
        return true;
    }


    //printf("Não pertence ao quad \n");
    return false;
}

void insertQuad(QuadTree *quad, void *data, Point *p) {

    QuadPoint *qPoint = initQuadPoint(p,data);

    if(inBoundary(quad, qPoint -> position) == false) {
        printf("Não pode inserir\n");
        return;

    }

    /*printf("PONTO A INSERIR: x -> %d  y -> %d\n", qPoint -> position -> x, qPoint -> position -> y);

    printf("QUAD: x -> %d    y -> %d\n",quad -> middlePoint -> x, quad -> middlePoint -> y );

    printf("quad dimension : %d\n", quad -> dimension);

    */
    if(quad -> type == NODELEAF) {
        if(quad -> contentNode.data == NULL) {
        printf("PONTOssss X: %d e Y: %d\n", qPoint -> position -> x, qPoint -> position -> y);
       // quadChilds type = whichQuadrant(quad, qPoint -> position);
        printf("inseriu  no quadrante com o ponto médio x: %d   y_: %d\n", quad -> middlePoint -> x, quad -> middlePoint -> y);
        printf("INSERI\n");
        quad -> contentNode.data = qPoint;
        } else {
            subdivide(quad);
            insertQuad(quad, data, p);
        }
    }

    else if(quad -> type == NODEFATHER) {

        //printf("FATHER\n");
        goThroughtFather(quad, qPoint);
    } else {
        printf("WTF\n");
    }
}

void goThroughtFather(QuadTree *father, QuadPoint *pqpoint) {

    int array = whatQuadrants(father,pqpoint);

    void *data = getDataQuadPoint(pqpoint);
    Point *p = getPositionQuadPoint(pqpoint);

    //printf("PONTO -> X: %d e Y: %d\n", p -> x, p -> y);
    //printf("dimension: %d\n", father -> dimension);

    if(array != -1) insertQuad(father -> contentNode.children[array], data,p);

    else printf("Não dá para inserir nenhum\n");
         
}

void subdivide(QuadTree *quad) {

    printf("SUBDIVIR\n");
    QuadPoint *pointQuad = quad -> contentNode.data;

    int currentDimension = (quad -> dimension); 
    int newDimension = 0;
    
    newDimension = currentDimension/2;

    quad -> type = NODEFATHER;

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
    
    if(inBoundary(quad -> contentNode.children[2], pq -> position)) return 2;

    for(int i = 0; i < 4; i++) {
        if(inBoundary(quad -> contentNode.children[i], pq -> position)) return i;
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

    else if(quad -> type == NODELEAF) {

        if(quad -> contentNode.data != NULL &&
           quad -> contentNode.data -> position -> x == p -> x &&
           quad -> contentNode.data -> position -> y == p -> y) {
            data = quad -> contentNode.data -> data;
            return data;
        }

        else {
          return data = NULL;
        }

    }

    else if(quad -> type == NODEFATHER) {
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


QuadPoint **allChildrens(QuadTree *quad, int gameBoardSize,int numberPoints)  {

    int k = 0;

    QuadPoint *pq = NULL;

    QuadPoint **allChildrens = malloc(numberPoints*sizeof(QuadPoint));


    for(int i = 0; i < gameBoardSize; i++) {
        for(int j = 0; j < gameBoardSize; j++) {
            Point *p1 = newPoint(i,j);
            pq = searchQuad(quad, p1);
            if(pq != NULL) {
                allChildrens[k] = pq;
                k++;
            }
        }
    }

    return allChildrens;
}


void deletePointQuad(QuadTree *quad, Point *p, int numberPoints) {

    QuadPoint **quadPointss = allChildrens(quad, 20, numberPoints);

    if(inBoundary(quad, p) == false) {

        printf("Não dá para eliminar");
        return;

    }

    for(int i = 0; i < numberPoints; i++) {

        if(quadPointss[i] -> position -> x == p -> x &&
           quadPointss[i] -> position -> y == p -> y) {
               deletePoint(quadPointss[i] -> position);
               quadPointss[i] = NULL;
           }

    }


    Point *middlePoint = quad -> middlePoint;
    int size = quad -> dimension;


    //free(quad);

   quad =  initQuad(middlePoint, NODELEAF,size);

    for(int i = 0; i < numberPoints; i++) {

        if(quadPointss[i] != NULL) {
            Point *p = quadPointss[i] -> position;
            void *data = quadPointss[i] -> data;
            insertQuad(quad,data,p);
        }
    }


}



void printQuadTree(QuadTree *quad, int gameBoardSize) {

    printf("\n");
    printf("  A ");

    char c1 = 'B';
    for(int i=1; i < gameBoardSize; i++) {
        printf("%c ", c1);
        c1++;
        if(c1 == '[') c1 = 'a';
    }
    printf("\n");
    c1 = 'A';
    for(int i = 0; i < gameBoardSize; i++) {
        printf("%c ", c1);
        c1++;
        if(c1 == '[') c1 = 'a';

      for(int j = 0; j < gameBoardSize; j++) {

        Point *aux = newPoint(j,i);
        if(searchQuad(quad, aux) != NULL) printf("x ");
        else printf(". ");
        free(aux);
      }
    printf("\n");
    }
}

int numberPointsInserted(QuadTree *quad) {

    if(quad -> type == NODELEAF) {

        if(quad -> contentNode.data != NULL) count += 1;
    }

    else if(quad -> type == NODEFATHER) {

        for(int i = 0; i < 4; i++) numberPointsInserted(quad -> contentNode.children[i]);

    }

    return count;

}



/*
int main() {

    Point *p1 = newPoint(0,0);
    Point *p2 = newPoint(0,1);
    Point *p3 = newPoint(0,2);
    Point *p4 = newPoint(0,3);
    Point *p5 = newPoint(1,0);
    Point *p6= newPoint(1,1);
    Point *p7 = newPoint(1,2);
    Point *p8 = newPoint(1,3);
    Point *p9 = newPoint(2,0);
    Point *p10 = newPoint(2,1);
    Point *p11 = newPoint(2,2);
    Point *p12 = newPoint(2,3);
    Point *p13 = newPoint(3,0);
    Point *p14 = newPoint(3,1);
    Point *p15 = newPoint(3,2);
    Point *p16 = newPoint(3,3);

    Point *middlePoint = newPoint(16,16);
    QuadTree *center = initQuadInitial(20);

    //bool boundary = inBoundary(center, p6);

   // int i = chooseQuad(center,p3);


    insertQuad(center, "ola", p2);
    insertQuad(center, "ola", p3);
    //insertQuad(center, "ola", p4);
    //insertQuad(center, "ola", p5);
    insertQuad(center, "ola", p1);
    insertQuad(center, "ola", p6);
    insertQuad(center, "ola", p7);
    insertQuad(center, "ola", p8);
    insertQuad(center, "ola", p9);
    insertQuad(center, "ola", p10);
    insertQuad(center, "ola", p11);
    insertQuad(center, "ola", p12);
    insertQuad(center, "ola", p13);
    insertQuad(center, "ola", p14);
    insertQuad(center, "ola", p15);
    insertQuad(center, "ola", p16);


    // Point *array[16] = {NULL};

//    void *encontrei1 = searchQuad(center,p1);
    void *encontrei2 = searchQuad(center,p2);
    void *encontrei3 = searchQuad(center,p3);
    void *encontrei4 = searchQuad(center,p4);
    void *encontrei5 = searchQuad(center,p5);
    void *encontrei6 = searchQuad(center,p6);
    void *encontrei7 = searchQuad(center,p7);
    void *encontrei8 = searchQuad(center,p8);
    void *encontrei9 = searchQuad(center,p9);
    void *encontrei10 = searchQuad(center,p10);
    void *encontrei11 = searchQuad(center,p11);
    void *encontrei12 = searchQuad(center,p12);
    void *encontrei13 = searchQuad(center,p13);
    void *encontrei14 = searchQuad(center,p14);
    void *encontrei15 = searchQuad(center,p15);
    void *encontrei16 = searchQuad(center,p16);


    if(encontrei2 == NULL) {
        printf("Está Nulo\n");
    }

    else printf("Não está nulo\n");

   
    return 0;

}
*/
