#include "Point3D.h"
#include <math.h>

Point3D::Point3D(double x, double y, double z) : 
    Point(x, y), _z(z)
{
}

Point3D::~Point3D()
{
}

double Point3D::distance( double pos_x, double pos_y, double pos_z ) 
{
    return(sqrt(pow((getXPos() - pos_x), 2) + pow((getYPos() - pos_y), 2)) + pow((getZPos() - pos_z), 2));
}