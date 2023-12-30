#include "closest_pair.h"
#include "point.h"

// maybe int is too small
int d2(
    Point p, 
    Point q)
{
    return (int)std::pow(p.x_coord() - q.x_coord(),2)
            + (int)std::pow(p.y_coord() - q.y_coord(),2);
}

std::vector<Point> sortPoints(std::vector<Point> set, bool byX) {
    std::vector<Point> sorted = set; // possibly unnecessary
    std::sort(sorted.begin(), sorted.end(), [byX](Point& a, Point& b) {
        if (byX) {  // sort by X
            return (a.x_coord() != b.x_coord()) 
            ? a.x_coord() < b.x_coord() 
            : a.y_coord() < b.y_coord();
        } else {    // sort by Y
            return (a.y_coord() != b.y_coord()) 
            ? a.y_coord() < b.y_coord() 
            : a.x_coord() < b.x_coord();
        }
    });

    return sorted;
}

// preprocess
// std::tuple<Point, Point> closestPair(std::vector<Point> set) {

// }

// std::tuple<Point, Point> closestPair(
//     std::vector<Point> s1, 
//     std::vector<Point> s2)
// {

// }

// std::tuple<Point, Point> closestPairSplit(
//     std::vector<Point> a, 
//     std::vector<Point> b, 
//     float distance)
// {

// }