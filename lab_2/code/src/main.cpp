#include <iostream>
#include <limits>
#include "matrix.hpp"
#include "multiply.hpp"
#include "print.hpp"
#include "bench.hpp"

using namespace std;

int main()
{
    size_t m = 3, n = 3, q = 3;
    if (input_dimensions(&m, &n, &q))
        return 1;

    Matrix mat_a = generate_matrix(m, n);
    Matrix mat_b = generate_matrix(n, q);

    cout << "\nСгенерированы исходные матрицы:\n";
    cout << "Матрица A:\n";
    print_matrix(mat_a);
    cout << "Матрица B:\n";
    print_matrix(mat_b);

    while (true)
    {
        print_menu();

        int choice;
        if (!(cin >> choice))
        {
            cout << "Ошибка ввода. Попробуйте снова.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        Matrix res;

        switch (choice)
        {
            case 1:
                res = multiply_standard(mat_a, mat_b, m, n, q);
                print_algo_header(1);
                print_matrix(res);
                break;

            case 2:
                res = multiply_winograd(mat_a, mat_b, m, n, q);
                print_algo_header(2);
                print_matrix(res);
                break;

            case 3:
                res = multiply_winograd_opt(mat_a, mat_b, m, n, q);
                print_algo_header(3);
                print_matrix(res);
                break;

            case 4:
                mat_a = generate_matrix(m, n);
                mat_b = generate_matrix(n, q);
                cout << "\nМатрицы успешно перегенерированы.\n";
                break;

            case 5:
                if (input_dimensions(&m, &n, &q)) break;
                mat_a = create_matrix(m, n);
                mat_b = create_matrix(n, q);
                if (input_matrix(mat_a, "A") || input_matrix(mat_b, "B")) break;
                cout << "\nМатрицы успешно обновлены.\n";
                break;

            case 6:
                cout << "\nМатрица A (" << m << "x" << n << "):\n";
                print_matrix(mat_a);
                cout << "\nМатрица B (" << n << "x" << q << "):\n";
                print_matrix(mat_b);
                break;

            case 7:
                run_comparison_benchmarks();
                break;

            case 0:
                cout << "Завершение работы программы.\n";
                return 0;

            default:
                cout << "Неверный выбор, попробуйте снова.\n";
                break;
        }
    }

    return 0;
}