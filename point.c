#include "point.h"



//create a new point
Point* newPoint(int x_, int y_) {

    Point* newResult = malloc(sizeof(Point));
    newResult -> x = x_;
    newResult -> y = y_;

    return newResult;
}


//delete a point
void deletePoint(Point* p) {

    free(p);    //delete the memory

}
