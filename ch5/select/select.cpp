#include"select.h"

int rselect(std::vector<int> set, int x) {
    return _rselect(set, 0, set.size(), x);
}

// x must be at least 1
int _rselect(std::vector<int> &set, int start, int end, int x) {
    int N = end - start;
    if (N <= 1) { return set[start]; } // base case
    printVector(set);
    set = selectRandomPivot(set, start, end);
    printVector(set);
    int pivotIndex {partition(set, start, end)};
    std::cout << "pivot: " << pivotIndex << '\n';
    printVector(set);
    if (pivotIndex == (x - 1)) { return set[pivotIndex]; }
    else if (pivotIndex > (x - 1)) {
        return _rselect(set, start, pivotIndex, x); // left
    } else {
        return _rselect(set, pivotIndex + 1, end, x - pivotIndex - 1); // right
    }
}

int rng(int min, int max) {
    return min + std::rand() % (max - min + 1);
}

std::vector<int> selectRandomPivot(std::vector<int> &set, int start, int end) {
    swap(set, start, rng(start, end - 1));
    return set;
}

void swap(std::vector<int> &set, int start, int end) {
    if (start < 0 || end >= set.size()) { throw std::runtime_error("Index out of bounds error. Can't swap."); }
    if (start == end) { return; } // do nothing
    int temp {set[start]};
    set[start] = set[end];
    set[end] = temp;
}

int partition(std::vector<int> &set, int start, int end) {
    if (end - start <= 1) { return start; }

    // start is the pivot value index
    int i {start + 1};
    int j {start + 1};

    while(j < end) {
        if (set[j] <= set[start]) {
            swap(set, i++, j++); // then update i and j
        } else {
            j++;
        }
    }
    swap(set, start, i - 1);
    return i - 1;
}

void printVector(const std::vector<int>& vec) {
    std::cout << "Vector elements: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << "\n";
}
