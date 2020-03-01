#include "ClusterCoordinator.h"
#include <algorithm>
#include <Poco/Util/XMLConfiguration.h>

namespace {
    const std::string cNumIterations = "num_iterations";
    const std::string cPointsFile = "points_file";
    const std::string cCentroidsFile = "centroids_file";
}

ClusterCoordinator::ClusterCoordinator(Poco::AutoPtr<Poco::Util::XMLConfiguration> config)
    : _config(config), _numIterations(0)
{ }

ClusterCoordinator::~ClusterCoordinator()
{ }

void ClusterCoordinator::initialize()
{
    _numIterations = _config->getInt(cNumIterations);
    std::string pointsFile = _config->getString(cPointsFile);
    std::string centroidsFile = _config->getString(cCentroidsFile);
    
    std::vector<Point> points = parseFile(pointsFile);
    std::vector<Point> centroids = parseFile(centroidsFile);
    setPoints(points);
    for (std::vector<Point>::iterator iter = centroids.begin(); iter != centroids.end(); ++iter)
    {
        CentroidPtr c = std::make_shared<Centroid>(*iter);
        addCentroid(c);
    }
}

void ClusterCoordinator::run()
{
    for (int i = 0; i < _numIterations; i++)
    {
        updateClusters();
    }
}

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