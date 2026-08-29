#include "headerz.h"
#include <math.h>

double point_dist(Point p1, Point p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double dot_product(Point p1, Point p2) { return p1.x * p2.x + p1.y * p2.y; }