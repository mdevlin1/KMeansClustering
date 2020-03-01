#include <iostream>
#include "Point.h"
#include "Centroid.h"
#include "ClusterCoordinator.h"
#include <memory>
#include <vector>

int main()
{
    std::vector<Point> dataPoints {
        Point(1,2), Point(2,3), Point(456, 23), Point(45, 2), Point(34, 64),
        Point(43, 123), Point(94, 23), Point(120, 32), Point(21, 37)
    };

    CentroidPtr c1 = std::make_shared<Centroid>(34, 10);
    CentroidPtr c2 = std::make_shared<Centroid>(123, 50);

    ClusterCoordinator clusterCoord;
    clusterCoord.addCentroid(c1);
    clusterCoord.addCentroid(c2);

    clusterCoord.setPoints(dataPoints);
    clusterCoord.updateClusters();

    c1->printContainingPoints();
    c2->printContainingPoints();

    return 0;
}