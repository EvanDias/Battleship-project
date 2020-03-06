#pragma once
#include <stdio.h>
#include "list.h"
#include "point.h"

typedef struct posPiece_ posPiece;

struct posPiece_ {

    List* pieces; 
    char* name;

}; 


posPiece* initShip(List* pieces, char* name);


