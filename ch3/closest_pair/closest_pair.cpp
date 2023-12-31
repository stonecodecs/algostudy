#include "closest_pair.h"
#include "point.h"
#include <limits.h>


// squared distance between 2 points
int d2(Point const &p, Point const &q)
{
    return static_cast<int>(std::pow(p.x_coord() - q.x_coord(),2)
            + std::pow(p.y_coord() - q.y_coord(),2));
}

// sorts points by X or Y coordinate (X by default; byX = true)
std::vector<Point> sortPoints(std::vector<Point> set, bool byX) {
    std::sort(set.begin(), set.end(), [byX](Point& a, Point& b) {
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
    return set;
}

// primarily used for splitPair 
// 'set' should be sorted on y-coord
// get vector of points nearest to one reference point some horizontal "dist" away
std::vector<Point> getPointsNearby(std::vector<Point> &set, int x_ref, int dist) {
    int N = set.size();
    std::vector<Point> points{};
    
    // iterate through y-sorted list and get any points within range "x_ref +/- dist"
    for(int i = 0; i < N; i++) {
        if (abs(set[i].x_coord() - x_ref) <= dist) {
            points.push_back(set[i]);
        }
    }
    return points;
}


std::tuple<std::vector<Point>,
           std::vector<Point>,
           std::vector<Point>,
           std::vector<Point>
          > divide(std::vector<Point> &a, std::vector<Point> &b) {
    std::vector<Point> leftx(a.begin(), a.begin() + a.size() /2);   // left half, sorted on x
    std::vector<Point> rightx(a.begin() + a.size() / 2, a.end());   // right half, sorted on x
    std::vector<Point> lefty{};
    std::vector<Point> righty{};
    Point* maxLeft = &leftx[leftx.size() - 1];

    for(int i = 0; i < b.size(); i++) {
        if (b[i].x_coord() < maxLeft->x_coord()) {
            lefty.push_back(b[i]);
        } else if (b[i].x_coord() > maxLeft->x_coord()) {
            righty.push_back(b[i]);
        } else {
            if (b[i].y_coord() <= maxLeft->y_coord()) {
                lefty.push_back(b[i]);
            } else { righty.push_back(b[i]); }
        }
    }

    std::tuple<std::vector<Point>,
               std::vector<Point>,
               std::vector<Point>,
               std::vector<Point>> inputVectors{leftx, rightx, lefty, righty};

    return inputVectors;
}

// preprocess
std::tuple<Point, Point> closestPair(std::vector<Point> &set) {
    if (set.size() < 3) {
        throw std::runtime_error("closestPair needs a input vector of at least 2 points.");
    }
    std::vector<Point> sortedByX = sortPoints(set, true);
    std::vector<Point> sortedByY = sortPoints(set, false);
    return closestPair(sortedByX, sortedByY);
}

std::tuple<Point, Point> closestPair(std::vector<Point> &a, std::vector<Point> &b) {
    if (a.size() <= 3) { // base case
        std::tuple<Point, Point> pair; // parent method guarentees at least one pair
        int smallest_dist{INT_MAX};
        for(int i = 0; i < a.size(); i++) {
            for(int j = i + 1; j < a.size(); j++) {
                int curr_d2 = d2(a[i], a[j]);
                if (curr_d2 < smallest_dist) {
                    pair = std::make_tuple(a[i], a[j]);
                    smallest_dist = curr_d2;
                }
            }
        }
        return pair;
    }

    // divide
    auto [leftx, rightx, lefty, righty] = divide(a, b);

    // conquer L and R
    std::tuple<Point, Point> leftPair  = closestPair(leftx, lefty);
    std::tuple<Point, Point> rightPair = closestPair(rightx, righty);
    int left_d2 = d2(std::get<0>(leftPair), std::get<1>(leftPair));
    int right_d2 = d2(std::get<0>(rightPair), std::get<1>(rightPair));

    // conquer split
    std::optional<std::tuple<Point, Point>> splitPair = closestPairSplit(a, b, std::min(left_d2, right_d2));
    int split_d2{INT_MAX};
    if (splitPair.has_value()) {
        split_d2 = d2(std::get<0>(*splitPair), std::get<1>(*splitPair));
    }
    
    // "combine" results
    if (left_d2 < right_d2) { 
        if (left_d2 < split_d2) { return leftPair; } else { return *splitPair; }}
    else { 
        if(right_d2 < split_d2) { return rightPair; } else { return *splitPair; }}
}

// may return nullptr
std::optional<std::tuple<Point, Point>> closestPairSplit(std::vector<Point> &a, 
                                                         std::vector<Point> &b, 
                                                         int dist) {

    int median_x {a[a.size() - 1].x_coord()};
    std::vector<Point> nearby {getPointsNearby(b, median_x, dist)};
    int closest_d2 {dist};
    std::optional<std::tuple<Point, Point>> closestPair {std::nullopt};

    for(int i = 0; i < nearby.size() - 1; i++) {
        for(int j = 1; j < std::min(7, (int)nearby.size() - i); j++) {
            int curr_dist = d2(nearby[i], nearby[i+j]);
            if (curr_dist < closest_d2 ) {
                closest_d2 = curr_dist;
                closestPair = std::make_tuple(nearby[i], nearby[i+j]);
            }
        }
    }

    return closestPair;
}