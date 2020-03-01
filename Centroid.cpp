#include "Centroid.h"
#include <iostream>

Centroid::Centroid(int x, int y) :
    Point(x, y)
{
}

Centroid::~Centroid()
{}

void Centroid::addPoint(Point p)
{
    _clusterPoints.push_back(p);
}

void Centroid::clear()
{
    _clusterPoints.clear();
}

void Centroid::printContainingPoints()
{
    std::cout << "Cluster points: " << std::endl;
    for (std::vector<Point>::iterator iter = _clusterPoints.begin(); iter != _clusterPoints.end(); ++iter)
    {
        std::cout << "\tPoint coordinates: (" << iter->getXPos() << ", " << iter->getYPos() << ")" << std::endl;
    }
}