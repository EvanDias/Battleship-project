#include <stdio.h> 
#include <stdlib.h>
#include "gamePiece.h"


posPiece *newShip(Point* p1, Point* p2) {

    posPiece* newResult = malloc(sizeof(posPiece));
    newResult -> p1 = p1;
    newResult -> p2 = p2;

    return newResult;

}


