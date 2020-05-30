#include <stdio.h>
#include <stdlib.h>

#define COORDX(P) (P->x)
#define COORDY(P) (P->y)
#define SETX(P, x) (P->x = x)
#define SETY(P, y) (P->y = y)

typedef struct Point_ Point;


//struct to create a point with x and y
struct Point_
{
    int x;
    int y;

};

Point *newPoint(int x, int y);
int getX(Point *p); 
int getY(Point *p); 
void setX(Point *p, int x); 
void setY(Point *p, int y);
void deletePoint(Point* p);