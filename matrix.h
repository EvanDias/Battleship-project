#pragma once
#include <stdio.h> 


typedef struct matrix_ Matrix; 

struct matrix_
{
    int size;
    char** data;

};


Matrix* initMatrix(int size);
Matrix* insertionMatrix()



