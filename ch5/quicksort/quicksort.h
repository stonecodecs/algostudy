#ifndef QUICKSORT_H
#define QUICKSORT_H
#include<iostream>
#include<vector>

std::vector<int> quicksort(std::vector<int> unsorted);
std::vector<int> _quicksort(std::vector<int> unsorted, int start, int end);
std::vector<int> swap(std::vector<int> set, int index1, int index2);
std::vector<int> partition(std::vector<int> set, int start, int end);

#endif