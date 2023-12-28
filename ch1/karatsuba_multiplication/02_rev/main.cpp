#include "001_karatsuba_multiplication.cpp"
// #include "001_karatsuba_multiplication.h"
#include <iostream>
#include <gtest/gtest.h>

TEST(KaratsubaTests, sameDigitNumbers) {
    EXPECT_EQ(26437216, karatsuba(9872, 2678));
    EXPECT_EQ(2304, karatsuba(32, 72));
    EXPECT_EQ(27084, karatsuba(122, 222));
}

TEST(KaratsubaTests, diffDigitNumbers) {
    EXPECT_EQ(23398128, karatsuba(99992, 234));
    EXPECT_EQ(5040, karatsuba(7, 720));
}

TEST(KaratsubaTests, edgeCases) {
    EXPECT_EQ(0, karatsuba(0, 0));
    EXPECT_EQ(5040, karatsuba(7, 720));
}


int main(int argc, char **argv) {
    // long X {getNumber()};
    // long Y {getNumber()};
    // long result = karatsuba(X, Y);
    // std::cout << "final result: " << result << "\n";
    // return 0;
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}