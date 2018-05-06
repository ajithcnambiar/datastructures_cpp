#include <iostream>
#include <vector>
using namespace std;

// Find O(logN)
// Union O(NlogN) N objects over N

class QuickUnion
{
    vector<int> id;
    vector<int> sz;
    int root(int p)
    {
        auto i = id[p];
        while(i != id[i]) i = id[i];
        return i;
    }
public:
    QuickUnion(int N):id(N), sz(N, 0)
    {
        for(int i = 0 ; i < N; i++)
        {
            id[i] = i;
        }
    }

    bool IsConnected(int p, int q)
    {
        return root(p) == root(q);
    }

    int Find (int q)
    {
        return root(q);
    }

    void Union(int p, int q)
    {
        int p_id = root(p);
        int q_id = root(q);

        if(sz[p_id] < sz[q_id]) {id[p_id] = q_id; sz[q_id] += sz[p_id];}
        else {id[q_id] = p_id; sz[p_id] += sz[q_id];}
    }
};


void checkPoint (QuickUnion uf, int p, int q)
{
    auto res = "";
    cout << p << " and " << q << " are ";
    res = uf.IsConnected(p, q) ? "connected" : "not connected";
    cout << res << endl;
}

int main ()
{
    QuickUnion uf(10);
    // false case
    checkPoint(uf, 1, 3);
    checkPoint(uf, 2, 8);

    uf.Union(1, 5);
    uf.Union(5, 3);
    uf.Union(5, 1);

    // Reflexive
    checkPoint(uf, 1, 1);

    // symmetric
    checkPoint(uf, 1, 5);
    checkPoint(uf, 5, 1);

    // transitive
    checkPoint(uf, 1, 3);

    // false case
    checkPoint(uf, 1, 8);
    return 0;
}