#ifndef SELECT_H
#define SELECT_H
#include<iostream>
#include<vector>

int rselect(std::vector<int> set, int x);
int _rselect(std::vector<int> &set, int index1, int index2, int x);
int dselect(std::vector<int> set, int x);
int _dselect(std::vector<int> &set, int index1, int index2, int x);
void swap(std::vector<int> &set, int index1, int index2);
int partition(std::vector<int> &set, int start, int end);
int rng(int min, int max);
std::vector<int> selectRandomPivot(std::vector<int> &set, int start, int end);
void printVector(const std::vector<int>& vec);

#endif