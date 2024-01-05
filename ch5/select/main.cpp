#include "select.cpp"
#include "gtest/gtest.h"
#include <algorithm>
#include <random>

TEST(RSelectTest, BasicTest) {
    std::vector<int> arr{3, 1, 4, 2, 5, 9, 7, 6, 8};
    int k;
    int result;
    std::random_device rd;

    std::mt19937 g(rd());
    for(int i = 0; i < 1000; i++) {
        k = rng(1,arr.size() - 1);
        result = rselect(arr, k);
        std::shuffle(arr.begin(), arr.end(), g);
        EXPECT_EQ(result, k);
    }

    
}

TEST(RSelectTest, EdgeCase) {
    // Test with an array of one element
    std::vector<int> arr{42};
    int k{1};

    int result = rselect(arr, k);

    // Check if the result is correct
    EXPECT_EQ(result, 42);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}