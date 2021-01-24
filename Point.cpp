#include "Point.h"
#include <math.h>

Point::Point(double x, double y) :
    _x(x), _y(y)
{
}

Point::~Point()
{
}

double Point::distance(const double pos_x, const double pos_y)
{
    return(sqrt(pow((_x - pos_x), 2) + pow((_y - pos_y), 2)));
}
