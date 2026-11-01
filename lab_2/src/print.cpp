#include "print.hpp"
#include <iostream>

using namespace std;

void print_menu()
{
    cout << "\n                   МЕНЮ                    "
         << "\n1. Умножение матриц: стандартный алгоритм"
         << "\n2. Умножение матриц: базовый алгоритм Винограда"
         << "\n3. Умножение матриц: оптимизированный алгоритм Винограда"
         << "\n4. Сгенерировать новые матрицы случайным образом"
         << "\n5. Ввести матрицы вручную с клавиатуры"
         << "\n6. Вывести текущие матрицы A и B"
         << "\n7. Запустить замеры процессорного времени"
         << "\n0. Выход из программы"
         << "\n"
         << "\nВыберите пункт меню: ";
}

void print_algo_header(int algo_id)
{
    cout << "\n--- ";
    switch (algo_id)
    {
        case 1:
            cout << "Стандартный алгоритм умножения матриц";
            break;
        case 2:
            cout << "Базовый алгоритм Винограда";
            break;
        case 3:
            cout << "Оптимизированный алгоритм Винограда (опт. а + в)";
            break;
        default:
            break;
    }
    cout << " ---\n";
}

void print_matrix(const Matrix &m)
{
    for (const auto &row : m)
    {
        for (int val : row)
        {
            cout << val << "\t";
        }
        cout << "\n";
    }
}