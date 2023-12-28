#include "secondmax.cpp"
#include <gtest/gtest.h>

TEST(SecondMaxTests, EmptyList) {
    EXPECT_THROW({secondMax(std::vector<int>{});}, std::invalid_argument);
}

TEST(SecondMaxTests, SingleElement) {
    EXPECT_THROW({secondMax(std::vector<int>{42});}, std::invalid_argument);
}

TEST(SecondMaxTests, TwoElementsInDescendingOrder) {
    EXPECT_EQ(7, secondMax(std::vector<int>{9, 7, 3, 4, 2}));
}

TEST(SecondMaxTests, TwoElementsInAscendingOrder) {
    EXPECT_EQ(11, secondMax(std::vector<int>{7, 9, 10, 11, 28}));
}

TEST(SecondMaxTests, MultipleElements) {
    EXPECT_EQ(12, secondMax(std::vector<int>{12, 8, 18, 6, 10}));
    EXPECT_EQ(14, secondMax(std::vector<int>{14, 15, 3, 1, 2, 7, 0, 13}));
    EXPECT_EQ(30, secondMax(std::vector<int>{14, 29, 8, 5, 21, 10, 27, 3, 18, 12, 
    25, 7, 15, 20, 9, 30, 6, 24, 1, 22, 11, 28, 17, 4, 19, 13, 26, 2, 23, 16, 30, 31}));
}

TEST(SecondMaxTests, DuplicateValues) {
    EXPECT_EQ(15, secondMax(std::vector<int>{10, 15, 10, 5, 15}));
}

TEST(SecondMaxTests, AllEqualValues) {
    EXPECT_EQ(3, secondMax(std::vector<int>{3, 3, 3, 3, 3}));
}

TEST(SecondMaxTests, LargeValues) {
    EXPECT_EQ(500, secondMax(std::vector<int>{100, 500, 999, 200, 300}));
}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}