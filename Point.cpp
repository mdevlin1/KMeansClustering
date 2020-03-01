#include "Point.h"
#include <math.h>

Point::Point(int x, int y) :
    _x(x), _y(y)
{
}

Point::~Point()
{
}

double Point::distance(const int pos_x, const int pos_y)
{
    return(sqrt(pow((_x - pos_x), 2) + pow((_y - pos_y), 2)));
}
