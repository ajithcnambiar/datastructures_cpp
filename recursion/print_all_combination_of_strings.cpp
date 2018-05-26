#include <iostream>
#include <vector>
using namespace std;


// abcd

void get_all_combinations(vector<int> str, int N, int k)
{
    if (N <= 0)
    {
        for (int i =str.size()-1; i >= 0; i--) cout << str[i] ;
        cout << endl;
        return;
    }

    for (int i = 0; i < k; i++)
    {
        str[N-1] = i;
        get_all_combinations(str, N-1, k );
    }
}

int main ()
{
    int N = 3;
    int k = 2;
    vector<int> str(N);
    get_all_combinations(str, N, k);
    return 0;
}