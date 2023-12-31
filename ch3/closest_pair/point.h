#pragma once
#include <iostream>

class Point {
    private:
        int x;
        int y;

    public:
        Point();
        Point(int _x, int _y);
        void printCoordinates();
        int x_coord() const;
        int y_coord() const;
};