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
    std::vector<Point> set = createRandomSet(8, -20, 20);

    // temporary testing of sorting
    for (int i = 0; i < set.size(); ++i) {
        set[i].printCoordinates();
        std::cout << ", ";
    }

    std::vector<Point> sortedByX = sortPoints(set);
    std::cout << "\n SORTED BY X: \n";

    for (int i = 0; i < sortedByX.size(); ++i) {
        sortedByX[i].printCoordinates();
        std::cout << ", ";
    }

    std::vector<Point> sortedByY = sortPoints(set, false);
    std::cout << "\n SORTED BY Y: \n";

    for (int i = 0; i < sortedByY.size(); ++i) {
        sortedByY[i].printCoordinates();
        std::cout << ", ";
    }

    std::cout << "\n BACK TO ORIGINAL: \n";
    for (int i = 0; i < set.size(); ++i) {
        set[i].printCoordinates();
        std::cout << ", ";
    }

    return 0;
}