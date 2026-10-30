#include "multiply.hpp"

using namespace std;

// Стандартный алгоритм умножения матриц
Matrix multiply_standard(const Matrix &a, const Matrix &b)
{
    const size_t m = a.size();
    const size_t n = a[0].size();
    const size_t q = b[0].size();

    Matrix c = create_matrix(m, q, 0);

    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < q; ++j)
        {
            for (size_t k = 0; k < n; ++k)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    return c;
}

// Базовый алгоритм Винограда
Matrix multiply_winograd(const Matrix &a, const Matrix &b)
{
    const size_t m = a.size();
    const size_t n = a[0].size();
    const size_t q = b[0].size();

    Matrix c = create_matrix(m, q, 0);

    vector<int> row(m, 0);
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t k = 0; k < n / 2; ++k)
        {
            row[i] += a[i][2 * k] * a[i][2 * k + 1];
        }
    }

    vector<int> col(q, 0);
    for (size_t j = 0; j < q; ++j)
    {
        for (size_t k = 0; k < n / 2; ++k)
        {
            col[j] += b[2 * k][j] * b[2 * k + 1][j];
        }
    }

    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < q; ++j)
        {
            c[i][j] = -row[i] - col[j];
            for (size_t k = 0; k < n / 2; ++k)
            {
                c[i][j] += (a[i][2 * k] + b[2 * k + 1][j]) *
                           (a[i][2 * k + 1] + b[2 * k][j]);
            }
        }
    }

    if (n % 2 == 1)
    {
        for (size_t i = 0; i < m; ++i)
        {
            for (size_t j = 0; j < q; ++j)
            {
                c[i][j] += a[i][n - 1] * b[n - 1][j];
            }
        }
    }

    return c;
}

// Оптимизированный алгоритм Винограда:
// Вариант а): замена 2 * k на k << 1 с сохранением в two_k
// Вариант в): кэширование n / 2 в half_n перед входом в циклы
Matrix multiply_winograd_opt(const Matrix &a, const Matrix &b)
{
    const size_t m = a.size();
    const size_t n = a[0].size();
    const size_t q = b[0].size();

    Matrix c = create_matrix(m, q, 0);

    // Оптимизация в): кэширование n / 2
    const size_t half_n = n / 2;

    vector<int> row(m, 0);
    for (size_t i = 0; i < m; ++i)
    {
        for (size_t k = 0; k < half_n; ++k)
        {
            // Оптимизация а): побитовый сдвиг k << 1
            const size_t two_k = k << 1;
            row[i] += a[i][two_k] * a[i][two_k + 1];
        }
    }

    vector<int> col(q, 0);
    for (size_t j = 0; j < q; ++j)
    {
        for (size_t k = 0; k < half_n; ++k)
        {
            const size_t two_k = k << 1;
            col[j] += b[two_k][j] * b[two_k + 1][j];
        }
    }

    for (size_t i = 0; i < m; ++i)
    {
        for (size_t j = 0; j < q; ++j)
        {
            c[i][j] = -row[i] - col[j];
            for (size_t k = 0; k < half_n; ++k)
            {
                const size_t two_k = k << 1;
                c[i][j] += (a[i][two_k] + b[two_k + 1][j]) *
                           (a[i][two_k + 1] + b[two_k][j]);
            }
        }
    }

    if (n % 2 == 1)
    {
        const size_t last = n - 1;
        for (size_t i = 0; i < m; ++i)
        {
            for (size_t j = 0; j < q; ++j)
            {
                c[i][j] += a[i][last] * b[last][j];
            }
        }
    }

    return c;
}