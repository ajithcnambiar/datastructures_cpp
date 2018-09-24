#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
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
    void PrllVector(const string&& str, vector<ll>& v, bool index = true)
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
        PrllVector("Depth :", depth);
        vector<bool> visited(G.size(), false);
        PopulateEulerPath(root, visited);
        PrllVector("Euler Path :", euler_path, false);
        PrllVector("Euler Depth :", euler_depth, false);
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
    return 0;
}