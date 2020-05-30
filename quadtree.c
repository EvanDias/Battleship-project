#include "quadtree.h"
#include<stdio.h>
#include<string.h>

static PointQuad *new = NULL;


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


List *pointsLeaf(QuadTree *quad) {

    List *list = initList();

    ListNode *nodeAux = quad -> type.nodeleaf -> points -> head;

       while( nodeAux != NULL) {

            headList(list,nodeAux -> data);
            nodeAux =  nodeAux -> next;
        }

    return list;
}

QuadTree *subdive(QuadTree *quad) {

    printf("SUBDIVIDI\n");
    List *pointsInserted = pointsLeaf(quad);

    Point *bottonLeft = quad -> bottonLeft;
    Point *topRight = quad -> topRight;

    deleteQuadNodeLeaf(quad);

    QuadTree *new = initQuad(bottonLeft, topRight, NODEFATHER);

    Point *neL = newPoint((bottonLeft -> x + topRight -> x)/2, (bottonLeft -> y + topRight -> y)/2);
    Point *neR = topRight;
    QuadTree *firstQuad = initQuad(neL,neR,NODELEAF);
    firstQuad -> type.nodeleaf -> father = new;

    Point *nwL = newPoint((bottonLeft -> x), (bottonLeft -> y + topRight -> y)/2);
    Point *nwR = newPoint((bottonLeft->x + topRight -> x)/2, (topRight -> y));
    QuadTree *secondQuad = initQuad(nwL,nwR, NODELEAF);
    secondQuad -> type.nodeleaf -> father = new;

    Point *seL = bottonLeft;
    Point *seR = newPoint((bottonLeft -> x + topRight -> x)/2, (bottonLeft -> y + topRight -> y)/2);
    QuadTree *thirdQuad = initQuad(seL,seR,NODELEAF);
    thirdQuad -> type.nodeleaf -> father = new;

    Point *swL = newPoint((bottonLeft -> x + topRight -> x)/2, bottonLeft -> y);
    Point *swR = newPoint((topRight -> x), (bottonLeft -> y + topRight -> y)/2);
    QuadTree *fourthQuad = initQuad(swL,swR, NODELEAF);
    fourthQuad -> type.nodeleaf -> father = new;

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

void searchFather(QuadTree *quad, Point *p, int choice) {

    ListNode *aux = quad -> type.nodefather -> child -> head; 
    int count = 0;
    int count1 = 0;

    while(aux != NULL) {
      if(choice == 1) {
          PointQuad * searched = searchQuadTree(aux -> data,p);

          if(searched != NULL) break;
      }
      else if(choice == 2) {
        Point** points = getRefQuad(aux -> data, p);

        if(points != NULL) {
            break;
        }

      }

      aux = aux -> next;
    }

}

PointQuad *searchQuadTree(QuadTree *quad, Point *point) {
    
    int searched = canSearch(quad, point);


    if(searched == 0) {
      printf("Não contém\n"); 
      new = NULL;
      return new; 
  
    }

    else if(quad -> node == NODELEAF) {
      ListNode *aux = quad -> type.nodeleaf -> points -> head;


      while(aux != NULL) {
         //printf("x: %d   y: %d\n",((PointQuad*)aux -> data )-> position -> x,((PointQuad*)aux -> data )-> position -> y);
          if(((PointQuad*)aux -> data )-> position -> x == point -> x && ((PointQuad*)aux -> data )-> position -> y == point -> y) {
            printf("Encontrei\n");
            new = ((PointQuad*)aux -> data);
            return new;
            
          }
          else {
              printf("Não encontrei\n");
              new = NULL;
             
          }
        aux = aux -> next; 
      }

   }

     else if(quad -> node == NODEFATHER) {
     
         searchFather(quad,point,1);
      
   } 

  
   return new;

}


Point** getRefQuad(QuadTree *quad, Point *point) {

    int searched = canSearch(quad, point);

    static Point *p[2];

    if(searched == 0) {
      return NULL;
    }

    else if(quad -> node == NODELEAF) {
      ListNode *aux = quad -> type.nodeleaf -> points -> head;

      while(aux != NULL) {

          if(((PointQuad*)aux -> data) -> position -> x == point -> x &&
            ((PointQuad*)aux -> data) -> position -> y == point -> y) {
            p[0] = quad -> bottonLeft;
            p[1] = quad -> topRight;
            return p;
      }
            aux = aux -> next;
      }

   }

   else if(quad -> node == NODEFATHER) {

     searchFather(quad,point,2);

   }

   return p;
}


void whichQuadrant(QuadTree *quad, Point *p) {
    Point** points = getRefQuad(quad, p);
    int x_bottomLeft = points[0] -> x;
    int y_bottomLeft = points[0] -> y;
    int x_topRight = points[1] -> x;
    int y_topRight = points[1] -> y;
    int x = p -> x, y = p -> y;

    // 1º Quadrant
    if(x > (x_topRight/2) && y > (y_topRight / 2)) {
        printf("1º Quadrant\n");

    // 2º Quadrant
    } else if(x < (x_topRight/2) && y > (y_topRight / 2)) {
        printf("2º Quadrant\n");

    // 3º Quadrant
    } else if(x < (x_topRight/2) && y < (y_topRight / 2)) {
        printf("3º Quadrant\n");

    // 4º Quadrant
    } else {
        printf("4º Quadrant\n");
    }
}


void deleteQuadPoint(QuadTree *quad, Point *point) {

    if(quad -> node == NODELEAF) {
      //  PointQuad *pq = searchQuadTree(quad,point);

        ListNode *aux = quad -> type.nodeleaf -> points -> head;

         while(aux != NULL) {

          if(((PointQuad*)aux -> data) -> position -> x == point -> x &&
            ((PointQuad*)aux -> data) -> position -> y == point -> y) {
                removeNode(quad -> type.nodeleaf -> points, (PointQuad*)aux -> data);
                aux -> data = NULL;
            }

            aux = aux -> next;

         }
    }

    else if(quad -> node == NODEFATHER) {
        deleteFather(quad, point);
    }

}

void deleteFather(QuadTree *quad, Point *p) {

    int sum = 0;
    sum = sumListsSize(quad);

    if(sum == 5) {
        quad = deleteFatherAux(quad,p);
    }
    else if(sum > 5) {
        ListNode *aux = quad -> type.nodeleaf -> points -> head;

        while(aux != NULL) {
            deleteQuadPoint(aux -> data, p);

            aux = aux -> next;
        }

    }

}


QuadTree *deleteFatherAux(QuadTree *quad, Point *p) {

    List *list = listFather(quad); 

    printf("antes: %d\n", list -> size);

    Point *bottonLeft = quad ->bottonLeft; 
    Point *topRight = quad -> topRight;

    deleteQuadNodeFather(quad); 

    QuadTree *new = initQuad(bottonLeft,topRight, NODELEAF);

    PointQuad *pq = searchQuadTree(quad,p); 

   // printf("PONTO: x: %d e y : %d\n", pq -> position -> x, pq -> position -> y);
    removeNode(list, pq);

    printf("depois: %d\n", list -> size);

    printMe(list);


    ListNode *aux = list -> head; 

    while(aux != NULL) {
        insertQuad(new,aux -> data);
     
        aux = aux -> next;
    }


    return new;
}



void printMe(List *list) {

    if(list -> size = 0) printf("List is empty \n");
    else {
    ListNode *node = list -> head;
    while( node != NULL) {
        PointQuad *nodePoint = (PointQuad*)(node -> data);
        printf("%d \n", nodePoint -> position -> x);
        node = node -> next;
    }
    printf("\n");
    }
  }



List *listFather(QuadTree *quad) {

    ListNode *node = quad -> type.nodefather -> child -> head; 
    List *listAux = initList();
    List *list = initList();

    while(node != NULL) {

      listAux = pointsLeaf(node -> data);
      list = concatenateList(list,listAux);

      node = node -> next;
    }

    return list;

}



int sumListsSize(QuadTree *quad) {
    int sum = 0;

    ListNode *aux = quad -> type.nodeleaf -> points -> head;

    while(aux != NULL) {
        QuadTree *aux2 = (QuadTree*)(aux -> data);
        sum += aux2 -> type.nodeleaf -> points -> size;

        aux = aux -> next;
        //free(aux2);
    }

    //free(aux);
    return sum;
}

void deleteQuadNodeLeaf(QuadTree *quad) {

    freeList(quad -> type.nodeleaf->points);
    free(quad -> type.nodeleaf);
    free(quad);
}


void deleteQuadNodeFather(QuadTree *quad) {

    freeList(quad -> type.nodefather -> child); 
    free(quad -> type.nodefather); 
    free(quad);

}

void printList(QuadTree *quad) {

    List *list = quad -> type.nodeleaf ->points;

    if(list -> size = 0) printf("List is empty \n");
    else {
    ListNode *node = list -> head;
    while( node != NULL) {
       PointQuad *aux2 = (PointQuad*)(node -> data);
        printf("x: %d e y: %d\n", aux2 -> position -> x, aux2 -> position -> y);

        node = node -> next;
    }
    printf("\n");
    }
  }

int main(){

    Point *bottonLeft = newPoint(0,0);
    Point *topRight = newPoint(10,10);
    
    QuadTree *center = initQuad(bottonLeft,topRight, NODELEAF);

    Point *p1 = newPoint(1,1); 
    Point *p2 = newPoint(6,8);
    Point *p3 = newPoint(8,8); 
    Point *p4 = newPoint(9,2);
    Point *p5 = newPoint(8,3);
    Point *p6 = newPoint(7,7);
    Point *p7 = newPoint(1,7);
    Point *p8 = newPoint(8,9);
    Point *p9 = newPoint(3,4);
    Point *p10 = newPoint(0,9);
    Point *p11 = newPoint(4,5);
    Point *p12 = newPoint(3,5);
    Point *p13 = newPoint(3,9);
    Point *p14 = newPoint(5,5);

    PointQuad *pq1 = initPointQuad(p1, "ola");
    PointQuad *pq2 = initPointQuad(p2, "ola"); 
    PointQuad *pq3 = initPointQuad(p3, "ola");
    PointQuad *pq4 = initPointQuad(p4, "ola");
    PointQuad *pq5 = initPointQuad(p5,"ola");
    PointQuad *pq6 = initPointQuad(p6,"ola");
    PointQuad *pq7 = initPointQuad(p7, "ola");
    PointQuad *pq8 = initPointQuad(p8, "ola");
    PointQuad *pq9 = initPointQuad(p9, "ola");
    PointQuad *pq10 = initPointQuad(p10, "ola");
    PointQuad *pq11 = initPointQuad(p11,"ola");
    PointQuad *pq12 = initPointQuad(p12,"ola");
    PointQuad *pq13 = initPointQuad(p13, "ola");
    PointQuad *pq14 = initPointQuad(p14, "ola");

    insertQuad(center, pq1);
    insertQuad(center, pq2); 
    insertQuad(center, pq3);
    insertQuad(center, pq4);
    insertQuad(center, pq5);
   /* insertQuad(center, pq6);
    insertQuad(center, pq7);
    insertQuad(center, pq8);
    insertQuad(center, pq9);
    insertQuad(center, pq10);
    insertQuad(center, pq11);
    insertQuad(center, pq12);
    insertQuad(center, pq13);
    insertQuad(center, pq14);
    

    //printf("x: %d  || y: %d \n", ponto[0] -> x, ponto[0] -> y);
    //printf("x: %d  || y: %d \n", ponto[1] -> x, ponto[1] -> y);



   /* whichQuadrant(center,p1);
    whichQuadrant(center,p2);
    whichQuadrant(center,p7);
    whichQuadrant(center,p4);
    whichQuadrant(center,p2);
*/

   // printList(center);
    PointQuad *ponto = searchQuadTree(center, p2);

    deleteQuadPoint(center, p2);

    PointQuad *ponto1 = searchQuadTree(center, p2);

    printf("type %d\n", center -> node);


   // deleteQuadPoint(center, p10);

   // PointQuad *ponto2 = searchQuadTree(center, p10);

    if(ponto == NULL) printf("OH YEAH\n");

    //printList(center);

    
    return 0;
}

