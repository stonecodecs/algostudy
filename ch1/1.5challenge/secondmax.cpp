#include "secondmax.h"
// could use pointers and indices for better memory efficiency

std::vector<int> createSubarray(std::vector<int> base, int start, int end) {
    std::vector<int> sub(base.begin() + start, base.begin() + end);
    return sub;
}

void printList(std::vector<int> a, int tag = 0) {
    if (tag) { std::cout << "tag: " << tag << "\n"; }
    for(int i = 0; i < a.size(); i++) {
        std::cout << a[i] << " ";
    }
    std::cout << "\n";
}

// divide and conquer algo to find 2nd largest element in list a
int secondMax(std::vector<int> a) {
    int N = a.size();
    if (N < 2) { throw std::invalid_argument("secondMax(): list has >2 elements;"
                                             "cannot find 2nd largest element"); }
    // findMax gets the max of each subroutine, and its largest "opponent" (vectors are len 2)
    std::vector<int> maxes = findMax(a);
    return maxes[1];
}

std::vector<int> findMax(std::vector<int> a) {
    int N = a.size();
    std::vector<int> maxes = std::vector<int>(2);
    if (N < 2) {
        maxes[0] = a[0];
        maxes[1] = INT_MIN; // "strongest opponent"
        return maxes; 
    }
    std::vector<int> leftMax = findMax(createSubarray(a, 0, N/2));
    std::vector<int> rightMax = findMax(createSubarray(a, N/2, N));
    if (leftMax[0] > rightMax[0]) {
        maxes[0] = leftMax[0];
        maxes[1] = (rightMax[0] > leftMax[1]) ? rightMax[0] : leftMax[1]; //update strongest opponent
    } else {
        maxes[0] = rightMax[0];
        maxes[1] = (leftMax[0] > rightMax[1]) ? leftMax[0] : rightMax[1];
    }
    return maxes;
}