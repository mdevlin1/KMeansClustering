#include "ClusterCoordinator.h"
#include <algorithm>
#include <Poco/Util/XMLConfiguration.h>

namespace {
    const std::string cNumIterations = "num_iterations";
    const std::string cPointsFile = "points_file";
    const std::string cNumberOfCentroids = "number_of_centroids";
}

ClusterCoordinator::ClusterCoordinator(Poco::AutoPtr<Poco::Util::XMLConfiguration> config)
    : _config(config), _numIterations(0)
{ }

ClusterCoordinator::~ClusterCoordinator()
{ }

void ClusterCoordinator::initialize()
{
    _numIterations = _config->getInt(cNumIterations);
    _numberOfCentroids = _config->getInt(cNumberOfCentroids);
    std::string pointsFile = _config->getString(cPointsFile);
    
    std::vector<Point> points = parseFile(pointsFile);
    _points = points;

    populateCentroidVector();
}

void ClusterCoordinator::run()
{
    for (int i = 0; i < _numIterations; i++)
    {
        updateClusters();
    }
}

// Finds the minimum x and y coordinates of a data point vector
// and return a Point object with those values
Point ClusterCoordinator::findMinDataPoint()
{
    std::vector<Point>::iterator iter = _points.begin();
    unsigned int minX = iter->getXPos();
    unsigned int minY = iter->getYPos();
    for (; iter != _points.end(); ++iter) 
    {
        if (iter->getXPos() < minX) { minX = iter->getXPos(); }
        if (iter->getYPos() < minY) { minY = iter->getYPos(); }
    }

    return Point(minX, minY);
}

// Finds the maximum x and y coordinates of a data point vector
// and return a Point object with those values
Point ClusterCoordinator::findMaxDataPoint()
{
    std::vector<Point>::iterator iter = _points.begin();
    unsigned int maxX = iter->getXPos();
    unsigned int maxY = iter->getYPos();
    for (; iter != _points.end(); ++iter)
    {
        if (iter->getXPos() > maxX) { maxX = iter->getXPos(); }
        if (iter->getYPos() > maxY) { maxY = iter->getYPos(); }
    }
    
    return Point(maxX, maxY);
}


void ClusterCoordinator::populateCentroidVector()
{
    Point minDataPoint = findMinDataPoint();
    Point maxDataPoint = findMaxDataPoint();

    srand(time(NULL));

    for (unsigned int centroidIdx = 0; centroidIdx < _numberOfCentroids; ++centroidIdx) 
    {
        int centroidXPos = rand() % maxDataPoint.getXPos();
        int centroidYPos = rand() % maxDataPoint.getYPos();

        _centroids.push_back(std::make_shared<Centroid>(Centroid(centroidXPos, centroidYPos)));
    }
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

void ClusterCoordinator::printClusterInformation()
{
    for (std::vector<CentroidPtr>::iterator iter = _centroids.begin(); iter != _centroids.end(); ++iter)
    {
        CentroidPtr current = *iter;
        current->printContainingPoints();
    }
}