#include "001_karatsuba_multiplication.h"
#include <iostream>
#include <string>
#include <cmath>

// #define ENABLE_DEBUG

std::string getNumberString() {
    std::cout << "Enter a value: ";  
    std::string num_str{};
    std::cin >> num_str;
    return num_str;
}

std::string preprocessNumber(std::string x, int numZerosToPrepend) {
    std::string result{x};
    std::string zeros{};

    if (numZerosToPrepend == 0) { return result; }
    zeros.append(std::abs(numZerosToPrepend), '0');
    result.insert(0, zeros);
    return result;
}

int to_int(std::string x) {
    return std::stoi(x);
}

std::string multiplyStringDigits(std::string x, std::string y) {
    int _x = to_int(x);
    int _y = to_int(y);
    int result = _x * _y;
    return std::to_string(result);
}

std::string addStringDigits(std::string x, std::string y) {
    int _x = to_int(x);
    int _y = to_int(y);
    int result = _x + _y;
    return std::to_string(result);
}

std::string subStringDigits(std::string x, std::string y) {
    int _x = to_int(x);
    int _y = to_int(y);
    int result = _x - _y;
    return std::to_string(result);
}

std::string karatsuba(std::string str_x, std::string str_y) {
    int n; // length of strings
    int lengthDiff {(int)str_x.length() - (int)str_y.length()};

    if(str_x.length() == 1 && str_y.length() == 1) {
        #ifdef ENABLE_DEBUG
        std::cout << "base case reached for " << str_x << ", " << str_y << "\n";
        #endif
        return multiplyStringDigits(str_x, str_y);
    }

#ifdef ENABLE_DEBUG
    std::cout << "lendiff: " << lengthDiff << '\n';
#endif

    if (lengthDiff > 0) { // x has more digits
        if (str_x.length() % 2 == 1) {
            std::string zero{'0'};
            str_x.insert(0, zero);
            lengthDiff++;
        }
        str_y = preprocessNumber(str_y, lengthDiff); // adjust y, the smaller #
    } else { // y more digits
        if (str_y.length() % 2 == 1) {
            std::string zero{'0'};
            str_y.insert(0, zero);
            lengthDiff--;
        }
        str_x = preprocessNumber(str_x, lengthDiff);
    }
    
    n = str_x.length(); // arbitrary

#ifdef ENABLE_DEBUG
    std::cout << "str_x: " << str_x << '\n';
    std::cout << "str_y: " << str_y << '\n';
#endif

    //split
    std::string a {str_x.substr(0, n / 2)};
    std::string b {str_x.substr(n / 2)};
    std::string c {str_y.substr(0, n / 2)};
    std::string d {str_y.substr(n / 2)};

#ifdef ENABLE_DEBUG
    std::cout << "a: " << a << '\n';
    std::cout << "b: " << b << '\n';
    std::cout << "c: " << c << '\n';
    std::cout << "d: " << d << '\n';
#endif

    std::string ac = karatsuba(a,c);
    std::string bd = karatsuba(b,d);
    std::string pq = karatsuba(addStringDigits(a,b), addStringDigits(c,d));

    std::string adbc = subStringDigits(subStringDigits(pq, ac), bd);
    std::string product = addStringDigits(
        addStringDigits(
            multiplyStringDigits(std::to_string(std::pow(10, n)), ac),
            multiplyStringDigits(std::to_string(std::pow(10,n/2)), adbc)
        ),
        bd
    );

    return product;
}