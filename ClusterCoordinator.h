#pragma once

#include "Centroid.h"
#include "Point.h"
#include <vector>
#include <Poco/Util/XMLConfiguration.h>
#include "KMCCommon.h"

class ClusterCoordinator
{
    public:
        ClusterCoordinator(Poco::AutoPtr<Poco::Util::XMLConfiguration> config);
        ~ClusterCoordinator();
        void initialize();
        void run();
        
        // Finds the minimum x and y coordinates of a data point vector
        // and return a Point object with those values
        Point findMinDataPoint(std::vector<Point> points);
        
        // Finds the maximum x and y coordinates of a data point vector
        // and return a Point object with those values
        Point findMaxDataPoint(std::vector<Point> points);

        // Finds the vector average of an inputted vector of points, this will
        // be used to recalculate the centroid's center each iteration
        std::pair<double, double> calculatePointsVectorAverage(std::vector<Point> points);

        void populateCentroidVector();
        void updateClusters();
        void recalculateClusterCoordinates();
        void printClusterInformation();

    private:
        std::vector<CentroidPtr> _centroids;
        std::vector<Point> _points;
        Poco::AutoPtr<Poco::Util::XMLConfiguration> _config;
        unsigned int _numIterations;
        unsigned int _numberOfCentroids;
};