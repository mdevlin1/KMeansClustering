#include "Point3D.h"
#include <math.h>

Point3D::Point3D(int x, int y, int z) : 
    Point(x, y), _z(z)
{
}

Point3D::~Point3D()
{
}

double Point3D::distance( int pos_x, int pos_y, int pos_z ) 
{
    return(sqrt(pow((getXPos() - pos_x), 2) + pow((getYPos() - pos_y), 2)) + pow((getZPos() - pos_z), 2));
}