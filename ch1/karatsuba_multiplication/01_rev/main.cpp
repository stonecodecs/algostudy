#include "001_karatsuba_multiplication.h"
#include <iostream>
#include <string>

int main() {
    std::string X {getNumberString()};
    std::string Y {getNumberString()};
    std::string result = karatsuba(X, Y);
    std::cout << "final result: " << result << "\n";
    return 0;
}