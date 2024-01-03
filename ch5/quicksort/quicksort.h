#ifndef QUICKSORT_H
#define QUICKSORT_H
#include<iostream>
#include<vector>
#include<algorithm>
#include<stdexcept>
#include<cstdlib>

enum class PivotSelector
{
    RANDOM,
    FIRST,
    LAST,
    MEDIANS
};

std::vector<int> quicksort(std::vector<int> unsorted, PivotSelector ps=PivotSelector::RANDOM);
std::vector<int> _quicksort(std::vector<int> &unsorted, int start, int end, PivotSelector ps=PivotSelector::RANDOM);
void swap(std::vector<int> &set, int index1, int index2);
int partition(std::vector<int> &set, int start, int end);
int rng(int min, int max);
std::vector<int> selectPivot(std::vector<int> &set, int start, int end, PivotSelector ps);
void printVector(const std::vector<int>& vec);

#endif