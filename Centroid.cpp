#include "Centroid.h"
#include <iostream>

Centroid::Centroid(double x, double y, double z) :
    Point3D(x, y, z)
{
}

Centroid::Centroid(const Point3D &p) :
    Point3D(p)
{
}

Centroid::~Centroid()
{}

void Centroid::addPoint(Point3DPtr p)
{
    _clusterPoints.push_back(p);
}

std::vector<Point3DPtr> Centroid::getCentroidPoints() 
{
    return _clusterPoints;
}

void Centroid::clear()
{
    _clusterPoints.clear();
}

void Centroid::printContainingPoints()
{
    std::cout << "Cluster (" << getXPos() << ", " << getYPos() << ", " << getZPos() << "): " << std::endl;

    std::cout << "Number of points in cluster: " << _clusterPoints.size() << std::endl << std::endl;
}