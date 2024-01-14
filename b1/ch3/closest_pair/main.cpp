#include "closest_pair.h"
#include "point.h"  
#include <cstdlib>

std::vector<Point> createRandomSet(int n, int min=0, int max=100) {
    std::vector<Point> randomSet{};
    for(int i = 0; i < n; i++) {
        int x {rand() % (max - min + 1) + min};
        int y {rand() % (max - min + 1) + min};
        Point p(x, y);
        randomSet.push_back(p);
    }
    return randomSet;
}

int main(int argc, char** argv) {
    std::vector<Point> set = createRandomSet(16, -100, 100);

    // temporary testing of sorting
    for (int i = 0; i < set.size(); ++i) {
        set[i].printCoordinates();
        std::cout << ", ";
    }

    std::cout << "closest pair: "; 
    std::tuple<Point, Point> pair = closestPair(set);
    (std::get<0>(pair)).printCoordinates();
    (std::get<1>(pair)).printCoordinates();
    return 0;
}