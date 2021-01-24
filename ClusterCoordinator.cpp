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
    for (unsigned int i = 0; i < _numIterations; i++)
    {
        updateClusters();
        recalculateClusterCoordinates();
        printClusterInformation();
    }
}

// Finds the minimum x and y coordinates of a data point vector
// and return a Point object with those values
Point ClusterCoordinator::findMinDataPoint(std::vector<Point> points)
{
    std::vector<Point>::iterator iter = points.begin();
    double minX = iter->getXPos();
    double minY = iter->getYPos();
    for (; iter != points.end(); ++iter) 
    {
        if (iter->getXPos() < minX) { minX = iter->getXPos(); }
        if (iter->getYPos() < minY) { minY = iter->getYPos(); }
    }

    return Point(minX, minY);
}

// Finds the maximum x and y coordinates of a data point vector
// and return a Point object with those values
Point ClusterCoordinator::findMaxDataPoint(std::vector<Point> points)
{
    std::vector<Point>::iterator iter = points.begin();
    double maxX = iter->getXPos();
    double maxY = iter->getYPos();
    for (; iter != points.end(); ++iter)
    {
        if (iter->getXPos() > maxX) { maxX = iter->getXPos(); }
        if (iter->getYPos() > maxY) { maxY = iter->getYPos(); }
    }
    
    return Point(maxX, maxY);
}

// Finds the vector average of an inputted vector of points, this will
// be used to recalculate the centroid's center each iteration
std::pair<double, double> ClusterCoordinator::calculatePointsVectorAverage(std::vector<Point> points)
{
    double totalX = 0, totalY = 0;
    for (std::vector<Point>::iterator point_iter = points.begin(); point_iter != points.end(); ++point_iter)
    {
        totalX += point_iter->getXPos();
        totalY += point_iter->getYPos();
    }
    return std::make_pair<int,int>( (totalX / points.size()), (totalY / points.size()) );
}

void ClusterCoordinator::populateCentroidVector()
{
    Point minDataPoint = findMinDataPoint(_points);
    Point maxDataPoint = findMaxDataPoint(_points);

    srand(time(NULL));

    for (unsigned int centroidIdx = 0; centroidIdx < _numberOfCentroids; ++centroidIdx) 
    {
        double centroidXPos = rand() % (int)maxDataPoint.getXPos();
        double centroidYPos = rand() % (int)maxDataPoint.getYPos();

        _centroids.push_back(std::make_shared<Centroid>(Centroid(centroidXPos, centroidYPos)));
    }
}

void ClusterCoordinator::recalculateClusterCoordinates()
{
    for (std::vector<CentroidPtr>::iterator cent_iter = _centroids.begin(); cent_iter != _centroids.end(); ++cent_iter)
    {
        CentroidPtr currentCent = *cent_iter;
        
        std::vector<Point> centroidPoints = currentCent->getCentroidPoints();

        // If there are no points in the cluster, then don't calculate the average
        if ( !centroidPoints.empty() )
        {
            std::pair<double, double> newCentroidCenter = calculatePointsVectorAverage(centroidPoints);

            currentCent->setXPos(newCentroidCenter.first);
            currentCent->setYPos(newCentroidCenter.second);
        }
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