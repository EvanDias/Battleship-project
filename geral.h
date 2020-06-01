#include "cell.h"


 void *initDataStructure(int boardSize); 
 void *searchPoint(void *structure, Point *p);
 void insertShip(void *structure,  void *information, Point *p);
 void deleteShip(void *structure, void *data, Point *p);
 void freeDataStructure(void *structure);
