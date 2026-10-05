#include "print.hpp"

using namespace std;

int input_N(int *N)
{
    cout << "Введите размер массива N: ";
    if (!(cin >> *N) || *N <= 0)
    {
        cout << "Ошибка ввода размера массива.\n";
        return 1;
    }
    return 0;
}

void print_main_menu()
{
    cout << "1. Поиск элемента x\n";
    cout << "0. Выход\n";
    cout << "\nВыберите действие: ";
}

int input_x(int *x)
{
    cout << "Введите искомое значение x: ";
    if (!(cin >> *x))
    {
        cout << "Ошибка ввода числа x.\n";
        return 1;
    }
    return 0;
}

void print_algo_menu()
{
    cout << "\nВыберите алгоритм поиска:\n";
    cout << "  1. Поиск полным перебором\n";
    cout << "  2. Бинарный поиск\n";
    cout << "  3. Бинарный поиск (ранний выход из цикла)\n";
    cout << "  4. Рекурсивный бинарный поиск\n";
    cout << "  0. Назад в главное меню\n";
    cout << "\nВаш выбор: ";
}

void print_algo_header(int algo_choice)
{
    switch (algo_choice)
    {
        case 1:
            cout << "\n[Результат линейного поиска] ";
            break;
        case 2:
            cout << "\n[Результат бинарного поиска 1] ";
            break;
        case 3:
            cout << "\n[Результат бинарного поиска 2] ";
            break;
        case 4:
            cout << "\n[Результат рекурсивного бинарного поиска] ";
            break;
    }
}

void print_search_result(int index, int x)
{
    if (index != -1)
        cout << "Элемент " << x << " найден по индексу: " << index << "\n";
    else
        cout << "Элемент " << x << " не найден в массиве.\n";
}