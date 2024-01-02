#include "quicksort.h"

std::vector<int> quicksort(std::vector<int> unsorted) {
    return _quicksort(unsorted, 0, unsorted.size());
}
std::vector<int> _quicksort(std::vector<int> unsorted, int start, int end){ 
    int N = unsorted.size();
    if (N <= 1) { // base case
        return unsorted;
    }
}

std::vector<int> swap(std::vector<int> set, int index1, int index2) {

}

std::vector<int> partition(std::vector<int> set, int start, int end) {

}