#pragma once

class Point
{
    public:
        Point(double x, double y);
        Point(const Point &p) { _x = p.getXPos(); _y = p.getYPos(); }
        ~Point();
        double distance(const double pos_x, const double pos_y);
        void setXPos(double pos_x) { _x = pos_x; }
        double getXPos() const { return _x; }
        void setYPos(double pos_y) { _y = pos_y; }
        double getYPos() const { return _y; }

    protected:
        double _x;
        double _y;
};