#ifndef SECONDMAX
#define SECONDMAX

#include <vector>
#include <limits.h>
#include <stdexcept>
#include <iostream>

std::vector<int> createSubarray(std::vector<int> a, int start, int end);
void printList(std::vector<int> a);
int secondMax(std::vector<int> a);
std::vector<int> findMax(std::vector<int> a);

#endif