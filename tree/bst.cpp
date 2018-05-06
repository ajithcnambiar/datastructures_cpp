#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class node
{
public:
    node* l;
    node* r;
    int k;
    int v;
    int count;
    node(int key, int value) : k(key), v(value), l(NULL), r(NULL), count(0)
    {}
};
class BST
{
    int size(node* x)
    {
        if(!x) return 0;
        return x->count;
    }
    node* root;
    node* get (node* x, int k)
    {
        if(!x) return NULL;

        if(x->k > k) return get (x->l, k);
        else if (x->k < k) return get (x->r, k);
        else return x;
    }
    node* put (node* x, int k, int v)
    {
        if(!x) 
        {
            x = new node(k, v);
            if(!root) root = x;
        }
        else if (k < x->k) x->l = put(x->l, k, v);
        else if(k > x->k) x->r = put(x->r, k, v);
        else x->v = v;
        x->count = 1 + size(x->l) + size(x->r); 
        return x;
    }
    node* floor (node* x, int k)
    {
        if(!x) return NULL;
        if (x->k == k) return x;
        else if (x->k > k) return floor(x->l, k);
        else
        {
            node* t = floor(x->r, k);
            if(!t) return x;
            else return t;
        }
    }
    int rank(node* x, int k)
    {
        if(!x) return 0;
        if (k == x->k) return size(x->l);
        else if (k < x->k) return rank(x->l, k);
        else if (k > x->k) return 1 + size(x->l) + rank(x->r, k);
    }
    void inorder (node* x)
    {
        if(!x) return;
        inorder(x->l);
        cout << x->k << " ";
        inorder(x->r);
    }
    node* min(node* x)
    {
        if(!x) return NULL;
        else if(!x->l) return x;

        return min(x->l);
    }

    node* max(node* x)
    {
        if(!x) return NULL;
        else if(!x->r) return x;

        return max(x->r);
    }

    node* deleteMin(node* x)
    {
        if(!x->l) return x->r;
        x->l = deleteMin(x->l);
        x->count  = 1 + size(x->l) + size(x->r);
        return x;
    }

    node* deleteNode(node* x, int k)
    {
        if(!x) return NULL;

        if(k <x->k) x->l =  deleteNode(x->l, k);
        else if(k > x->k) x->r = deleteNode(x->r, k);
        else
        {
            node* t = x; 
            x = min(x->r); if(t == root) root = x;
            x->r = deleteMin(t->r);
            x->l = t->l;
        }
        x->count = 1 + size(x->l) + size(x->r);
        return x;
    }
    void levelOrder(node* x)
    {
        if(!x) return;
        queue<node*> q;
        q.push(x);
        while(!q.empty())
        {
            auto f = q.front();
            cout << f->k <<" ";
            if(f->l) q.push(f->l);
            if(f->r) q.push(f->r);
            q.pop();
        }
    }
public:
    BST(): root(NULL){}
    int get (int k)
    {
        node* f = get (root, k);
        return f ? f->v : -1;
    }

    void put (int k, int v)
    {
        put(root, k, v);
    }
    int floor (int k)
    {
        node* t = floor(root, k);
        return t ? t->k : -1;
    }
    int rank (int k)
    {
        return rank(root, k);
    }
    void inorder()
    {
        inorder(root);
        cout << endl;
    }
    int min()
    {
        node* x= min(root);
        return x ? x->k : -1;
    }
    int max()
    {
        node* x= max(root);
        return x ? x->k : -1;
    }
    void deleteMin()
    {
        deleteMin(root);
    }
    void deleteNode(int k)
    {
        deleteNode(root, k);
    }
    void levelOrder()
    {
        levelOrder(root);
        cout << endl;
    }
};

int main()
{
    BST tree;
    vector<int> v({3, 2, 0, 5, 1, 9});
    auto i = v.begin();
    while( i != v.end())
    {
        tree.put(*i, 1);
        i++;
    }

    for (int i = 0; i < v.size(); i++)
    {
        cout << "rank of " << v[i] << " --> " << tree.rank(v[i]) << endl;
    }

    cout << "get the value of 9 --> " << tree.get(9) << endl;
    cout << "get the value of 10 --> " << tree.get(10) << endl;
    cout << "floor of 6 --> " << tree.floor(6) << endl;
    cout << "floor of 3 --> " << tree.floor(3) << endl;
    tree.inorder();
    tree.levelOrder();
    cout << "max = " << tree.max() << endl;
    tree.deleteNode(0);
    cout << "after deleting 0" << endl;
    tree.inorder();
    tree.levelOrder();
    cout << "after deleting 3" << endl;
    tree.deleteNode(3);
    tree.inorder();
    tree.levelOrder();

    return 0;
}