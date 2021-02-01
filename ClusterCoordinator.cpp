#include "ClusterCoordinator.h"
#include <algorithm>
#include <Poco/Util/XMLConfiguration.h>

namespace {
    const std::string cNumIterations = "num_iterations";
    const std::string cPointsFile = "points_file";
    const std::string cNumberOfCentroids = "number_of_centroids";
    const std::string cImageFile = "image_file";
    const std::string cOutputImageFile = "output_image_file";
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
    std::string imageFile = _config->getString(cImageFile);
    _outputImageFile = _config->getString(cOutputImageFile);

    // This can be used to debug the k means algorithm, it 
    // reads in points from a text file and can be used to 
    // populate the vector of points
    //std::vector<Point3D> points = parseFile(pointsFile);

    // Uses opencv to convert the image specified in the config file 
    // to an opencv Mat 
    _imageMat = cv::imread(imageFile);

    _points = ImageProcessor::convertImageToPoints( _imageMat );

    populateCentroidVector();
}

void ClusterCoordinator::run()
{
    // This boolean value will tell us if there is a valid update to at least one of the 
    // cluster's points, if yes, we keep iterating, if no, we finish the program
    bool isUpdated = true;
    
    while( isUpdated )
    {
        updateClusters();
        isUpdated = recalculateClusterCoordinates();

        printClusterInformation();
    }

    cv::Mat compressedImg = ImageProcessor::convertPointsToImage(_centroids, _points, _imageMat);

    std::vector<int> compression_params;
    compression_params.push_back(cv::IMWRITE_JPEG_OPTIMIZE);
    compression_params.push_back(1);
    cv::imwrite(_outputImageFile, compressedImg);
}

// Finds the minimum x and y coordinates of a data point vector
// and return a Point object with those values
Point3D ClusterCoordinator::findMinDataPoint(std::vector<Point3DPtr> points)
{
    std::vector<Point3DPtr>::iterator iter = points.begin();
    double minX = (*iter)->getXPos();
    double minY = (*iter)->getYPos();
    double minZ = (*iter)->getZPos();
    for (; iter != points.end(); ++iter) 
    {
        if ((*iter)->getXPos() < minX) { minX = (*iter)->getXPos(); }
        if ((*iter)->getYPos() < minY) { minY = (*iter)->getYPos(); }
        if ((*iter)->getZPos() < minZ) { minZ = (*iter)->getZPos(); }
    }

    return Point3D(minX, minY, minZ);
}

// Finds the maximum x and y coordinates of a data point vector
// and return a Point object with those values
Point3D ClusterCoordinator::findMaxDataPoint(std::vector<Point3DPtr> points)
{
    std::vector<Point3DPtr>::iterator iter = points.begin();
    double maxX = (*iter)->getXPos();
    double maxY = (*iter)->getYPos();
    double maxZ = (*iter)->getZPos();
    for (; iter != points.end(); ++iter)
    {
        if ((*iter)->getXPos() > maxX) { maxX = (*iter)->getXPos(); }
        if ((*iter)->getYPos() > maxY) { maxY = (*iter)->getYPos(); }
        if ((*iter)->getZPos() > maxZ) { maxZ = (*iter)->getZPos(); }
    }
    
    return Point3D(maxX, maxY, maxZ);
}

// Finds the vector average of an inputted vector of points, this will
// be used to recalculate the centroid's center each iteration
std::tuple<double, double, double> ClusterCoordinator::calculatePointsVectorAverage(std::vector<Point3DPtr> points)
{
    double totalX = 0, totalY = 0, totalZ = 0;
    for (std::vector<Point3DPtr>::iterator point_iter = points.begin(); point_iter != points.end(); ++point_iter)
    {
        totalX += (*point_iter)->getXPos();
        totalY += (*point_iter)->getYPos();
        totalZ += (*point_iter)->getZPos();
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

bool ClusterCoordinator::recalculateClusterCoordinates()
{
    // This boolean value will tell us if there is a valid update to at least one of the 
    // cluster's points, if yes, we keep iterating, if no, we finish the program
    bool isUpdated = false;

    for (std::vector<CentroidPtr>::iterator cent_iter = _centroids.begin(); cent_iter != _centroids.end(); ++cent_iter)
    {
        std::vector<Point3DPtr> centroidPoints = (*cent_iter)->getCentroidPoints();

        // If there are no points in the cluster, then don't calculate the average
        if ( !centroidPoints.empty() )
        {
            auto [ newXPos, newYPos, newZPos ] = calculatePointsVectorAverage(centroidPoints);

            if ( (*cent_iter)->getXPos() != newXPos && (*cent_iter)->getYPos() != newYPos && (*cent_iter)->getZPos() != newZPos )
            {
                isUpdated = true;
            }

            (*cent_iter)->setXPos(newXPos);
            (*cent_iter)->setYPos(newYPos);
            (*cent_iter)->setZPos(newZPos);
        }
    }

    return isUpdated;
}

void ClusterCoordinator::updateClusters()
{
    // Clears the old points from the cluster
    for (std::vector<CentroidPtr>::iterator cent_iter = _centroids.begin(); cent_iter != _centroids.end(); ++cent_iter)
    {
        (*cent_iter)->clear();
    }

    // Calculates the distance from points to centroids and assigns the points to the closest
    // centroid
    for (std::vector<Point3DPtr>::iterator iter = _points.begin(); iter != _points.end(); ++iter)
    {
        double min_distance = 0;
        CentroidPtr pointsCluster = NULL;
        for (std::vector<CentroidPtr>::iterator cent_iter = _centroids.begin(); cent_iter != _centroids.end(); ++cent_iter)
        {
            double distance = (*cent_iter)->distance((*iter)->getXPos(), (*iter)->getYPos(), (*iter)->getZPos());
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
        (*iter)->printContainingPoints();
    }
}