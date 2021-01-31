#pragma once

#include "Point3D.h"
#include <vector>
#include <memory>

class Centroid : public Point3D
{
    public:
        Centroid(double x, double y, double z);
        Centroid(const Point3D &p);
        ~Centroid();
        void addPoint(Point3DPtr p);
        std::vector<Point3DPtr> getCentroidPoints();
        void clear();
        void printContainingPoints();

    private:
        std::vector<Point3DPtr> _clusterPoints;
};

typedef std::shared_ptr<Centroid> CentroidPtr;