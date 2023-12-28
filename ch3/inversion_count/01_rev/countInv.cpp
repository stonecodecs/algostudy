#include "countInv.h"

long countInv(std::vector<long> a){ 
    if (a.size() < 2) { return 0; }
    std::vector<long> a_cpy = a; // to not effect the original list
    return countInv(&a_cpy, 0, a.size());
}

long countInv(std::vector<long>* a, long start, long end){
    long N {end - start};
    long mid { start + (end - start) / 2 };
    
    if (N < 2) { return 0; }
    long left  = countInv(a, start, mid); // inv. count for left
    long right = countInv(a, mid, end);   // inv. count for right
    long split = countSplitInvAndMerge(a, start, end, mid); // all inversions detected on split

    return left + right + split;
}

long countSplitInvAndMerge(std::vector<long>* a, long start, long end, long mid){
    long N {end - start};
    long invCount {0};
    std::vector<long> sorted(N);
    long i {start};
    long j {mid};

    for (long k = 0; k < N; k++) {
        if(j >= end || (i < mid && ((*a)[i] < (*a)[j]))) {
            sorted[k] = (*a)[i++];
        } else {
            sorted[k] = (*a)[j++];
            invCount += (mid - i);
        }
    }
    
    // then overwrite relevant part of original list 'a'
    for (long i = start; i < end; i++) {
        (*a)[i] = sorted[i - start]; 
    }

    return invCount;
}  

std::vector<long> file2vec(std::string file_path) {
    std::ifstream file(file_path);
    std::vector<long> fileContents {};
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            fileContents.push_back(std::stoi(line));
        }

        file.close();
    }

    return fileContents;
}