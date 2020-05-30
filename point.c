#include "point.h"



//create a new point
Point* newPoint(int x_, int y_) {

    Point* newResult = malloc(sizeof(Point));
    newResult -> x = x_;
    newResult -> y = y_;

    return newResult;
}

int getX(Point *p) {

    return p -> x;
}

int getY(Point *p) {

    return p -> y;
}

void setX(Point *p, int x) {

    p -> x = x; 

}

void setY(Point *p, int y) {

    p -> y = y;

}



//delete a point
void deletePoint(Point* p) {

    free(p);    //delete the memory

}
