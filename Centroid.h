#pragma once

#include "Point.h"
#include <vector>
#include <memory>

class Centroid : public Point
{
    public:
        Centroid(int x, int y);
        Centroid(const Point &p);
        ~Centroid();
        void addPoint(Point p);
        void clear();
        void printContainingPoints();

    private:
        std::vector<Point> _clusterPoints;
};