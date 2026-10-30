#include "bench.hpp"
#include "multiply.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <functional>

using namespace std;

static double measure_time_sec(function<Matrix()> func, int repeats)
{
    clock_t start = clock();
    for (int i = 0; i < repeats; ++i)
    {
        volatile Matrix res = func();
        (void)res;
    }
    clock_t end = clock();

    return static_cast<double>(end - start) / (CLOCKS_PER_SEC * repeats);
}

void run_comparison_benchmarks()
{
    cout << "\nЗапуск массированных замеров процессорного времени...\n";

    ofstream file_even("results_even.csv");
    ofstream file_odd("results_odd.csv");

    const string header = "N,Standard,Winograd,Winograd_Opt\n";
    file_even << header;
    file_odd << header;

    // Сетка чётных и нечётных размеров N
    const vector<size_t> sizes_even = {10, 20, 40, 60, 80, 100, 150, 200, 250, 300, 400, 500};
    const vector<size_t> sizes_odd  = {11, 21, 41, 61, 81, 101, 151, 201, 251, 301, 401, 501};

    auto run_series = [](const vector<size_t> &sizes, ofstream &out, const string &type)
    {
        cout << "\n--- Серия замеров (" << type << " размеры) ---\n";
        cout << setw(6) << "N"
             << setw(16) << "Стандартный (с)"
             << setw(16) << "Виноград (с)"
             << setw(20) << "Оптимиз. Виноград\n";

        for (size_t n : sizes)
        {
            Matrix a = generate_matrix(n, n);
            Matrix b = generate_matrix(n, n);

            int repeats = (n <= 100) ? 20 : (n <= 300 ? 5 : 2);

            double t_std = measure_time_sec([&]() { return multiply_standard(a, b); }, repeats);
            double t_win = measure_time_sec([&]() { return multiply_winograd(a, b); }, repeats);
            double t_opt = measure_time_sec([&]() { return multiply_winograd_opt(a, b); }, repeats);

            out << n << "," << t_std << "," << t_win << "," << t_opt << "\n";

            cout << setw(6) << n
                 << setw(16) << fixed << setprecision(6) << t_std
                 << setw(16) << t_win
                 << setw(20) << t_opt << endl;
        }
    };

    run_series(sizes_even, file_even, "чётные");
    run_series(sizes_odd, file_odd, "нечётные");

    cout << "\nРезультаты замеров сохранены в 'results_even.csv' и 'results_odd.csv'.\n";
}