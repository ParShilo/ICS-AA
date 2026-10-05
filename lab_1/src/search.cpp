#include "search.hpp"

using namespace std;

// Полный перебор
int linear_search(const vector<int>& arr, int target)
{
    for (size_t i = 0; i < arr.size(); ++i)
        if (arr[i] == target)
            return static_cast<int>(i);

    return -1;
}

// Нерекурсивный бинарный поиск 1
int bin_search_1(const vector<int>& arr, int target)
{
    if (arr.empty())
        return -1;

    int l = 0, r = static_cast<int>(arr.size()) - 1, m;

    while (l < r)
    {
        m = l + (r - l) / 2;
        if (arr[m] < target)
            l = m + 1;
        else
            r = m;
    }

    if (l < static_cast<int>(arr.size()) && arr[l] == target)
        return l;

    return -1;
}

// Нерекурсивный бинарный поиск с предварительным выходом
int bin_search_2(const vector<int>& arr, int target)
{
    int l = 0, r = static_cast<int>(arr.size()) - 1, m;

    while (l <= r)
    {
        m = l + (r - l) / 2;

        if (arr[m] == target)
            return m;
        if (arr[m] < target)
            l = m + 1;
        else
            r = m - 1;
    }

    return -1;
}

// Рекурсивный бинарный поиск
// Внутреняя часть
int recursion_bin_search(const vector<int>& arr, int target, int l, int r)
{
    if (l > r)
        return -1;

    int m = l + (r - l) / 2;
    
    if (arr[m] == target)
        return m;

    if (arr[m] < target)
        return recursion_bin_search(arr, target, m + 1, r);
    return recursion_bin_search(arr, target, l, m - 1);
}

// Внешняя часть
int recursion_bin_search(const vector<int>& arr, int target)
{
    if (arr.empty())
        return -1;
    return recursion_bin_search(arr, target, 0, static_cast<int>(arr.size()) - 1);
}

