#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;


// Find the number of k-complementary pairs

int solution(int K, vector<int>& A)
{
    int res = 0;
    unordered_map<int,int> num2idx;
    int N = A.size();
    for (int k = 0; k < N; k++)
    {
        num2idx[k] += 1;
    }
    for (int k = 0; k < N; k++)
    {
        auto f = K - A[k];
        res += num2idx[f];
    }
    return res;
}

int main()
{
    vector<int> v({1, 8, -3, 0, 1, 3, -2, 4, 5});
    cout << solution (6, v) << endl;
    return 0;
}