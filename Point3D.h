#pragma once

#include "Point.h"

class Point3D : Point
{
    public:
        Point3D(int x, int y, int z);
        ~Point3D();
        void setZPos(int z) { _z = z; }
        int getZPos() { return _z; }
        double distance(int pos_x, int pos_y, int pos_z);
    private:
        int _z;
};