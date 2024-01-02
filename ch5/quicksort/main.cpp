#include "quicksort.cpp"
#include "gtest/gtest.h"
#include <algorithm>

std::vector<int> createRandomSet(int n, int min=0, int max=100) {
    std::vector<int> randomSet{};
    for(int i = 0; i < n; i++) {
        int x {rng(min, max)};
        randomSet.push_back(x);
    }
    return randomSet;
}

void printVector(const std::vector<int>& vec) {
    std::cout << "Vector elements: ";
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << "\n";
}

std::vector<std::vector<int>> createRandomSets(int numSets, int min=0, int max=100) {
    std::vector<std::vector<int>> randomSets{};
    int n {rng(2, 50)};
    for(int i = 0; i < numSets; i++) {
        randomSets.push_back(createRandomSet(n, min, max));
    }
    return randomSets;
}

TEST(QuicksortTests, RandomValues) {
    // Test scenario
    int numSets = 2;
    std::vector<std::vector<int>> randSets {createRandomSets(numSets)};

    for(int i = 0; i < numSets; i++) {
        std::vector<int> truesorted = randSets[i];
        printVector(truesorted);
        std::sort(truesorted.begin(), truesorted.end());
        printVector(truesorted);
        printVector(quicksort(randSets[i]));
        printVector(randSets[i]);
        ASSERT_EQ(truesorted, quicksort(randSets[i]));
        printVector(randSets[i]);
    }
    
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}