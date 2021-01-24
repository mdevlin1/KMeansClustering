#pragma once

class Point
{
    public:
        Point(double x, double y);
        Point(const Point &p) { _x = p.getXPos(); _y = p.getYPos(); }
        ~Point();
        double distance(const double pos_x, const double pos_y);
        virtual void setXPos(double pos_x) { _x = pos_x; }
        virtual double getXPos() const { return _x; }
        virtual void setYPos(double pos_y) { _y = pos_y; }
        virtual double getYPos() const { return _y; }

    protected:
        double _x;
        double _y;
};