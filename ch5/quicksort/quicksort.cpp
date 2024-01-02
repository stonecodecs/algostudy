#include "quicksort.h"

std::vector<int> quicksort(std::vector<int> unsorted, PivotSelector ps) {
    return _quicksort(unsorted, 0, unsorted.size(), ps);
}

// warning: "end" is non-inclusive and is out-of-bounds if using unsorted[end]
std::vector<int> _quicksort(std::vector<int> &set, int start, int end, PivotSelector ps) { 
    int N {end - start};
    if (N <= 1) { return set; } // base case
    
    set = selectPivot(set, start, end, ps); // swaps pivot to 'start,'
    int pivotIndex {partition(set, start, end)}; // partition set around pivot
    // d&c
    std::vector<int> left  = _quicksort(set, start, pivotIndex, ps);
    std::vector<int> right = _quicksort(set, pivotIndex + 1, end, ps);
    return set;
}

void swap(std::vector<int> &set, int index1, int index2) {
    if (index1 < 0 || index2 > set.size()) { throw std::runtime_error("Index out of bounds error. Can't swap."); }
    if (index1 == index2) { return; } // do nothing
    int temp = set[index1];
    set[index1] = set[index2];
    set[index2] = temp;
}

// returns pivot index and swaps values destructively
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

    // lastly, swap the pivot to i - 1 (end of <pivot partition)
    swap(set, start, i - 1);
    return i - 1;
}

int rng(int min, int max) {
    return min + std::rand() % (max - min + 1);
}

std::vector<int> selectPivot(std::vector<int> &set, int start, int end, PivotSelector ps) {
    switch (ps) 
    {
    case PivotSelector::RANDOM:
        swap(set, 0, rng(start, end - 1));
        break;
    default:
        // leave as is
        break;
    }

    return set;
}