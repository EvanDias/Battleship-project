#include <stdio.h> 
#include <stdlib.h>
#include "point.h"

Point* newPoint(int x_, int y_) {

    Point* newResult = malloc(sizeof(Point));
     newResult -> x = x_;
     newResult -> y = y_;

     return newResult;
}

void deletePoint(Point* p) {

    free(p);    //delete the memory

}

