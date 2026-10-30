#include "matrix.hpp"
#include <iostream>
#include <random>
#include <limits>

using namespace std;

Matrix create_matrix(size_t rows, size_t cols, int init_val)
{
    return Matrix(rows, vector<int>(cols, init_val));
}

Matrix generate_matrix(size_t rows, size_t cols, int min_val, int max_val)
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> dist(min_val, max_val);

    Matrix mat = create_matrix(rows, cols);
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            mat[i][j] = dist(gen);
        }
    }

    return mat;
}

int input_dimensions(size_t *m, size_t *n, size_t *q)
{
    cout << "Введите размеры матриц M, N, Q (A[M x N] * B[N x Q]): ";
    if (!(cin >> *m >> *n >> *q) || *m == 0 || *n == 0 || *q == 0)
    {
        cout << "Ошибка ввода размеров матриц.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 1;
    }

    return 0;
}

int input_matrix(Matrix &mat, const string &name)
{
    cout << "Введите элементы матрицы " << name << " (" << mat.size() << "x" << mat[0].size() << "):\n";
    for (size_t i = 0; i < mat.size(); ++i)
    {
        for (size_t j = 0; j < mat[0].size(); ++j)
        {
            if (!(cin >> mat[i][j]))
            {
                cout << "Ошибка ввода элемента матрицы.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return 1;
            }
        }
    }

    return 0;
}