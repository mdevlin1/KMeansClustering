#pragma once

#include "Point.h"

class Point3D : Point
{
    public:
        Point3D(double x, double y, double z);
        ~Point3D();
        void setXPos(double pos_x) { _x = pos_x; }
        double getXPos() const { return _x; }
        void setYPos(double pos_y) { _y = pos_y; }
        double getYPos() const { return _y; }
        void setZPos(double z) { _z = z; }
        double getZPos() { return _z; }
        double distance(double pos_x, double pos_y, double pos_z);
    private:
        double _z;
};