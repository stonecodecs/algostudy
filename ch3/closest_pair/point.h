#pragma once
#include <iostream>

class Point {
    private:
        int x{};
        int y{};

    public:
        Point(int _x, int _y);
        void printCoordinates();
        int x_coord();
        int y_coord();
};