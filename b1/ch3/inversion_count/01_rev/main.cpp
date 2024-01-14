#define GTEST

#ifdef GTEST
#include "countInv.cpp"
#include <gtest/gtest.h>

TEST(InversionCountTest, BaseCase) {
        EXPECT_EQ(0, countInv(std::vector<long>{}));
        EXPECT_EQ(0, countInv(std::vector<long>{1}));
}

TEST(InversionCountTest, EvenLists) {
    EXPECT_EQ(1, countInv(std::vector<long>{3,1}));
    EXPECT_EQ(3, countInv(std::vector<long>{1,3,5,2,4,6}));
    EXPECT_EQ(15, countInv(std::vector<long>{6,5,4,3,2,1}));
    EXPECT_EQ(6, countInv(std::vector<long>{4,3,2,1}));
    EXPECT_EQ(28, countInv(std::vector<long>{54044,
                                            14108,
                                            79294,
                                            29649,
                                            25260,
                                            60660,
                                            2995,
                                            53777,
                                            49689,
                                            9083}));
}

TEST(InversionCountTest, OddLists) {
    EXPECT_EQ(2, countInv(std::vector<long>{3,1,2}));
    EXPECT_EQ(3, countInv(std::vector<long>{1,3,5,2,4,6,7}));
    EXPECT_EQ(21, countInv(std::vector<long>{7,6,5,4,3,2,1}));
    EXPECT_EQ(8, countInv(std::vector<long>{4,3,5,2,1}));
    EXPECT_EQ(45, countInv(std::vector<long>{10,9,8,7,6,5,4,3,2,1}));
}

TEST(InversionCountTest, FromFile) {
    std::string file_invalid {"notexistingfile.txt"};
    std::string file_valid {"problem3.5.txt"};
    std::vector<long> zerovec = file2vec(file_invalid);
    std::vector<long> vec = file2vec(file_valid);

    EXPECT_EQ(0, zerovec.size());
    EXPECT_EQ(100000, vec.size());
    EXPECT_EQ(0, countInv(zerovec));
    EXPECT_EQ(2407905288, countInv(vec));

}


int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif

#ifndef GTEST
#include "countInv.h"
#include <iostream>
long main(long argc, char** argv) {
    std::vector<long> ex1 {4,3,5,2,1};
    std::cout << countInv(ex1);
    return 0;
}
#endif