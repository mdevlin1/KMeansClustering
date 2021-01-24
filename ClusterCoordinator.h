#pragma once

#include "Centroid.h"
#include "Point3D.h"
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
        Point3D findMinDataPoint(std::vector<Point3D> points);
        
        // Finds the maximum x and y coordinates of a data point vector
        // and return a Point object with those values
        Point3D findMaxDataPoint(std::vector<Point3D> points);

        // Finds the vector average of an inputted vector of points, this will
        // be used to recalculate the centroid's center each iteration
        std::tuple<double, double, double> calculatePointsVectorAverage(std::vector<Point3D> points);

        void populateCentroidVector();
        void updateClusters();
        void recalculateClusterCoordinates();
        void printClusterInformation();

    private:
        std::vector<CentroidPtr> _centroids;
        std::vector<Point3D> _points;
        Poco::AutoPtr<Poco::Util::XMLConfiguration> _config;
        unsigned int _numIterations;
        unsigned int _numberOfCentroids;
};