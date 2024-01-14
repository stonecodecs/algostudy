#include "mergesort.cpp"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

TEST(MergeSortTests, BaseCase) {
    EXPECT_EQ((std::vector<int>{}), mergesort(std::vector<int>{}));
    EXPECT_EQ((std::vector<int>{72}), mergesort(std::vector<int>{72}));
    EXPECT_EQ((std::vector<int>{10, 72}), mergesort(std::vector<int>{72, 10}));
}

TEST(MergeSortTests, EvenLengthList) {
    EXPECT_EQ((std::vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}), mergesort(std::vector<int>{15, 8, 12, 18, 4, 7, 14, 20, 1, 5, 19, 10, 3, 17, 6, 13, 11, 16, 2, 9}));
    EXPECT_EQ((std::vector<int>{1, 2, 3, 4, 5, 6, 122, 222}), mergesort(std::vector<int>{5, 4,222, 2, 1, 122, 3, 6}));
    EXPECT_EQ((std::vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50}),
    mergesort(std::vector<int>{ 39, 12, 47, 23, 5, 18, 36, 45, 2, 49, 31, 8, 15, 28, 41, 7, 20, 4, 30, 11,
        42, 26, 13, 33, 22, 6, 16, 37, 50, 19, 3, 35, 10, 27, 46, 9, 34, 14, 48, 24,
        1, 29, 40, 17, 44, 21, 32, 25, 38, 43}
    ));
}

TEST(MergeSortTests, OddLengthList) {
    EXPECT_EQ((std::vector<int>{0}), mergesort(std::vector<int>{0}));
    EXPECT_EQ((std::vector<int>{-10, 7, 10, 40, 50}), mergesort(std::vector<int>{7, 50, 40, 10, -10}));
}


int main(int argc, char** argv){
    // std::vector<int> list{1, 4, 9, 2, 7, 8, 10};
    // std::vector<int> sorted{mergesort(list)};


    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS(); 
}