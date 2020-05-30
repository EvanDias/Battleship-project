#include "cell.h"


 void *initDataStructure(int boardSize); 
 void *searchPoint(void *structure, Point *p);
 void insertShip(void *structure,  void *information, Point *p);
 void deleteShip(void *structure, Point *p, int numberPoints);
 void freeDataStructure(void *structure);
