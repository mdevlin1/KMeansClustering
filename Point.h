#pragma once

class Point
{
    public:
        Point(int x, int y);
        ~Point();
        double distance(const int pos_x, const int pos_y);
        int setXPos(int pos_x) { _x = pos_x; }
        int getXPos() const { return _x; }
        int setYPos(int pos_y) { _y = pos_y; }
        int getYPos() const { return _y; }

    protected:
        int _x;
        int _y;
};