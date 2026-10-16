#include "counts.hpp"

using namespace std;

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
        (*count)++; // Считаем финальную проверку A[l] == x
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
            (*count)++; // Считаем сравнение A[m] == x
        if (A[m] == x)
            return m;
        
        if (count) 
            (*count)++; // Считаем сравнение A[m] < x
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


void run_comparison_tests(size_t N)
{
    vector<int> A(N);
    for (size_t i = 0; i < N; ++i)
        A[i] = static_cast<int>(i);

    int w_n = 8;
    int w_case = 14;
    int w_alg = 12;
    int total_width = w_n + w_case + w_alg * 4;

    cout << "\n" << string(total_width, '=') << "\n";
    cout << left << setw(w_n) << "N" 
         << setw(w_case) << "Случай" 
         << setw(w_alg) << "Linear" 
         << setw(w_alg) << "Bin_1" 
         << setw(w_alg) << "Bin_2" 
         << setw(w_alg) << "Rec_Bin" << "\n";
    cout << string(total_width, '-') << "\n";

    int x_best_lin = A[0];          
    int x_best_b1 = A[0];           
    int x_best_b2 = A[(N - 1) / 2]; 
    int x_best_rec = A[(N - 1) / 2];

    size_t c_lin = 0, c_b1 = 0, c_b2 = 0, c_rec = 0;
    linear_search(A, x_best_lin, &c_lin);
    bin_search_1(A, x_best_b1, &c_b1);
    bin_search_2(A, x_best_b2, &c_b2);
    recursion_bin_search(A, x_best_rec, &c_rec);

    cout << left << setw(w_n) << N 
         << setw(w_case) << "Лучший" 
         << setw(w_alg) << c_lin 
         << setw(w_alg) << c_b1 
         << setw(w_alg) << c_b2 
         << setw(w_alg) << c_rec << "\n";

    int x_worst_lin_b1 = -1;          
    int x_worst_b2_rec = A.back() + 1;

    c_lin = c_b1 = c_b2 = c_rec = 0;
    linear_search(A, x_worst_lin_b1, &c_lin);
    bin_search_1(A, x_worst_lin_b1, &c_b1);
    bin_search_2(A, x_worst_b2_rec, &c_b2);
    recursion_bin_search(A, x_worst_b2_rec, &c_rec);

    cout << left << setw(w_n) << N 
         << setw(w_case) << "Худший" 
         << setw(w_alg) << c_lin 
         << setw(w_alg) << c_b1 
         << setw(w_alg) << c_b2 
         << setw(w_alg) << c_rec << "\n";

    cout << string(total_width, '=') << "\n\n";
}