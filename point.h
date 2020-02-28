#pragma once

typedef struct Point_ Point;

struct Point_
{
    int x; 
    int y;
};

Point* newPoint(int x, int y); 
void deletePoint(Point* p);