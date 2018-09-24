#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <math.h>
using namespace std;

typedef unsigned long long ll;

struct Graph
{
    vector<ll> euler_path;
    vector<ll> euler_depth;
    vector<ll> depth;
    vector<ll> path;
    vector<ll> parent;
    // Idx of a node on euler path for its first appearance
    vector<ll> FirstAppearance;
    vector<vector<ll>> G;
    ll root;
    Graph(ll n, ll r = 0) : root(r)
    {
        G.resize(n+r);
        depth.resize(G.size(), -1);
        parent.resize(G.size(), -1);
        FirstAppearance.resize(G.size(), -1);
    }
    void AddEdge(ll a, ll b)
    {
        G[a].push_back(b);
        G[b].push_back(a);
    }
    // O(n)
    void PopulateDepth(ll v)
    {
        queue<ll> Q;
        Q.push(v);
        depth[v] = 0;
        vector<bool> visited(G.size(), false);
        visited[v] = true;
        while(!Q.empty())
        {
            auto cur = Q.front();
            auto neighbours = G[cur];
            auto n_itr = neighbours.begin();
            while (n_itr != neighbours.end())
            {
                if(!visited[*n_itr])
                {
                    Q.push(*n_itr);
                    depth[*n_itr] = depth[cur]+1;
                    visited[*n_itr] = true;
                    parent[*n_itr] = cur;
                }
                n_itr++;
            }
            Q.pop();
        }
    }
    // O(n)
    void PopulateEulerPath(ll v, vector<bool>& visited)
    {
        visited[v] = true;
        euler_path.push_back(v);
        euler_depth.push_back(depth[v]);
        if(FirstAppearance[v] == -1) FirstAppearance[v] = euler_path.size() - 1;
        auto neighbours = G[v];
        auto neighbours_itr = G[v].begin();
        while (neighbours_itr != G[v].end())
        {
            if(!visited[*neighbours_itr])
            {
                PopulateEulerPath(*neighbours_itr, visited);
                euler_path.push_back(v);
                euler_depth.push_back(depth[v]);
                if(FirstAppearance[*neighbours_itr] == -1) FirstAppearance[*neighbours_itr] = euler_path.size() - 1;
            }
            neighbours_itr++;
        }
    }
    void PrintVector(const string&& str, vector<ll>& v, bool index = true)
    {
        cout << str << '\n';
        for (ll i = 0; i < v.size(); i++)
        {
            if(index)
                cout << i << " --> " <<v[i] << ", ";
            else
                cout << v[i] << ", ";
        }
        cout << '\n';
    }
    void Process()
    {
        PopulateDepth(root);
        //PrintVector("Depth :", depth);
        vector<bool> visited(G.size(), false);
        PopulateEulerPath(root, visited);
        //PrintVector("Euler Path :", euler_path, false);
        //PrintVector("Euler Depth :", euler_depth, false);
    }
};

#define HUGE_NUMBER 18446744073709551615 

class Min
{
public:
    static ll GetMin(vector<ll>& v, ll a, ll b)
    {
        return v[a] < v[b] ? a : b;
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

class SegTree
{
protected:
    vector<ll> m_Tree;
    vector<ll> m_input;
    void CreateSegTree(ll low, ll high, ll pos)
    {
        if(low == high)
        {
            m_Tree[pos] = low;
            return;
        }
        ll mid = (low + high)/2;
        CreateSegTree(low, mid, 2*pos+1);
        CreateSegTree(mid+1, high, 2*pos+2);
        m_Tree[pos] = DoOperation(m_Tree[2*pos+1], m_Tree[2*pos+2]);
    }

    ll Traverse(ll qlow, ll qhigh, ll tree_low, ll tree_high, ll pos)
    {
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

protected:
    virtual ll DoOperation(ll, ll) = 0;
    virtual ll NoOverlappingValue() = 0;

public:
    void Initialize()
    {
        m_Tree.resize(NextPowerOf2::NextPower(m_input.size()) -1, HUGE_NUMBER);
        CreateSegTree(0, m_input.size()-1, 0);
    }
    SegTree(const vector<ll>& input):m_input(input){}
};

class MinSegTree : public SegTree
{
public:
    ll DoOperation( ll a, ll b)
    {
        return Min::GetMin(m_input, a, b);
    }
    ll NoOverlappingValue()
    {
        return HUGE_NUMBER;
    }
    MinSegTree(const vector<ll>& v) : SegTree(v){}
    ll GetMin(ll l, ll h)
    {
        return Traverse(l, h, 0, m_input.size()-1, 0);
    }
};

struct LCA
{
    const Graph& G;
    MinSegTree rgMinQuery;
    LCA(const Graph& g) : G(g), rgMinQuery(g.euler_depth)
    {
        rgMinQuery.Initialize();
    }
    ll GetLCA(ll a, ll b)
    {
        // 1. Euler path
        // 2. Depth of each node in Euler path
        // 3. Get the first appearance of each node in euler path
        // 4. Get the minimum depth node between identified nodes in the euler path
        auto lowest_idx = G.FirstAppearance[a] < G.FirstAppearance[b] ? G.FirstAppearance[a] : G.FirstAppearance[b];
        auto next_idx = lowest_idx == G.FirstAppearance[a] ? G.FirstAppearance[b] : G.FirstAppearance[b];
        auto idxEulerDepth = rgMinQuery.GetMin(lowest_idx, next_idx);
        return G.euler_path[idxEulerDepth];
    }
};

int main()
{
    ifstream ifs;
    ifs.open("euler");
    ll n, e;
    ifs >> n >> e;
    Graph G(n, 1);
    ll x;
    ll y;
    while(e--)
    {
        ifs >> x >> y;
        G.AddEdge(x, y);
    }
    G.Process();

    LCA lca(G);
    ll res = lca.GetLCA(1, 7);
//    cout << res << endl;

    
    return 0;
}