#include"select.h"
#include<exception>

int dselect(std::vector<int> set, int x) {
    if (x < 1 || x > set.size() + 1) { 
        throw std::runtime_error("x must be a positive integer within range of input vector");
    }
    return _dselect(set, 0, set.size(), x - 1);
}

// median of medians
int _dselect(std::vector<int> &set, int start, int end, int x) {
    int N = end - start;
    if (N <= 1) { return set[start]; } // base case
    std::vector<int> mediansOfK{};
    int K = 5;

    // establish medians of medians vector
    for (int i = 0; i < std::ceil(N / K); i++) {
        std::vector<int> buffer{};
        int mid{};
        buffer.assign(set.begin() + i*K, set.begin() + i*K + std::min(K, N - i*K));
        std::sort(buffer.begin(), buffer.end());
        mid = buffer[buffer.size() / 2]; // if even, default to right val
        mediansOfK.push_back(mid);
    }

    int pivotValue = _dselect(mediansOfK, 0, mediansOfK.size(), N / (K*2));
    set = selectPivotFromValue(set, start, end, pivotValue); 
    int pivotIndex {partition(set, start, end)};

    if (pivotIndex == x) { return set[pivotIndex]; }
    else if (pivotIndex > x) {
        return _rselect(set, start, pivotIndex, x); // left
    } else {
        return _rselect(set, pivotIndex + 1, end, x); // right
    }
}

int rselect(std::vector<int> set, int x) {
    if (x < 1 || x > set.size() + 1) { 
        throw std::runtime_error("x must be a positive integer within range of input vector");
    }
    return _rselect(set, 0, set.size(), x - 1);
}

// x must be at least 1
// USING start and end indexes, we don't change x on recursive call (or, add start to pivot index)
int _rselect(std::vector<int> &set, int start, int end, int x) {
    int N = end - start;
    if (N <= 1) { return set[start]; } // base case
    set = selectRandomPivot(set, start, end);
    int pivotIndex {partition(set, start, end)};
    
    if (pivotIndex == x) { return set[pivotIndex]; }
    else if (pivotIndex > x) {
        return _rselect(set, start, pivotIndex, x); // left
    } else {
        return _rselect(set, pivotIndex + 1, end, x); // right
    }
}

int rng(int min, int max) {
    return min + std::rand() % (max - min + 1);
}

// could be more efficent, but gets the idea done
std::vector<int> selectPivotFromValue(std::vector<int> &set, int start, int end, int pivot) {
    int pivotIndex{};
    for(int i = start; i < end; i++) {
        if (pivot == set[i]) {
            pivotIndex = i;
        }
    }
    swap(set, start, pivotIndex);
    return set;
}

std::vector<int> selectRandomPivot(std::vector<int> &set, int start, int end) {
    swap(set, start, rng(start, end - 1));
    return set;
}

void swap(std::vector<int> &set, int index1, int index2) {
    if (index1 < 0 || index2 >= set.size()) { throw std::runtime_error("Index out of bounds error. Can't swap."); }
    if (index1 == index2) { return; } // do nothing
    int temp {set[index1]};
    set[index1] = set[index2];
    set[index2] = temp;
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
