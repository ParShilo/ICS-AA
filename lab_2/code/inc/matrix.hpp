#pragma once

#include <vector>
#include <cstddef>
#include <string>

using Matrix = std::vector<std::vector<int>>;

Matrix create_matrix(size_t rows, size_t cols, int init_val = 0);
Matrix generate_matrix(size_t rows, size_t cols, int min_val = -10, int max_val = 10);
int input_dimensions(size_t *m, size_t *n, size_t *q);
int input_matrix(Matrix &mat, const std::string &name);