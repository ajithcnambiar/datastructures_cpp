#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class UndirectedGraph
{
    vector<vector<int>> G;
    int number_of_connected_comps;
    
    void DFS(int v, vector<bool>& visited)
    {
        visited[v] = true;
        auto adj_itr = G[v].begin();
        while (adj_itr != G[v].end())
        {
            if(!visited[*adj_itr])
            {
                DFS(*adj_itr, visited);
            }
            adj_itr++;
        }
    }
public:
    UndirectedGraph(int v):number_of_connected_comps(0)
    {
        G.resize(v);
    }    
    void addEdge(int i, int j)
    {
        if (i == j) return;
        G[i].push_back(j);
        G[j].push_back(i);
    }
    void doDFS()
    {
        vector<bool> visited(G.size(), false);
        for (int i = 0 ; i < G.size(); i++)
        {
            if (!visited[i])
            {
                DFS(i, visited);
                number_of_connected_comps++;
            }
        }
    }
    void print()
    {
        cout << "Graph looks like" << endl;
        for (int i = 0 ; i < G.size(); i++)
        {
            cout << "vertex = " << i << " --> ";
            for (int j= 0; j < G[i].size(); j++)
            {
                cout << G[i][j] << " ";
            }
            cout << endl;
        }
        cout << "number of connected components --> " << number_of_connected_comps << endl;
    }
};

int main ()
{
    std::ifstream ifs("undirectedgraph_input.txt");

    if (!ifs.is_open())
    {
        cout << "file is not opened" << endl;
        return 0;
    }

    int v;
    ifs >> v;
    cout << "vertex = " << v << endl;
    int i;
    int j;
    UndirectedGraph g(v);
    while(ifs)
    {
        ifs >> i >> j;
        cout << i << " " << j << endl;
        g.addEdge(i, j);
    }
    ifs.close();
    g.doDFS();
    g.print();
}