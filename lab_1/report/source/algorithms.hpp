#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <vector>

int linear_search(const vector<int>& A, int x)
{
    int index = -1;
    for (size_t i = 0; i < A.size(); ++i)
    {
        if (A[i] == x)
        {
            index = i;
            break;
        }
    }

    return index;
}

int bin_search_1(const vector<int>& A, int x)
{
    if (A.empty())
        return -1;

    int l = 0, r = A.size() - 1, m;

    while (l < r)
    {
        m = l + (r - l) / 2;
        if (A[m] < x)
            l = m + 1;
        else
            r = m;
    }

    if (l < A.size() && A[l] == x)
        return l;

    return -1;
}

int bin_search_2(const vector<int>& A, int x)
{
    int l = 0, r = A.size() - 1, m;

    while (l <= r)
    {
        m = l + (r - l) / 2;

        if (A[m] == x)
            return m;
        if (A[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }

    return -1;
}

int recursion_bin_search(const vector<int>& A, int x, int l, int r)
{
    if (l > r)
        return -1;

    int m = l + (r - l) / 2;
    
    if (A[m] == x)
        return m;

    if (A[m] < x)
        return recursion_bin_search(A, x, m + 1, r);
    return recursion_bin_search(A, x, l, m - 1);
}

int recursion_bin_search(const vector<int>& A, int x)
{
    if (A.empty())
        return -1;
    return recursion_bin_search(A, x, 0, A.size() - 1);
}


static int linear_search(const vector<int>& A, int x, size_t* count = nullptr)
{
    int index = -1;
    for (size_t i = 0; i < A.size(); ++i)
    {
        if (count) 
            (*count)++;
        if (A[i] == x)
        {
            index = i;
            break;
        }
    }
    return index;
}

static int bin_search_1(const vector<int>& A, int x, size_t* count = nullptr)
{
    if (A.empty())
        return -1;

    int l = 0, r = static_cast<int>(A.size()) - 1, m;

    while (l < r)
    {
        m = l + (r - l) / 2;
        if (count)
            (*count)++;
        if (A[m] < x)
            l = m + 1;
        else
            r = m;
    }

    if (count) 
        (*count)++;
    if (A[l] == x)
        return l;

    return -1;
}

static int bin_search_2(const vector<int>& A, int x, size_t* count = nullptr)
{
    if (A.empty())
        return -1;

    int l = 0, r = static_cast<int>(A.size()) - 1, m;

    while (l <= r)
    {
        m = l + (r - l) / 2;

        if (count) 
            (*count)++;
        if (A[m] == x)
            return m;
        
        if (count) 
            (*count)++;
        if (A[m] < x)
            l = m + 1;
        else
            r = m - 1;
    }

    return -1;
}

static int recursion_bin_search(const vector<int>& A, int x, int l, int r, size_t* count = nullptr)
{
    if (l > r)
        return -1;

    int m = l + (r - l) / 2;
    
    if (count) 
        (*count)++;
    if (A[m] == x)
        return m;

    if (count) 
        (*count)++;
    if (A[m] < x)
        return recursion_bin_search(A, x, m + 1, r, count);
    
    return recursion_bin_search(A, x, l, m - 1, count);
}

static int recursion_bin_search(const vector<int>& A, int x, size_t* count = nullptr)
{
    if (A.empty())
        return -1;
    return recursion_bin_search(A, x, 0, static_cast<int>(A.size()) - 1, count);
}

#endif