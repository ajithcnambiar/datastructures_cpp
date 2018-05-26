#include <iostream>
#include <vector>
using namespace std;

template<class V>
class dl_node
{
public:
    dl_node<V>* next;
    dl_node<V>* prev;
    V data;
    dl_node(): prev(NULL), next(NULL){}
};

template<class V>
class DoublyLinkedList
{
    dl_node<V>* first;
    dl_node<V>* last;
    int size;
public:
 DoublyLinkedList() : first(NULL), last(NULL), size(0){}

 dl_node<V>* push_back (V d)
 {
     dl_node<V>* n = new dl_node<V>();
     n->data = d;
     n->next = NULL;
     n->prev = last;
     
     if(!first) first = n;
     
     if(last) last->next = n;
     last = n;
     size++;
     return n;
 }

 dl_node<V>* push_front(V d)
 {
     if(!first){ return push_back(d);}
     dl_node<V>* n = new dl_node<V>();
     n->data = d;

     dl_node<V>* nowFirst = first;

     nowFirst->prev = n;
     n->next = nowFirst;

     first = n;
     size++;
     return n;
 }

 void deleteNode(dl_node<V>* n)
 {
     if(!n) return;
     
     size--;
     if(n == first)
     {
         dl_node<V>* nFirst = first->next;
         if(nFirst) nFirst->prev = NULL;
         first = nFirst;
         delete n;n = NULL;
         return;
     }
     else if (n == last)
     {
        dl_node<V>* nLast = last->prev;
        if(nLast) nLast->next = NULL;
        last = nLast;
        delete n;n = NULL;
        return;
     }
     else
     {
        dl_node<V>* nNext = n->next;
        dl_node<V>* nPrev = n->prev;
        delete n; n = NULL;
        nNext->prev = nPrev;
        nPrev->next = nNext;
        return;
     }
 }

 dl_node<V>* getNode(V d)
 {
     dl_node<V>* r = NULL;
     dl_node<V>* c = first;
     while(c)
     {
         if (c->data == d) {r = c; break;}
         c = c->next;
     }
     return r;
 }

 dl_node<V>* back()
 {
     return last;
 }

 void printForward()
 {
     dl_node<V>* c =first;
     while (c)
     {
         cout << c->data  ;
         c = c->next;
     }
     cout << endl;
 }

 void printBackward()
 {
     dl_node<V>* c = last;
     while(c)
     {
         cout << c->data ;
         c = c->prev;
     }
     cout << endl;
 }

 int getSize()
 {
     return size;
 }
  
};

/*int main ()
{
    DoublyLinkedList<int> dl;
    vector<int> v ({4, 8, 2, 0, 1, 3, 9});

    vector<int>::iterator itr = v.begin();
    while (itr != v.end())
    {
        dl.push(*itr);
        itr++;
    }

    dl.printForward();
    dl.printBackward();

    dl.deleteNode(dl.getNode(4));
    dl.printForward();
    dl.printBackward();

    dl.deleteNode(dl.getNode(9));
    dl.printForward();
    dl.printBackward();
    
    dl.deleteNode(dl.getNode(0));
    dl.printForward();
    dl.printBackward();


    dl.push_front(10);
    dl.push_front(11);
    dl.printForward();
    dl.printBackward();

    return 0;
}*/