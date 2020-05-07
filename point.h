#include <stdio.h>
#include <stdlib.h>


typedef struct Point_ Point;


//struct to create a point with x and y
struct Point_
{
    int x;
    int y;

};

Point* newPoint(int x, int y);
void deletePoint(Point* p);