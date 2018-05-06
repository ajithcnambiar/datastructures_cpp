#include <iostream>
#include <vector>
using namespace std;
class node
{
public:
    node(int key, int val) : l(NULL), r(NULL), color(true), k(key), v(val)
    {}
    node* l;
    node* r;
    int k;
    int v;
    bool color;
};
class llrb_tree
{
    node* root;

//      h                    x
//     / \                  / \
//    hl  x                h
//       / \              / \
//                       hl

    node* leftRotate(node* h)
    {
        node* x = h->r; if(h == root) root = x;
        h->r = x->l;
        x->l = h;
        x->color = h->color;
        h->color = true;
        return x;
    }

//     h                    x
//    / \                  / \
//   x                        h
//  / \

    node* rightRotate(node* h)
    {
        node* x = h->l; if(h == root) root = x;
        h->l = x->r;
        x->r = h;
        x->color = h->color;
        h->color = true;
        return x;
    }

    void flip(node* h)
    {
        h->l->color = false;
        h->r->color = false;
        h->color = true;
    }

    bool isRed(node* h)
    {
        if(!h) return false;
        return h->color;
    }

    node* put(node* h, int k, int v)
    {
        if (!h) {h = new node(k, v); if(!root) root = h;}
        else if(k < h->k) h->l = put(h->l, k, v);
        else if(k > h->k) h->r = put(h->r, k, v);
        else h->v = v;

        if(isRed(h->r) && !isRed(h->l)) h = leftRotate(h);
        if(isRed(h->l) && isRed(h->l->l)) h = rightRotate(h);
        if(isRed(h->l) && isRed(h->r)) flip(h);

        return h;
    }

    node* get (node* x, int k)
    {
        if(!x) return NULL;
        if(k < x->k) return get(x->l, k);
        else if (k > x->k) return get(x->r, k);
        else return x;
    }

    void validate_lengths(node* x, int h)
    {
        if(!x) return ;
        
        if(!x->l && !x->r) 
        {
            cout << "leaf node --> " << x->k << " --> height --> " << h << endl; 
            return;
        }
        validate_lengths(x->l, h+1);
        validate_lengths(x->r, h+1);
    }

    void inorder (node* x)
    {
        if(!x) return;
        inorder(x->l);
        cout << x->k <<" ";
        inorder(x->r);
    }

public:
    llrb_tree() : root(NULL){}

    void put(int k, int v)
    {
        put(root, k, v);
    }

    int get(int k)
    {
        node* t = get (root, k);
        return t ? t->v : -1;
    }

    void validate_lengths()
    {
        validate_lengths(root, 0);
        cout << endl;
    }

    void inorder()
    {
        inorder(root);
        cout << endl;
    }

};

int main()
{
    llrb_tree tree;
    vector<int> v({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15});
    
    auto i = v.begin();
    while (i != v.end())
    {
        tree.put(*i, -1);
        i++;
    }
    tree.validate_lengths();

    tree.inorder();

}