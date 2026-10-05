#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <cstdlib>

#include "search.hpp"

using SearchFunc = std::function<int(const std::vector<int>&, int)>;

struct TestCase 
{
    std::string description;
    std::vector<int> arr;
    int target;
    int expected_index; 
};

bool run_single_test(const TestCase& test, SearchFunc func)
{
    int result = func(test.arr, test.target);

    if (test.expected_index == -1 && result == -1)
        return true;
    if (result >= 0 && result < static_cast<int>(test.arr.size()) && test.arr[result] == test.target) 
        return true;
    
    return false;
}

int run_suite(const std::string& func_name, SearchFunc func) 
{
    std::vector<TestCase> tests = 
    {
        {"Пустой массив", {}, 5, -1},
        {"Массив из одного элемента (есть в списке)", {10}, 10, 0},
        {"Массив из одного элемента (нет в списке)", {10}, 5, -1},
        {"Массив из двух элементов, первый искомый", {10, 20}, 10, 0},
        {"Массив из двух элементов, второй искомый", {10, 20}, 20, 1},
        {"Массив из двух элементов, нет искомого", {10, 20}, 15, -1},
        {"Массив нечётной длины, первый искомый", {1, 3, 5, 7, 9}, 1, 0},
        {"Массив нечётной длины, последний искомый", {1, 3, 5, 7, 9}, 9, 4},
        {"Массив нечётной длины, искомый элемент в середине массива", {1, 3, 5, 7, 9}, 5, 2},
        {"Массив нечётной длины, нет искомого", {1, 3, 5, 7, 9}, 0, -1},
        {"Массив чётной длины, первый искомый", {1, 3, 5, 7}, 1, 0},
        {"Массив чётной длины, последний искомый", {1, 3, 5, 7}, 7, 3},
        {"Массив чётной длины, искомый элемент в середине массива", {1, 3, 5, 7}, 5, 2},
        {"Массив чётной длины, нет искомого", {1, 3, 5, 7}, 0, -1},
    };

    int passed = 0;
    std::cout << "\n=== Тестирование функции: " << func_name << " ===\n";

    for (size_t i = 0; i < tests.size(); ++i) 
    {
        bool ok = run_single_test(tests[i], func);
        if (ok) 
        {
            std::cout << "  [OK] Test " << (i + 1) << ": " << tests[i].description << "\n";
            passed++;
        } 
        else
            std::cout << "  [FAIL] Test " << (i + 1) << ": " << tests[i].description << "\n";
    }

    std::cout << "Итого " << func_name << ": " << passed << "/" << tests.size() << " passed.\n";
    return (passed == static_cast<int>(tests.size())) ? 0 : 1;
}

int main() 
{
    int status = 0;

    status |= run_suite("linear_search", linear_search);
    status |= run_suite("bin_search_1", bin_search_1);
    status |= run_suite("bin_search_2", bin_search_2);
    status |= run_suite("recursion_bin_search", recursion_bin_search);

    if (status == 0)
        std::cout << "\n Все тесты прошли\n";
    else
        std::cout << "\n Не все тесты прошли\n";

    return status;
}