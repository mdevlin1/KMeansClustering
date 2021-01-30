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

void Centroid::addPoint(Point3D p)
{
    _clusterPoints.push_back(p);
}

std::vector<Point3D> Centroid::getCentroidPoints() 
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
    std::cout << "[ ";
    for (std::vector<Point3D>::iterator iter = _clusterPoints.begin(); iter != _clusterPoints.end(); ++iter)
    {
        std::cout << "(" << iter->getXPos() << ", " << iter->getYPos() << ", " << iter->getZPos() << ")" << ",";
    }
    std::cout << "]" << std::endl;
    std::cout << "Number of points in cluster: " << _clusterPoints.size() << std::endl;
}