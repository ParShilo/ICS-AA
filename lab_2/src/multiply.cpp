#include "multiply.hpp"

using namespace std;

// Стандартный алгоритм умножения матриц
Matrix multiply_standard(const Matrix &A, const Matrix &B)
{
    const size_t M = A.size();
    const size_t N = A[0].size();
    const size_t Q = B[0].size();

    Matrix C = create_matrix(M, Q, 0);

    for (size_t i = 0; i < M; ++i)
        for (size_t j = 0; j < Q; ++j)
            for (size_t k = 0; k < N; ++k)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}

// Базовый алгоритм Винограда
Matrix multiply_winograd(const Matrix &A, const Matrix &B)
{
    const size_t M = A.size();
    const size_t N = A[0].size();
    const size_t Q = B[0].size();

    Matrix C = create_matrix(M, Q, 0);

    vector<int> row(M, 0);
    for (size_t i = 0; i < M; ++i)
        for (size_t j = 0; j < N / 2; ++j)
            row[i] += A[i][2 * j] * A[i][2 * j + 1];

    vector<int> col(Q, 0);
    for (size_t i = 0; i < Q; ++i)
        for (size_t j = 0; j < N / 2; ++j)
            col[i] += B[2 * j][i] * B[2 * j + 1][i];

    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < Q; ++j)
        {
            C[i][j] = -row[i] - col[j];
            for (size_t k = 0; k < N / 2; ++k)
                C[i][j] += (A[i][2 * k] + B[2 * k + 1][j]) * (A[i][2 * k + 1] + B[2 * k][j]);
        }
    }

    if (N % 2 == 1)
        for (size_t i = 0; i < M; ++i)
            for (size_t j = 0; j < Q; ++j)
                C[i][j] += A[i][N - 1] * B[N - 1][j];

    return C;
}

// Оптимизированный алгоритм Винограда:
// Вариант а): замена 2 * k на k << 1 с сохранением в two_k
// Вариант в): кэширование N / 2 в half_n перед входом в циклы
Matrix multiply_winograd_opt(const Matrix &A, const Matrix &B)
{
    const size_t M = A.size();
    const size_t N = A[0].size();
    const size_t Q = B[0].size();

    Matrix C = create_matrix(M, Q, 0);

    // Оптимизация в): кэширование N / 2
    const size_t half_n = N / 2;

    vector<int> row(M, 0);
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t k = 0; k < half_n; ++k)
        {
            // Оптимизация а): побитовый сдвиг k << 1
            const size_t two_k = k << 1;
            row[i] += A[i][two_k] * A[i][two_k + 1];
        }
    }

    vector<int> col(Q, 0);
    for (size_t j = 0; j < Q; ++j)
    {
        for (size_t k = 0; k < half_n; ++k)
        {
            const size_t two_k = k << 1;
            col[j] += B[two_k][j] * B[two_k + 1][j];
        }
    }

    for (size_t i = 0; i < M; ++i)
    {
        for (size_t j = 0; j < Q; ++j)
        {
            C[i][j] = -row[i] - col[j];
            for (size_t k = 0; k < half_n; ++k)
            {
                const size_t two_k = k << 1;
                C[i][j] += (A[i][two_k] + B[two_k + 1][j]) * (A[i][two_k + 1] + B[two_k][j]);
            }
        }
    }

    if (N % 2 == 1)
        for (size_t i = 0; i < M; ++i)
            for (size_t j = 0; j < Q; ++j)
                C[i][j] += A[i][N - 1] * B[N - 1][j];

    return C;
}