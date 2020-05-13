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
            quad = subdive(quad);
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

            headList(list,nodeAux -> data);
            nodeAux =  nodeAux -> next;
        }

    return list;
}

QuadTree *subdive(QuadTree *quad){

    printf("SUBDIVIDI\n");
    List *pointsInserted = pointsFather(quad);

    Point *bottonLeft = quad -> bottonLeft;
    Point *topRight = quad -> topRight;

    deleteQuadNodeLeaf(quad);
    QuadTree *new = initQuad(bottonLeft, topRight, NODEFATHER);

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

    headList(new -> type.nodefather -> child, firstQuad);
    headList(new -> type.nodefather -> child, secondQuad);
    headList(new -> type.nodefather -> child, thirdQuad);
    headList(new -> type.nodefather -> child, fourthQuad);


    ListNode *aux = pointsInserted -> head;

    while(aux != NULL) {
           insertQuad(firstQuad, aux -> data); 
           insertQuad(secondQuad, aux -> data);
           insertQuad(thirdQuad, aux -> data);
           insertQuad(fourthQuad, aux -> data);
      
      aux = aux -> next;
    }

    return new;

}


void goThroughFatherInsert(QuadTree *quad, PointQuad *p) {

      ListNode *nodeAux = quad -> type.nodefather -> child -> head;

        while( nodeAux != NULL) {
            insertQuad(nodeAux -> data, p);
            //printf("percorreu no pai\n");
            nodeAux =  nodeAux -> next;
        }
}


int canSearch(QuadTree *quad, Point *point) {

  if(point -> x >= quad -> bottonLeft -> x &&
   point -> y >= quad -> bottonLeft -> y &&
   point -> x <= quad -> topRight -> x &&
   point -> y <= quad -> topRight -> y) return 1;

    else return 0;
  
}

void searchFather(QuadTree *quad, Point *p) {

    ListNode *aux = quad -> type.nodefather -> child -> head; 

    while(aux != NULL) {

      PointQuad * searched = searchQuadTree(aux -> data,p); 

      if(searched == NULL) aux = aux -> next;
      else break;
    }

}

PointQuad *searchQuadTree(QuadTree *quad, Point *point) {
    
    int searched = canSearch(quad, point);

    PointQuad *new = NULL;

    int broke = 0;

    if(searched == 0) {
      printf("Não contém\n"); 
      return new; 
  
    }

    else if(quad -> node == NODELEAF) {
      ListNode *aux = quad -> type.nodeleaf -> points -> head;

      while(aux != NULL) {

          if(((PointQuad*)aux -> data )-> position -> x == point -> x && ((PointQuad*)aux -> data )-> position -> y == point -> y) {
            printf("Encontrei\n");
            new = ((PointQuad*)aux -> data);
            printf("%d %d\n", new ->position ->x, new ->position ->y);
            return new;

      }

          else {
            printf("Não encontrei \n");
          }

        aux = aux -> next; 
      }

   }

   else if(quad -> node == NODEFATHER) {
     
     printf("entrei\n");
     searchFather(quad,point);
      
   } 

    //return new;

}

void deleteQuadNodeLeaf(QuadTree *quad) {

    free(quad -> type.nodeleaf->points);
    free(quad -> type.nodeleaf);
    free(quad);
}

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
    Point *p9 = newPoint(3,4);

    Point *p10 = newPoint(5,5);

    PointQuad *pq1 = initPointQuad(p1, "ola");
    PointQuad *pq2 = initPointQuad(p2, "ola"); 
    PointQuad *pq3 = initPointQuad(p3, "ola");
    PointQuad *pq4 = initPointQuad(p4, "ola");
    PointQuad *pq5 = initPointQuad(p5,"ola");
    PointQuad *pq6 = initPointQuad(p6,"ola");
    PointQuad *pq7 = initPointQuad(p7, "ola");
    PointQuad *pq8 = initPointQuad(p8, "ola");

    PointQuad *pq10 = initPointQuad(p10, "ola");

    insertQuad(center, pq1);
    insertQuad(center, pq2); 
    insertQuad(center, pq3); 
    insertQuad(center, pq4);
    insertQuad(center, pq8);
    insertQuad(center, pq6);
    //insertQuad(center, pq7);
   // insertQuad(center, pq8);

    printf("%d\n", center ->node);

    PointQuad *ponto = searchQuadTree(center, p3);

    if(ponto == NULL) printf("ola\n");
    
    else printf("YESSSSSSSSSSSSSSSSSSSSSSs\n");

    return 0;
}

