#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>


long countInv(std::vector<long> a);
long countInv(std::vector<long>* a, long start, long end);
long countSplitInvAndMerge(std::vector<long>* a, long start, long end, long mid);

std::vector<long> file2vec(std::string file_path);
