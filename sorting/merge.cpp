#include <vector>
#include "../util/show.cpp"
using namespace std; 

// 0 2 4 8 1 3 5 7 9 a
// 0 2 4 8 1 3 5 7 9 aux
// 0 1 2 3 4 5 6 7 8 idx -> i, j, k

// lo 0 hi 8 mid 4, k = 0, i = 0, j = 4

// 0 2 4 8 1 3 5 7 9 a, k = 0, i = 1, j = 4
// 0 1 4 8 1 3 5 7 9 a, k = 1, i = 1, j = 5
// 0 1 2 8 1 3 5 7 9 a, k = 2, i = 2, j = 5
// 0 1 2 3 1 3 5 7 9 a, k = 3, i = 2, j = 6
// 0 1 2 3 4 3 5 7 9 a, k = 4, i = 3, j = 6
// 0 1 2 3 4 5 5 7 9 a, k = 4, i = 3, j = 7
// 0 1 2 3 4 5 7 7 9 a, k = 4, i = 3, j = 8
// 0 1 2 3 4 5 7 8 9 a, k = 4, i = 4, j = 8
// 0 1 2 3 4 5 7 8 9 a, k = 4, i = 4, j = 9

class MergeSort
{
    bool less(vector<int>& a, int i, int j)
    {
        return a[i] < a[j];
    }

    void merge (vector<int>& a, vector<int>& aux, int lo, int mid, int hi)
    {
        for (int k = lo; k <= hi; k++) aux[k] = a[k];

        int i = lo;
        int j = mid+1;

        for (int k = lo; k <= hi; k++)
        {
            if (i > mid)              a[k] = aux[j++];
            else if (j > hi)          a[k] = aux[i++];
            else if (less(aux, j, i)) a[k] = aux[j++];
            else                      a[k] = aux[i++];
        }
    }

    void divide_and_merge (vector<int>& a, vector<int>& aux, int lo, int hi)
    {
        if (hi <= lo) return;
        int m = lo + (hi - lo)/2;
        divide_and_merge(a, aux, lo, m);
        divide_and_merge(a, aux, m+1, hi);
        merge(a, aux, lo, m, hi);
    }

public:
    MergeSort(vector<int> bag)
    {
        vector<int> aux(bag);
        divide_and_merge(bag, aux, 0, bag.size()-1);
        showVector(bag);
    }
};

int main()
{
    MergeSort m({0, 2, 4, 6, 1, 3, 5, 7, 9});
    return 0;
}