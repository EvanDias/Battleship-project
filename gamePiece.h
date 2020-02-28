#pragma once
#include <stdio.h>
#include "point.h"

typedef struct posPiece_ posPiece;

struct posPiece_
{

    Point *p1, *p2;
            
};


posPiece* newShip(Point* p1, Point* p2);



