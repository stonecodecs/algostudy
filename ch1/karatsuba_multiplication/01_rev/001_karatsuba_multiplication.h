#ifndef KARATSUBA_H
#define KARATSUBA_H
#include <string>

std::string getNumberString();
std::string preprocessNumber(std::string x, int numZerosToPrepend);
int to_int(std::string x);
std::string multiplyStringDigits(std::string x, std::string y);
std::string addStringDigits(std::string x, std::string y);
std::string subStringDigits(std::string x, std::string y);
std::string karatsuba(std::string x, std::string y);

#endif