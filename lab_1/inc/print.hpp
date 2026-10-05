#ifndef PRINT_HPP
#define PRINT_HPP

#include <iostream>

int input_N(int *N);

void print_main_menu();

int input_x(int *x);

void print_algo_menu();
void print_algo_header(int algo_choice);

void print_search_result(int index, int x);

#endif // PRINT_HPP