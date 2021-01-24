#pragma once

class Point
{
    public:
        Point(int x, int y);
        Point(const Point &p) { _x = p.getXPos(); _y = p.getYPos(); }
        ~Point();
        double distance(const int pos_x, const int pos_y);
        void setXPos(int pos_x) { _x = pos_x; }
        int getXPos() const { return _x; }
        void setYPos(int pos_y) { _y = pos_y; }
        int getYPos() const { return _y; }

    protected:
        int _x;
        int _y;
};