#include <iostream>
#include <vector>
using namespace std;

void showVector(vector<int> v)
{
    auto i = v.begin ();
    while (i != v.end())
    {
        cout << *i << " ";
        i++;
    }
    cout << endl;
}