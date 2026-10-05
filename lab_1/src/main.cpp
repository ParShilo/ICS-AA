#include <iostream>
#include <vector>
#include <algorithm>
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
        cout << "\nМассив: ";
        print_array(sorted_arr);
        print_main_menu();

        int main_choice;
        if (!(cin >> main_choice) || main_choice == 0) 
        {
            cout << "Завершение работы программы.\n";
            break;
        }

        if (main_choice != 1)
        {
            cout << "Неверный пункт меню, попробуйте снова.\n";
            continue;
        }

        int x;
        if (input_x(&x) != 0)
            break;

        print_algo_menu();

        int algo_choice;
        if (!(cin >> algo_choice)) 
            break;

        int index = -1;
        bool valid_algo = true;

        switch (algo_choice)
        {
            case 1:
                index = linear_search(sorted_arr, x);
                break;
            case 2:
                index = bin_search_1(sorted_arr, x);
                break;
            case 3:
                index = bin_search_2(sorted_arr, x);
                break;
            case 4:
                index = recursion_bin_search(sorted_arr, x);
                break;
            case 0:
                valid_algo = false;
                break;
            default:
                cout << "Неверный выбор алгоритма.\n";
                valid_algo = false;
                break;
        }

        if (valid_algo)
        {
            print_algo_header(algo_choice);
            print_search_result(index, x);
        }
    }

    return 0;
}