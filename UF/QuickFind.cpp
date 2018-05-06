#include <iostream>
#include <vector>
using namespace std;

// Union of N objects over N  = O(N^2)
// Find O(1)
// Initialize O(N)
class QuickFind
{
    vector<int> id;
public:
    QuickFind(int N) : id(N)
    {
        for (int i = 0; i < N; i++)
        {
            id[i] = i;
        }
    }

    void Union(int p, int q)
    {
        auto id_p = id[p];
        auto id_q = id[q];

        for (int i = 0; i < id.size(); i++)
        {
            if(id[i] == id_q)
            {
                id[i] = id_p;
            }
        }
    }

    int Find(int i)
    {
        return id[i];
    }

    bool IsConnected(int p, int q)
    {
        return id[p] == id[q];
    }
};


void checkPoint (QuickFind uf, int p, int q)
{
    auto res = "";
    cout << p << " and " << q << " are ";
    res = uf.IsConnected(p, q) ? "connected" : "not connected";
    cout << res << endl;
}

int main()
{
    QuickFind uf(10);

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