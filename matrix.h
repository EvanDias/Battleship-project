#pragma once
#include <stdio.h>
#include "ship.h"
#include "point.h"

typedef struct matrix_ Matrix; 

struct matrix_
{
    int size;
    char** data;

};


Matrix *initMatrix(int size);
Matrix *insertShipInMatrix(Matrix *a, SHIP *ship);



