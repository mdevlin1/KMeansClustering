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
    
    std::vector<Point3D> points = parseFile(pointsFile);
    _points = points;

    populateCentroidVector();
}

void ClusterCoordinator::run()
{
    for (unsigned int i = 0; i < _numIterations; i++)
    {
        updateClusters();
        recalculateClusterCoordinates();
    }
}

// Finds the minimum x and y coordinates of a data point vector
// and return a Point object with those values
Point3D ClusterCoordinator::findMinDataPoint(std::vector<Point3D> points)
{
    std::vector<Point3D>::iterator iter = points.begin();
    double minX = iter->getXPos();
    double minY = iter->getYPos();
    double minZ = iter->getZPos();
    for (; iter != points.end(); ++iter) 
    {
        if (iter->getXPos() < minX) { minX = iter->getXPos(); }
        if (iter->getYPos() < minY) { minY = iter->getYPos(); }
        if (iter->getZPos() < minZ) { minZ = iter->getZPos(); }
    }

    return Point3D(minX, minY, minZ);
}

// Finds the maximum x and y coordinates of a data point vector
// and return a Point object with those values
Point3D ClusterCoordinator::findMaxDataPoint(std::vector<Point3D> points)
{
    std::vector<Point3D>::iterator iter = points.begin();
    double maxX = iter->getXPos();
    double maxY = iter->getYPos();
    double maxZ = iter->getZPos();
    for (; iter != points.end(); ++iter)
    {
        if (iter->getXPos() > maxX) { maxX = iter->getXPos(); }
        if (iter->getYPos() > maxY) { maxY = iter->getYPos(); }
        if (iter->getZPos() > maxZ) { maxZ = iter->getZPos(); }
    }
    
    return Point3D(maxX, maxY, maxZ);
}

// Finds the vector average of an inputted vector of points, this will
// be used to recalculate the centroid's center each iteration
std::tuple<double, double, double> ClusterCoordinator::calculatePointsVectorAverage(std::vector<Point3D> points)
{
    double totalX = 0, totalY = 0, totalZ = 0;
    for (std::vector<Point3D>::iterator point_iter = points.begin(); point_iter != points.end(); ++point_iter)
    {
        totalX += point_iter->getXPos();
        totalY += point_iter->getYPos();
        totalZ += point_iter->getZPos();
    }
    return std::make_tuple<double,double,double>( (totalX / points.size()), (totalY / points.size()), (totalZ / points.size()) );
}

void ClusterCoordinator::populateCentroidVector()
{
    Point3D minDataPoint = findMinDataPoint(_points);
    Point3D maxDataPoint = findMaxDataPoint(_points);

    srand(time(NULL));

    for (unsigned int centroidIdx = 0; centroidIdx < _numberOfCentroids; ++centroidIdx) 
    {
        double centroidXPos = rand() % (int)maxDataPoint.getXPos();
        double centroidYPos = rand() % (int)maxDataPoint.getYPos();
        double centroidZPos = rand() % (int)maxDataPoint.getZPos();

        _centroids.push_back(std::make_shared<Centroid>(Centroid(centroidXPos, centroidYPos, centroidZPos)));
    }
}

void ClusterCoordinator::recalculateClusterCoordinates()
{
    for (std::vector<CentroidPtr>::iterator cent_iter = _centroids.begin(); cent_iter != _centroids.end(); ++cent_iter)
    {
        CentroidPtr currentCent = *cent_iter;
        
        std::vector<Point3D> centroidPoints = currentCent->getCentroidPoints();

        // If there are no points in the cluster, then don't calculate the average
        if ( !centroidPoints.empty() )
        {
            auto [ newXPos, newYPos, newZPos ] = calculatePointsVectorAverage(centroidPoints);

            currentCent->setXPos(newXPos);
            currentCent->setYPos(newYPos);
            currentCent->setZPos(newZPos);
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
    for (std::vector<Point3D>::iterator iter = _points.begin(); iter != _points.end(); ++iter)
    {
        double min_distance = 0;
        CentroidPtr pointsCluster;
        for (std::vector<CentroidPtr>::iterator cent_iter = _centroids.begin(); cent_iter != _centroids.end(); ++cent_iter)
        {
            CentroidPtr currentCent = *cent_iter;
            double distance = currentCent->distance(iter->getXPos(), iter->getYPos(), iter->getZPos());
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