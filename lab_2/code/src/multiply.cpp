#include "multiply.hpp"

using namespace std;

Matrix multiply_standard(const Matrix &A, const Matrix &B, size_t M, size_t N, size_t Q)
{
    Matrix C = create_matrix(M, Q, 0);

    for (size_t i = 0; i < M; ++i)
        for (size_t j = 0; j < Q; ++j)
            for (size_t k = 0; k < N; ++k)
                C[i][j] += A[i][k] * B[k][j];

    return C;
}

Matrix multiply_winograd(const Matrix &A, const Matrix &B, size_t M, size_t N, size_t Q)
{
    Matrix C = create_matrix(M, Q, 0);

    vector<int> row(M, 0);
    for (size_t i = 0; i < M; ++i)
        for (size_t j = 0; j < N / 2; ++j)
            row[i] += A[i][2 * j] * A[i][2 * j + 1];

    vector<int> col(Q, 0);
    for (size_t j = 0; j < Q; ++j)
        for (size_t i = 0; i < N / 2; ++i)
            col[j] += B[2 * i][j] * B[2 * i + 1][j];

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

Matrix multiply_winograd_opt(const Matrix &A, const Matrix &B, size_t M, size_t N, size_t Q)
{
    Matrix C = create_matrix(M, Q, 0);
    const size_t half_n = N / 2;
    size_t two_k;

    vector<int> row(M, 0);
    for (size_t i = 0; i < M; ++i)
    {
        for (size_t k = 0; k < half_n; ++k)
        {
            two_k = k << 1;
            row[i] += A[i][two_k] * A[i][two_k + 1];
        }
    }

    vector<int> col(Q, 0);
    for (size_t j = 0; j < Q; ++j)
    {
        for (size_t k = 0; k < half_n; ++k)
        {
            two_k = k << 1;
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
                two_k = k << 1;
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