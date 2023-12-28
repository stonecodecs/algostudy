#include "mergesort.h"
#include <iostream>

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

// Input: unordered list a
// Output: ordered list a (smallest -> largest)
std::vector<int> mergesort(std::vector<int> a) {
    int N = a.size();
    if (N < 2) { return a; } // base case
    std::vector<int> left  = mergesort(createSubarray(a, 0, N/2));
    std::vector<int> right = mergesort(createSubarray(a, N/2, N));
    return merge(left, right);
}


// Input: two ordered lists
// Output: one ordered list
std::vector<int> merge(std::vector<int> a, std::vector<int> b) {
    long unsigned int size_a{a.size()};
    long unsigned int size_b{b.size()};
    std::vector<int> ordered(size_a + size_b);
    int j = 0; // a index
    int k = 0; // b index
    for(int i = 0; i < size_a + size_b; i++) {
        if (k >= size_b || (j < size_a && (a[j] < b[k]))) {
            ordered[i] = a[j++];
        } else {
            ordered[i] = b[k++];
        }
    }
    return ordered;
}