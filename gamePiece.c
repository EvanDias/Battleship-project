#include <stdio.h> 
#include <stdlib.h>
#include "gamePiece.h"


posPiece* newShip(List* pieces, char* name) {

    posPiece* newResult = malloc(sizeof(posPiece));
    newResult -> pieces = pieces;
    newResult -> name = name;

    return newResult;

}








