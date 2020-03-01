#pragma once

#include "Centroid.h"
#include "Point.h"
#include <vector>

typedef std::shared_ptr<Centroid> CentroidPtr;

class ClusterCoordinator
{
    public:
        ClusterCoordinator();
        ~ClusterCoordinator();
        void addCentroid(CentroidPtr c);
        void setPoints(std::vector<Point> points);
        void updateClusters();

    private:
        std::vector<CentroidPtr> _centroids;
        std::vector<Point> _points;
};