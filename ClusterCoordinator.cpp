#include "ClusterCoordinator.h"
#include <algorithm>

ClusterCoordinator::ClusterCoordinator()
{ }

ClusterCoordinator::~ClusterCoordinator()
{ }

void ClusterCoordinator::addCentroid(CentroidPtr c)
{
    _centroids.push_back(c);
}

void ClusterCoordinator::setPoints(std::vector<Point> points)
{
    _points = points;
}

void ClusterCoordinator::updateClusters()
{
    // Clears the old points from the cluster
    for (std::vector<CentroidPtr>::iterator cent_iter = _centroids.begin(); cent_iter != _centroids.end(); ++cent_iter)
    {
        CentroidPtr currentCent = *cent_iter;
        currentCent->clear();
    }

    // Calculates the distance from points to centroids and assigns the points to the closest
    // centroid
    for (std::vector<Point>::iterator iter = _points.begin(); iter != _points.end(); ++iter)
    {
        double min_distance = 0;
        CentroidPtr pointsCluster;
        for (std::vector<CentroidPtr>::iterator cent_iter = _centroids.begin(); cent_iter != _centroids.end(); ++cent_iter)
        {
            CentroidPtr currentCent = *cent_iter;
            double distance = currentCent->distance(iter->getXPos(), iter->getYPos());
            if (distance < min_distance || pointsCluster == NULL)
            {
                min_distance = distance;
                pointsCluster = *cent_iter;
            }
        }
        pointsCluster->addPoint(*iter);
    }
}