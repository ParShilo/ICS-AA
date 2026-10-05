#include "array.hpp"

using namespace std;

vector<int> generate_array(int n)
{
    vector<int> arr(n);
    iota(arr.begin(), arr.end(), 1);
    random_device rd;
    mt19937 g(rd());
    shuffle(arr.begin(), arr.end(), g);
    return arr;
}

void print_array(const vector<int>& arr)
{
    for (int val : arr) 
        cout << val << " ";
    cout << "\n";
}