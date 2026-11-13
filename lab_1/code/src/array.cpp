#include "array.hpp"
#include <set>
#include <random>
#include <algorithm>

using namespace std;

vector<int> generate_array(int n)
{
    set<int> unique_vals;
    random_device rd;
    mt19937 gen(rd());
    
    int max_val = max(100000, n * 10);
    uniform_int_distribution<> distrib(1, max_val);

    while (unique_vals.size() < static_cast<size_t>(n))
    {
        unique_vals.insert(distrib(gen));
    }

    vector<int> arr(unique_vals.begin(), unique_vals.end());
    
    shuffle(arr.begin(), arr.end(), gen);
    
    return arr;
}

void print_array(const vector<int>& arr)
{
    for (int val : arr) 
        cout << val << " ";
    cout << "\n";
}