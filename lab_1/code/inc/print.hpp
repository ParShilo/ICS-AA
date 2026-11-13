#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>
#include <limits>

int input_N(int *N);

int input_x(int *x);

void print_menu();
void print_algo_header(int algo_choice);

void print_search_result(int index, int x);

#endif // PRINT_HPP