#include <iostream>
#include <vector>
#include "../util/show.cpp"
using namespace std;

class MaxPQ
{
    int N;
    int size;
    vector<int> pq;
    void exch (int i, int j)
    {
        int t = pq[i];
        pq[i] = pq[j];
        pq[j] = t;
    }
    bool less( int i, int j)
    {
        return pq[i] < pq[j];
    }
    void swim(int k)
    {
        while( k > 1 )
        {
            if (less (k, k/2)) break;
            exch(k, k/2);
            k = k/2;
        }
    }
    void sink (int k)
    {
        while( 2*k <= size)
        {
            int j = 2*k;
            if (j < size && less(j, j+1))j++;
            if (less(j, k)) break;
            exch(k, j);
            k = j;
        }
    }
public:
    MaxPQ(int capacity) : N(capacity), size(0)
    {
        pq.resize(N+1);
    }

    void insert(int i)
    {
        pq[++size] = i;
        swim(size);
    }
    int max()
    {
        return pq[1];
    }
    void deleteMax()
    {
        exch(1, size--);
        sink(1);
        //cout << endl;
        //showVector(pq);
    }
    bool isEmpty()
    {
        return size == 0;
    }
};

int main ()
{
    vector<int> v ({4, 5, 1, 9, 10, 3});
    MaxPQ pq(v.size());
    
    auto i = v.begin ();

    while (i != v.end())
    {
        pq.insert(*i);
        cout << pq.max() << " ";
        i++;
    }

    cout << endl; 

    while (!pq.isEmpty())
    {
        cout << pq.max() << " ";
        pq.deleteMax();
    }

}