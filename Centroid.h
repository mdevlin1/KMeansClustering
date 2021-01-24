#pragma once

#include "Point.h"
#include <vector>
#include <memory>

class Centroid : public Point
{
    public:
        Centroid(double x, double y);
        Centroid(const Point &p);
        ~Centroid();
        void addPoint(Point p);
        std::vector<Point> getCentroidPoints();
        void clear();
        void printContainingPoints();

    private:
        std::vector<Point> _clusterPoints;
};