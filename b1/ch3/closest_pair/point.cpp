#include "point.h"

Point::Point() : x(0), y(0) {}

Point::Point(int _x, int _y)
: x{_x}
, y{_y}
{ 
}

void Point::printCoordinates() {
    std::cout << "(" << x << ", " << y << ") ";
}

int Point::x_coord() const {
    return x;
}

int Point::y_coord() const {
    return y;
}