#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include "multiply.hpp"

using namespace std;

using MultiplyFunc = function<Matrix(const Matrix&, const Matrix&, size_t, size_t, size_t)>;

struct TestCase
{
    string description;
    Matrix a;
    Matrix b;
    Matrix expected;
};

bool run_single_test(const TestCase& test, MultiplyFunc func)
{
    size_t m = test.a.size();
    size_t n = test.a.empty() ? 0 : test.a[0].size();
    size_t q = test.b.empty() ? 0 : test.b[0].size();

    Matrix result = func(test.a, test.b, m, n, q);
    return result == test.expected;
}

int run_suite(const string& func_name, MultiplyFunc func)
{
    vector<TestCase> tests =
    {
        {
            "Матрицы 1x1",
            {{3}},
            {{-4}},
            {{-12}}
        },
        {
            "Умножение на единичную матрицу 3x3",
            {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
            {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}},
            {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}
        },
        {
            "Умножение на нулевую матрицу 2x2",
            {{1, 2}, {3, 4}},
            {{0, 0}, {0, 0}},
            {{0, 0}, {0, 0}}
        },
        {
            "Квадратные матрицы 2x2 (чётный размер)",
            {{1, 2}, {3, 4}},
            {{5, 6}, {7, 8}},
            {{19, 22}, {43, 50}}
        },
        {
            "Квадратные матрицы 3x3 (нечётный размер)",
            {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
            {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}},
            {{30, 24, 18}, {84, 69, 54}, {138, 114, 90}}
        },
        {
            "Прямоугольные 2x3 и 3x2 (нечётный общий размер)",
            {{1, 2, 3}, {4, 5, 6}},
            {{7, 8}, {9, 10}, {11, 12}},
            {{58, 64}, {139, 154}}
        },
        {
            "Прямоугольные 3x2 и 2x4 (чётный общий размер)",
            {{1, 2}, {3, 4}, {5, 6}},
            {{1, 2, 3, 4}, {5, 6, 7, 8}},
            {{11, 14, 17, 20}, {23, 30, 37, 44}, {35, 46, 57, 68}}
        },
        {
            "Строка на столбец (1x4 на 4x1)",
            {{1, 2, 3, 4}},
            {{1}, {2}, {3}, {4}},
            {{30}}
        },
        {
            "Столбец на строку (3x1 на 1x2)",
            {{1}, {2}, {3}},
            {{4, 5}},
            {{4, 5}, {8, 10}, {12, 15}}
        }
    };

    int passed = 0;
    cout << "\n=== Тестирование функции: " << func_name << " ===\n";

    for (size_t i = 0; i < tests.size(); ++i)
    {
        bool ok = run_single_test(tests[i], func);
        if (ok)
        {
            cout << "  [OK] Test " << (i + 1) << ": " << tests[i].description << "\n";
            passed++;
        }
        else
        {
            cout << "  [FAIL] Test " << (i + 1) << ": " << tests[i].description << "\n";
        }
    }

    bool stress_ok = true;
    for (size_t n = 1; n <= 8; ++n)
    {
        Matrix rand_a = generate_matrix(n, n);
        Matrix rand_b = generate_matrix(n, n);
        Matrix expected = multiply_standard(rand_a, rand_b, n, n, n);
        if (func(rand_a, rand_b, n, n, n) != expected)
        {
            stress_ok = false;
            break;
        }
    }

    if (stress_ok)
    {
        cout << "  [OK] Стресс-тест на случайных матрицах (размеры 1..8)\n";
        passed++;
    }
    else
    {
        cout << "  [FAIL] Стресс-тест на случайных матрицах\n";
    }

    const size_t total_tests = tests.size() + 1;
    cout << "Итого " << func_name << ": " << passed << "/" << total_tests << " passed.\n";

    return (passed == static_cast<int>(total_tests)) ? 0 : 1;
}

int main()
{
    int status = 0;

    status |= run_suite("multiply_standard", multiply_standard);
    status |= run_suite("multiply_winograd", multiply_winograd);
    status |= run_suite("multiply_winograd_opt", multiply_winograd_opt);

    if (status == 0)
        cout << "\n Все тесты прошли успешно!\n";
    else
        cout << "\n Не все тесты прошли!\n";

    return status;
}