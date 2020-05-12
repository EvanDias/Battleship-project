#include "quadtree.h"



PointQuad *initPointQuad(Point *p, void *value) {

    PointQuad *new = malloc(sizeof(PointQuad));

    new -> position = p;
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


/*
void insertQuad(QuadTree *quad, PointQuad *p) {

    Point *bottonLeft = quad -> bottonLeft;
    Point *topRight = quad -> topRight;

    QuadTree *firstQuad = NULL;
    QuadTree *secondQuad = NULL;
    QuadTree *thirdQuad = NULL;
    QuadTree *fourthQuad = NULL;


    if(p == NULL) return;

    if(canInsertQuad(quad, p) == 0) {
      return;
    }


    if (abs(bottonLeft -> x - topRight -> x) <= 1 &&
        abs(bottonLeft -> y - topRight -> y) <= 1)
    {
        PointQuad *point = NULL;
        if (point == NULL) {
            point = p;
            printf("INSERIU SEM SUBDIVIDIR\n");
          }
          return;
    }

    if(quad -> type.nodeleaf -> points -> size < BOUNDARY) {
      headList(quad -> type.nodeleaf -> points,p);
      printf("era do tipo leaf\n");
      return;
    }

    else {
    //left side
    if((bottonLeft -> x + topRight -> x)/2 >= p -> position -> x) {

        //Indicates secondQuad
        if((bottonLeft -> y + topRight -> y)/2 >= p -> position -> y) {
          if(secondQuad == NULL) {
            Point *nwL = newPoint((bottonLeft -> x), (bottonLeft -> y + topRight -> y)/2);
            Point *nwR = newPoint((bottonLeft->x + topRight -> x)/2, (topRight -> y));
            secondQuad = initQuad(nwL,nwR, NODELEAF);
            printf("inseriu no 2 quadrante\n");
          }
          insertQuad(secondQuad,p);
        }

        //indicates thirdQuad
        else {
          if(thirdQuad == NULL) {
            Point *swL = bottonLeft;
            Point *swR = newPoint((bottonLeft -> x + topRight -> x)/2, (bottonLeft -> y + topRight -> y)/2);
            thirdQuad = initQuad(swL,swR,NODELEAF);
            printf("inseriu no 3 quadrante\n");

          }
          insertQuad(thirdQuad, p);
        }
    }

    //right side
    else {

      //indicates firstQuad
      if((bottonLeft -> y + topRight -> y)/2 >= p -> position -> y) {
        if(firstQuad == NULL) {
          Point *neL = newPoint((bottonLeft -> x + topRight -> x)/2, (bottonLeft -> y + topRight -> y)/2);
          Point *neR = topRight;
          firstQuad = initQuad(neL,neR,NODELEAF);
          printf("inseriu no 1 quadrante\n");

        }
        insertQuad(firstQuad,p);
      }

      else {
        if(fourthQuad == NULL) {
          Point *seL = newPoint((bottonLeft -> x + topRight -> x)/2, bottonLeft -> y);
          Point *seR = newPoint((topRight -> x), (bottonLeft -> y + topRight -> y)/2);
          fourthQuad = initQuad(seL,seR,NODELEAF);
          printf("inseriu no 4 quadrante\n");

        }
        insertQuad(fourthQuad,p);
      }

    }
    }
}
*/


void insertQuad(QuadTree *quad, PointQuad *p) {

    int insert = canInsertQuad(quad,p);

   // printf("(x %d e y %d)\n", p -> position -> x, p -> position ->y);

    if(insert == 0) {
        printf("Can't insert point\n");
        //printf("point: x %d e y %d \n", p -> position -> x, p -> position ->y);
        //printf("%d\n",quad);
        return;
    }

    else if(quad -> node == NODELEAF) {

        if(quad -> type.nodeleaf -> points -> size == 0 || quad -> type.nodeleaf -> points -> size < BOUNDARY) {
          headList(quad -> type.nodeleaf -> points,p);
          printf("inseriu\n");
          return;
        }
        else {
          //  printf("quad, before: %d\n", quad -> node);
            subdive(quad);
            insertQuad(quad, p);
           // printf("quad, after: %d\n", quad -> node);
        }
    }

    else if(quad -> node == NODEFATHER) {
       // printf("YESSSSSSSSSSS\n");
       goThroughFatherInsert(quad,p);
    }

}


//retornar bool

int canInsertQuad(QuadTree *quad, PointQuad *p) {

    if(p -> position -> x >= quad -> bottonLeft -> x &&
    p -> position -> y >= quad -> bottonLeft -> y &&
    p -> position -> x <= quad -> topRight -> x &&
    p -> position -> y <= quad -> topRight -> y) return 1;

    else return 0;

}


List *pointsFather(QuadTree *quad) {

    List *list = initList();

    ListNode *nodeAux = quad -> type.nodeleaf -> points -> head;

       while( nodeAux != NULL) {
            //printf("ponto: x -> %d e y -> %d\n", ((PointQuad*)nodeAux -> data) -> position -> x, ((PointQuad*)nodeAux -> data) -> position -> y);
            headList(list,nodeAux -> data);
            nodeAux =  nodeAux -> next;
        }

    return list;
}

void subdive(QuadTree *quad){

    printf("SUBDIVIDI\n");
    List *pointsInserted = pointsFather(quad);

    Point *bottonLeft = quad -> bottonLeft;
    Point *topRight = quad -> topRight;

    deleteQuadNodeLeaf(quad);
    quad = initQuad(bottonLeft, topRight, NODEFATHER);

    Point *neL = newPoint((bottonLeft -> x + topRight -> x)/2, (bottonLeft -> y + topRight -> y)/2);
    Point *neR = topRight;
    QuadTree *firstQuad = initQuad(neL,neR,NODELEAF);

    Point *nwL = newPoint((bottonLeft -> x), (bottonLeft -> y + topRight -> y)/2);
    Point *nwR = newPoint((bottonLeft->x + topRight -> x)/2, (topRight -> y));
    QuadTree *secondQuad = initQuad(nwL,nwR, NODELEAF);

    Point *seL = bottonLeft;
    Point *seR = newPoint((bottonLeft -> x + topRight -> x)/2, (bottonLeft -> y + topRight -> y)/2);
    QuadTree *thirdQuad = initQuad(seL,seR,NODELEAF);

    Point *swL = newPoint((bottonLeft -> x + topRight -> x)/2, bottonLeft -> y);
    Point *swR = newPoint((topRight -> x), (bottonLeft -> y + topRight -> y)/2);
    QuadTree *fourthQuad = initQuad(swL,swR, NODELEAF);

    headList(quad -> type.nodefather -> child, firstQuad);
    headList(quad -> type.nodefather -> child, secondQuad);
    headList(quad -> type.nodefather -> child, thirdQuad);
    headList(quad -> type.nodefather -> child, fourthQuad);


    printf("%d\n",quad -> type.nodefather ->child -> size);

    ListNode *aux = pointsInserted -> head;

    while(aux != NULL) {

     // printf("ponto: x -> %d e y -> %d\n", ((PointQuad*)aux -> data) -> position -> x, ((PointQuad*)aux -> data) -> position -> y);

     // Point *new = newPoint(((PointQuad*)aux -> data) -> position -> x, ((PointQuad*)aux -> data) -> position -> y); 
     // if(new != firstQuad -> bottonLeft && new != firstQuad -> topRight)
           insertQuad(firstQuad, aux -> data); 
     // else if(new != secondQuad -> bottonLeft && new != secondQuad -> topRight)
            insertQuad(secondQuad, aux -> data);
      //else if(new != thirdQuad -> bottonLeft && new != thirdQuad -> topRight)
            insertQuad(thirdQuad, aux -> data);
      //else if(new != fourthQuad -> bottonLeft && new != fourthQuad -> topRight)
            insertQuad(fourthQuad, aux -> data);

     // else continue;
      
      aux = aux -> next;
    }

}


void goThroughFatherInsert(QuadTree *quad, PointQuad *p) {

      ListNode *nodeAux = quad -> type.nodefather -> child -> head;

        while( nodeAux != NULL) {
            insertQuad(nodeAux -> data, p);
            //printf("percorreu no pai\n");
            nodeAux =  nodeAux -> next;
        }
}


void deleteQuadNodeLeaf(QuadTree *quad) {

    free(quad -> type.nodeleaf->points);
    free(quad -> type.nodeleaf);
    free(quad);
}


/*
void printList(QuadTree *quad) {

    List *list = quad -> type.nodefather -> child; 
    if(list -> size = 0) printf("List is empty \n");

    else {
    ListNode *node = list -> head;

    while( node != NULL) {
        printf("lista: %d\n", node);
        node = node -> next;
    }
    printf("\n");
    }
  }

*/

int main(){


    Point *bottonLeft = newPoint(0,0);
    Point *topRight = newPoint(10,10);
    
    
    QuadTree *center = initQuad(bottonLeft,topRight, NODELEAF);

    Point *p1 = newPoint(1,1); 
    Point *p2 = newPoint(6,8);
    Point *p3 = newPoint(8,8); 
    Point *p4 = newPoint(9,7); 
    Point *p5 = newPoint(8,3);
    Point *p6 = newPoint(7,7);
    Point *p7 = newPoint(1,7);
    Point *p8 = newPoint(8,9);


    PointQuad *pq1 = initPointQuad(p1, "ola");
    PointQuad *pq2 = initPointQuad(p2, "ola"); 
    PointQuad *pq3 = initPointQuad(p3, "ola");
    PointQuad *pq4 = initPointQuad(p4, "ola");
    PointQuad *pq5 = initPointQuad(p5,"ola");
    PointQuad *pq6 = initPointQuad(p6,"ola");
    PointQuad *pq7 = initPointQuad(p7, "ola");
    PointQuad *pq8 = initPointQuad(p8, "ola");


    insertQuad(center, pq1);
    insertQuad(center, pq2); 
    insertQuad(center, pq3); 
    insertQuad(center, pq4);
    insertQuad(center, pq5);
    insertQuad(center, pq6);
    insertQuad(center, pq7);
    insertQuad(center, pq8);


    return 0;
}

