#pragma once

#include "matrix.hpp"

// Стандартный алгоритм умножения матриц
Matrix multiply_standard(const Matrix &A, const Matrix &B, size_t M, size_t N, size_t Q);

// Базовый алгоритм Винограда
Matrix multiply_winograd(const Matrix &A, const Matrix &B, size_t M, size_t N, size_t Q);

// Оптимизированный алгоритм Винограда (оптимизации: а + в)
Matrix multiply_winograd_opt(const Matrix &A, const Matrix &B, size_t M, size_t N, size_t Q);