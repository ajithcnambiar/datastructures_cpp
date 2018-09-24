#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

typedef unsigned long long ll;
#define HUGE_NUMBER 18446744073709551615 

class Min
{
public:
    static ll GetMin(ll a, ll b)
    {
        return a < b ? a : b;
    }
};

class NextPowerOf2
{
public:
    static ll NextPower(ll N)
    {
        ll ret = 0;
        while(N > 0)
        {
            N = N >> 1;
            ret++;
        }
        return pow(2, ret);
    }
};

class DebugPrint
{
public:
    static void PrintVect(vector<ll>& v)
    {
        auto i = v.begin();
        while (i != v.end())
        {
            cout << *i << " ";
            i++;
        }
        cout << '\n';
    }
};

class SegTree
{
protected:
    vector<ll> m_Tree;
    vector<ll> m_input;
    void CreateSegTree(ll low, ll high, ll pos)
    {
        if(low == high)
        {
            m_Tree[pos] = m_input[low];
            return;
        }
        ll mid = (low + high)/2;
        CreateSegTree(low, mid, 2*pos+1);
        CreateSegTree(mid+1, high, 2*pos+2);
        m_Tree[pos] = DoOperation(m_Tree[2*pos+1], m_Tree[2*pos+2]);
    }

    //                           0(0)
    //             1(1)                        0(2)
    //     3(3)          1(4)           0(5)            8(6)
    // 3(7)   4(8)   5(9)   1(10)   2(11)   0(12)   8(13)   8(14)
    //  0      1      2      3        4       5       6       7
    //

    ll Traverse(ll qlow, ll qhigh, ll tree_low, ll tree_high, ll pos)
    {
        //cout << qlow << " " << qhigh << " " << tree_low << "  " << tree_high << "  " << pos << '\n';
        if(tree_low >= qlow && tree_high <= qhigh)
        {
            return m_Tree[pos];
        }
        else if (qhigh < tree_low || qlow > tree_high)
        {
            return NoOverlappingValue();
        }
        else
        {
            ll mid = (tree_low + tree_high)/2;
            return DoOperation(Traverse(qlow, qhigh, tree_low, mid, 2*pos+1),
                                  Traverse(qlow, qhigh, mid+1, tree_high, 2*pos+2));
        }
    }
    void UpdateSegTreeRange(ll low, ll high, ll pos, ll delta)
    {
        if(low == high)
        {
            m_Tree[pos] = m_input[low];
            return;
        }
        ll mid = (low + high)/2;
        UpdateSegTreeRange(low, mid, 2*pos+1, delta);
        UpdateSegTreeRange(mid+1, high, 2*pos+2, delta);
        m_Tree[pos] = DoOperation(m_Tree[2*pos+1], m_Tree[2*pos+2]);
    }
    // 0 0 0 1 0 0 0 3 4 5 1 2 0 8 8
    // 0 1 0 3 1 0 8

//              0
//       1             0
//   3      1       0       8
// 3  4   5   1   2   0   8   8

protected:
    virtual ll DoOperation(ll, ll) = 0;
    virtual ll NoOverlappingValue() = 0;

public:
    void Initialize()
    {
        m_Tree.resize(NextPowerOf2::NextPower(m_input.size()) -1, HUGE_NUMBER);
        CreateSegTree(0, m_input.size()-1, 0);
    }
    SegTree(vector<ll>& input):m_input(input)
    {}
    void UpdateSegTreeRange(ll qlow, ll qhigh, ll delta)
    {
        for (ll i = qlow; i <= qhigh; i++)
        {
            m_input[i] += delta;
        }
        UpdateSegTreeRange(0, m_input.size()-1, 0, delta);
    }
};


class SumSegTree : public SegTree
{
public:
    ll DoOperation(ll a, ll b)
    {
        return a + b;
    }
    ll NoOverlappingValue()
    {
        return 0;
    }
    SumSegTree(vector<ll>& v) : SegTree(v){}
    ll GetSum(ll l, ll h)
    {
        return Traverse(l, h, 0, m_input.size()-1, 0);
    }
};

class MinSegTree : public SegTree
{
public:
    ll DoOperation( ll a, ll b)
    {
        return Min::GetMin(a, b);
    }
    ll NoOverlappingValue()
    {
        return HUGE_NUMBER;
    }
    MinSegTree(vector<ll>& v) : SegTree(v){}
    ll GetMin(ll l, ll h)
    {
        return Traverse(l, h, 0, m_input.size()-1, 0);
    }
    void Print()
    {
        DebugPrint::PrintVect(m_Tree);
    }
};

int main ()
{
    vector<ll> v({3, 4, 5, 1, 2, 0, 8, 8});
    //            0  1  2  3  4  5  6  7
    MinSegTree minSg(v);
    minSg.Initialize();

    minSg.UpdateSegTreeRange(0, 4, 3);

    minSg.Print();
    cout << minSg.GetMin(5, 7) << '\n';

    vector<ll> v2({3, 4, 5, 1, 2, 0, 8, 8});
    SumSegTree sSg(v2);
    sSg.Initialize();
    sSg.UpdateSegTreeRange(0, 4, 3);
    cout << sSg.GetSum(3, 4) << '\n';
}