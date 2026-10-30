#pragma once

#include "matrix.hpp"

// Стандартный алгоритм умножения матриц
Matrix multiply_standard(const Matrix &a, const Matrix &b);

// Базовый алгоритм Винограда
Matrix multiply_winograd(const Matrix &a, const Matrix &b);

// Оптимизированный алгоритм Винограда (оптимизации: а + в)
Matrix multiply_winograd_opt(const Matrix &a, const Matrix &b);