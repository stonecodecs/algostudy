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

std::vector<std::vector<int>> createRandomSets(int numSets, int min=0, int max=100) {
    std::vector<std::vector<int>> randomSets{};
    int n {rng(2, 30)};
    for(int i = 0; i < numSets; i++) {
        randomSets.push_back(createRandomSet(n, min, max));
    }
    return randomSets;
}

TEST(QuicksortTests, Partition) {
    std::vector<int> prepart {5,2,8,9,3,7};
    std::vector<int> prepart2 {10,8,5,2,8,9,3,7};
    ASSERT_EQ(2, partition(prepart, 0, prepart.size())); // assumes first index is pivot
    ASSERT_EQ(prepart2.size() - 1, partition(prepart2, 0, prepart2.size())); // assumes first index is pivot
}

TEST(QuicksortTests, RandomValuesQuicksort) {
    // Test scenario
    int numSets = 1000;
    std::vector<std::vector<int>> randSets {createRandomSets(numSets)};


    for(int i = 0; i < numSets; i++) {
        std::vector<int> truesorted = randSets[i];
        //printVector(truesorted);
        std::sort(truesorted.begin(), truesorted.end());
        //printVector(truesorted);
        //printVector(quicksort(randSets[i]));
        //printVector(randSets[i]);
        ASSERT_EQ(truesorted, quicksort(randSets[i], PivotSelector::RANDOM));
        //printVector(randSets[i]);
    }
}

TEST(QuicksortTests, LastValuesQuicksort) {
    // Test scenario
    int numSets = 1000;
    std::vector<std::vector<int>> randSets {createRandomSets(numSets)};


    for(int i = 0; i < numSets; i++) {
        std::vector<int> truesorted = randSets[i];
        //printVector(truesorted);
        std::sort(truesorted.begin(), truesorted.end());
        //printVector(truesorted);
        //printVector(quicksort(randSets[i]));
        //printVector(randSets[i]);
        ASSERT_EQ(truesorted, quicksort(randSets[i], PivotSelector::LAST));
        //printVector(randSets[i]);
    }
}

TEST(QuicksortTests, FirstValuesQuicksort) {
    // Test scenario
    int numSets = 1000;
    std::vector<std::vector<int>> randSets {createRandomSets(numSets)};


    for(int i = 0; i < numSets; i++) {
        std::vector<int> truesorted = randSets[i];
        //printVector(truesorted);
        std::sort(truesorted.begin(), truesorted.end());
        //printVector(truesorted);
        //printVector(quicksort(randSets[i]));
        //printVector(randSets[i]);
        ASSERT_EQ(truesorted, quicksort(randSets[i], PivotSelector::FIRST));
        //printVector(randSets[i]);
    }
}

TEST(QuicksortTests, MedianValuesQuicksort) {
    // Test scenario
    int numSets = 1000;
    std::vector<std::vector<int>> randSets {createRandomSets(numSets)};


    for(int i = 0; i < numSets; i++) {
        std::vector<int> truesorted = randSets[i];
        //printVector(truesorted);
        std::sort(truesorted.begin(), truesorted.end());
        //printVector(truesorted);
        //printVector(quicksort(randSets[i]));
        //printVector(randSets[i]);
        ASSERT_EQ(truesorted, quicksort(randSets[i], PivotSelector::MEDIANS));
        //printVector(randSets[i]);
    }
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}