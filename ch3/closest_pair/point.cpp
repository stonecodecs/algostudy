#include "point.h"

Point::Point(int _x, int _y)
: x{_x}
, y{_y}
{ 
}

void Point::printCoordinates() {
    std::cout << "(" << x << ", " << y << ") ";
}

int Point::x_coord() {
    return x;
}

int Point::y_coord() {
    return y;
}