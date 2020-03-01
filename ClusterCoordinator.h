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
        void addCentroid(CentroidPtr c);
        void setPoints(std::vector<Point> points);
        void updateClusters();

    private:
        std::vector<CentroidPtr> _centroids;
        std::vector<Point> _points;
        Poco::AutoPtr<Poco::Util::XMLConfiguration> _config;
        int _numIterations;
};