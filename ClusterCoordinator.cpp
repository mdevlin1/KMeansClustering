#include "ClusterCoordinator.h"

ClusterCoordinator::ClusterCoordinator()
{

}

ClusterCoordinator::~ClusterCoordinator()
{

}


void ClusterCoordinator::addCentroid(CentroidPtr c)
{
    _centroids.push_back(c);
}

void ClusterCoordinator::setPoints(std::vector<Point> points)
{
    _points = points;
}

void ClusterCoordinator::populateClusters()
{
    for (std::vector<Point>::iterator iter = _points.begin(); iter != _points.end(); ++iter)
    {
        
    }
}