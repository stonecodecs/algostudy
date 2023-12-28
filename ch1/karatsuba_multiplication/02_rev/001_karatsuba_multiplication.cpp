#include "001_karatsuba_multiplication.h"
#include <iostream>
#include <cmath>
#include <algorithm>

long getNumber() {
    std::cout << "Enter a value: ";  
    long num{};
    std::cin >> num;
    return num;
}

long numDigits(long x) {
    if (x < 10) { return 1; }
    return numDigits(x / 10) + 1;
}

long karatsuba(long x, long y) {
    long N = numDigits(std::max(x, y));

    if(N < 2) { return x*y; }

    long a {x / (long)std::pow(10, (N+1)/2)};
    long b {x - a * (long)std::pow(10, (N+1)/2)};
    long c {y / (long)std::pow(10, (N+1)/2)};
    long d {y - c * (long)std::pow(10, (N+1)/2)};

    long ac = karatsuba(a,c);
    long bd = karatsuba(b,d);
    long pq = karatsuba((a+b), (c+d));
    long adbc = pq - ac - bd;
    long product {(long)std::pow(10, 2*((N+1)/2)) * ac + (long)std::pow(10, (N+1)/2) * adbc + bd};

    return product;
}