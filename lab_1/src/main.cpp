#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include "array.hpp"
#include "search.hpp"
#include "print.hpp"

using namespace std;

int main()
{
    int rc = 0, N;
    rc = input_N(&N);
    if (rc)
        return rc;

    vector<int> original_arr = generate_array(N);
    vector<int> sorted_arr = original_arr;
    sort(sorted_arr.begin(), sorted_arr.end());

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

        int x;
        int index = -1;

        switch (choice)
        {
            case 1:
                if (input_x(&x)) continue;
                index = linear_search(sorted_arr, x);
                print_algo_header(1);
                print_search_result(index, x);
                break;

            case 2:
                if (input_x(&x)) continue;
                index = bin_search_1(sorted_arr, x);
                print_algo_header(2);
                print_search_result(index, x);
                break;

            case 3:
                if (input_x(&x)) continue;
                index = bin_search_2(sorted_arr, x);
                print_algo_header(3);
                print_search_result(index, x);
                break;

            case 4:
                if (input_x(&x)) continue;
                index = recursion_bin_search(sorted_arr, x);
                print_algo_header(4);
                print_search_result(index, x);
                break;

            case 5:
                cout << "\nМассив: ";
                print_array(sorted_arr);
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