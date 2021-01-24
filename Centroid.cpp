#include "Centroid.h"
#include <iostream>

Centroid::Centroid(double x, double y) :
    Point(x, y)
{
}

Centroid::Centroid(const Point &p) :
    Point(p)
{
}

Centroid::~Centroid()
{}

void Centroid::addPoint(Point p)
{
    _clusterPoints.push_back(p);
}

std::vector<Point> Centroid::getCentroidPoints() 
{
    return _clusterPoints;
}

void Centroid::clear()
{
    _clusterPoints.clear();
}

void Centroid::printContainingPoints()
{
    std::cout << "Cluster (" << getXPos() << ", " << getYPos() << "): " << std::endl;
    for (std::vector<Point>::iterator iter = _clusterPoints.begin(); iter != _clusterPoints.end(); ++iter)
    {
        std::cout << "\tPoint coordinates: (" << iter->getXPos() << ", " << iter->getYPos() << ")" << std::endl;
    }
}