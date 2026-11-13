#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <iostream>
#include <vector>
#include <numeric>

int linear_search(const std::vector<int>& A, int x);
int bin_search_1(const std::vector<int>& A, int x);
int bin_search_2(const std::vector<int>& A, int x);
int recursion_bin_search(const std::vector<int>& A, int x);

#endif